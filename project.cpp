#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<ctime>

using namespace std;

class Vehicle {
    protected: 
    string vehicleID;
    string model;
    double rentalRate;
    int stock;
    public:
    Vehicle(string id, string m, double r, int s)
        : vehicleID(id), model(m), rentalRate(r), stock(s)  {
    }
    virtual ~Vehicle() {}
    void displayInfo() const {
        cout << "Vehicle ID: " << vehicleID << "|";
        cout << "Model: " << model << "|";
        cout << "Rental Rate: " << rentalRate <<"|"<< endl;
        cout << "Stock: " << stock << endl;
    }
    double getRentalRate() const {
        return rentalRate;
    }
    string getVehicleID() const {
        return vehicleID;
    }
    string getModel() const {
        return model;
    }
    int getStock() const {
        return stock;
    }

};
vector<Vehicle> LoadCarData() {
    vector<Vehicle> cars;
    ifstream file("cars.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return cars;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, model;
        double rate;
        int stock; 
        ss >> id >> model >> rate>> stock;
        Vehicle car(id, model, rate, stock);
        car.displayInfo();
        cars.push_back(car);
    }
    file.close();
    return cars;
}
vector<Vehicle> LoadBikeData() {
    vector<Vehicle> bikes;
    ifstream file("bikes.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return bikes;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, model;
        double rate;
        int stock;
        ss >> id >> model >> rate >> stock;
        Vehicle bike(id, model, rate, stock);
        bike.displayInfo();
        bikes.push_back(bike);
    }
    file.close();
    return bikes;
}
vector<Vehicle> LoadTruckData() {
    vector<Vehicle> trucks;
    ifstream file("trucks.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return trucks;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, model;
        double rate;
        int stock;
        ss >> id >> model >> rate >> stock;
        Vehicle truck(id, model, rate, stock);
        truck.displayInfo();
        trucks.push_back(truck);
    }
    file.close();
    return trucks;
}
/// @brief Displays the vehicle management menu and handles user interactions for renting vehicles or accessing the admin menu.
void vehicleMenu() {
    int choice;
    menu:
    cout << "Welcome to the Vehicle Rental System!" << endl;
    cout << "Press Enter to continue..." << endl;
    cin.ignore();

    cout << "---Vehicle Management Menu---" << endl;
    cout << "1.Car" << endl;
    cout << "2.Bike" << endl;
    cout << "3.Truck" << endl;
    cout << "4.Admin Menu" << endl;
    cin >> choice;
    switch(choice) {
        case 1: {
            cout << "Car selected." << endl;
            vector<Vehicle> cars = LoadCarData();
            cout<< "select a vehicle to rent (enter vehicle ID): ";
            string vehicleID;
            cin >> vehicleID;
            string selectedModel;
            double rentalRate = 0;
            int stock;
            bool found = false;
            for (const auto& car : cars) {
                if (car.getVehicleID() == vehicleID) {
                    selectedModel = car.getModel();
                    rentalRate = car.getRentalRate();
                    stock = car.getStock();
                    found = true;
                    break;
                }
            }
            if( stock > 0){
            if (found) {
                cout << "You have selected vehicle : " << vehicleID << " | " << selectedModel << ". Proceeding to rental process..." << endl;
                cout << "Enter rental duration in days: ";
                int days;
                cin >> days;
                cout << "Calculating rental cost for " << days << " days..." << endl;
                double TotalRate = days * rentalRate;
                cout << "Total rental cost: $" << TotalRate << endl;
                cout << "Enter name for the rental agreement: ";
                string renterName;
                cin >> renterName;
                cout << "Enter contact number: " << endl;
                string contactNumber;
                cin >> contactNumber;
                ofstream file("RentedVehicle.txt", ios::app);
                if (file.is_open()) {
                    file << "Renter Name: " << renterName << endl;
                    file << "Contact Number: " << contactNumber << endl;
                    file << "Vehicle ID: " << vehicleID << endl;
                    file << "Model: " << selectedModel << endl;
                    file << "Rental Duration (days): " << days << endl;
                    file << "Total Rental Cost: $" << TotalRate << endl;
                    file << "-----------------------------" << endl;
                    file.flush();
                    file.close();
                } else {
                    cerr << "Error opening rental log file!" << endl;
                }
            } else {
                cout << "Vehicle not found." << endl;
            }
            ofstream file("cars.txt", ios::trunc);
            if (file.is_open()) {
                for (const auto& car : cars) {
                    if (car.getVehicleID() == vehicleID) {
                        file << car.getVehicleID() << " " << car.getModel() << " " << car.getRentalRate() << " " << car.getStock() - 1 << endl;
                    } else {
                        file << car.getVehicleID() << " " << car.getModel() << " " << car.getRentalRate() << " " << car.getStock() << endl;
                    }
                }
                file.flush();
                file.close();
            } else {
                cerr << "Error opening file to update stock!" << endl;
            }
        }
            break;
        }
        case 2: {
            cout << "Bike selected." << endl;
            vector<Vehicle> bikes = LoadBikeData();
            cout<< "select a vehicle to rent (enter vehicle ID): ";
            string vehicleID;
            cin >> vehicleID;
            string selectedModel;
            double rentalRate = 0;
            int stock;
            bool found = false;
            for (const auto& bike : bikes) {
                if (bike.getVehicleID() == vehicleID) {
                    selectedModel = bike.getModel();
                    rentalRate = bike.getRentalRate();
                    stock = bike.getStock();
                    found = true;
                    break;
                }
            }if(stock>0){
            if (found) {
                cout << "You have selected vehicle : " << vehicleID << " | " << selectedModel << ". Proceeding to rental process..." << endl;
                cout << "Enter rental duration in days: ";
                int days;
                cin >> days;
                cout << "Calculating rental cost for " << days << " days..." << endl;
                double TotalRate = days * rentalRate;
                cout << "Total rental cost: $" << TotalRate << endl;
                cout << "Enter name for the rental agreement: ";
                string renterName;
                cin >> renterName;
                cout << "Enter contact number: " << endl;
                string contactNumber;
                cin >> contactNumber;
                ofstream file("RentedVehicle.txt", ios::app);
                if (file.is_open()) {
                    file << "Renter Name: " << renterName << endl;
                    file << "Contact Number: " << contactNumber << endl;
                    file << "Vehicle ID: " << vehicleID << endl;
                    file << "Model: " << selectedModel << endl;
                    file << "Rental Duration (days): " << days << endl;
                    file << "Total Rental Cost: $" << TotalRate << endl;
                    file << "-----------------------------" << endl;
                    file.flush();
                    file.close();
                } else {
                    cerr << "Error opening rental log file!" << endl;
                }

            } else {
                cout << "Vehicle not found." << endl;
            }
            ofstream file("bikes.txt", ios::trunc);
            if (file.is_open()) {
                for (const auto& bike : bikes) {
                    if (bike.getVehicleID() == vehicleID) {
                        file << bike.getVehicleID() << " " << bike.getModel() << " " << bike.getRentalRate() << " " << bike.getStock() - 1 << endl;
                    } else {
                        file << bike.getVehicleID() << " " << bike.getModel() << " " << bike.getRentalRate() << " " << bike.getStock() << endl;
                    }
                }
                file.flush();
                file.close();
            } else {
                cerr << "Error opening file to update stock!" << endl;
            }

        }
            break;
        }
        case 3: {
            cout << "Truck selected." << endl;
            vector<Vehicle> trucks = LoadTruckData();
            cout<< "select a vehicle to rent (enter vehicle ID): ";
            string vehicleID;
            cin >> vehicleID;
            string selectedModel;
            double rentalRate = 0;
            int stock;
            bool found = false;
            for (const auto& truck : trucks) {
                if (truck.getVehicleID() == vehicleID) {
                    selectedModel = truck.getModel();
                    rentalRate = truck.getRentalRate();
                    stock = truck.getStock();
                    found = true;
                    break;
                }
            }if(stock>0){
            if (found) {
                cout << "You have selected vehicle : " << vehicleID << " | " << selectedModel << ". Proceeding to rental process..." << endl;
                cout << "Enter rental duration in days: ";
                int days;
                cin >> days;
                cout << "Calculating rental cost for " << days << " days..." << endl;
                double TotalRate = days * rentalRate;
                cout << "Total rental cost: $" << TotalRate << endl;
                cout << "Enter name for the rental agreement: ";
                string renterName;
                cin >> renterName;
                cout << "Enter contact number: " << endl;
                string contactNumber;
                cin >> contactNumber;
                ofstream file("RentedVehicle.txt", ios::app);
                if (file.is_open()) {
                    file << "Renter Name: " << renterName << endl;
                    file << "Contact Number: " << contactNumber << endl;
                    file << "Vehicle ID: " << vehicleID << endl;
                    file << "Model: " << selectedModel << endl;
                    file << "Rental Duration (days): " << days << endl;
                    file << "Total Rental Cost: $" << TotalRate << endl;
                    file << "-----------------------------" << endl;
                    file.flush();
                    file.close();
                } else {
                    cerr << "Error opening rental log file!" << endl;
                }
            } else {
                cout << "Vehicle not found." << endl;
            }
            ofstream file("trucks.txt", ios::trunc);
            if (file.is_open()) {
                for (const auto& truck : trucks) {
                    if (truck.getVehicleID() == vehicleID) {
                        file << truck.getVehicleID() << " " << truck.getModel() << " " << truck.getRentalRate() << " " << truck.getStock() - 1 << endl;
                    } else {
                        file << truck.getVehicleID() << " " << truck.getModel() << " " << truck.getRentalRate() << " " << truck.getStock() << endl;
                    }
                }
                file.flush();
                file.close();
            } else {
                cerr << "Error opening file to update stock!" << endl;
            }

        }
            break;
        }
        case 4: {
            cout << "Admin Menu selected." << endl;
            cout << "Enter admin credentials:" << endl;
            cout << "Username: ";
            string username;
            cin >> username;
            cout << "Password: ";
            string password;
            cin >> password;
            if (username == "Employee" && password == "12345678" || username == "Manager" && password =="manager123" || 
                username == "Nautical" && password == "nautyc06" ) {
                cout << "Access granted. Welcome,"<<username <<"!" << endl<< endl;
                cout << "-------------------------------"<<endl <<endl;
                ofstream file("admin_log.txt", ios::app);
                time_t now = time(nullptr);
                char buf[20];
                strftime(buf,sizeof(buf),"%Y-%m-%d|%H:%M:%S",localtime(&now));
                if (file.is_open()) {
                    file << "Admin accessed the system." << endl;
                    file << "------"<<"[ "<<buf<<" ]"<<"-------"<< endl;
                    file <<"Username: " << username << endl;
                    file << "Password: " << password << endl;
                    file << "-----------------------------" << endl;
                    file.flush();
                    file.close();
                } else {
                    cerr << "Error opening log file!" << endl;
                }
            } else {
                cout << "Access denied. Invalid credentials." << endl;
            }
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
    goto menu;


}
int main() {
    vehicleMenu();

    return 0;
}
