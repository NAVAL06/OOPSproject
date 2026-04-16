#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

class Vehicle
{
protected:
    string vehicleID;
    string model;
    double rentalRate;
    int stock;

public:
    Vehicle(string id, string m, double r, int s)
        : vehicleID(id), model(m), rentalRate(r), stock(s)
    {
    }
    virtual ~Vehicle() {}
    void displayInfo() const
    {
        cout << "Vehicle ID: " << vehicleID << "|";
        cout << "Model: " << model << "|";
        cout << "Rental Rate: " << rentalRate << "|";
        cout << "Stock: " << stock << endl;
    }
    double getRentalRate() const
    {
        return rentalRate;
    }
    string getVehicleID() const
    {
        return vehicleID;
    }
    string getModel() const
    {
        return model;
    }
    int getStock() const
    {
        return stock;
    }
};
vector<Vehicle> LoadCarData()
{
    vector<Vehicle> cars;
    ifstream file("cars.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
        return cars;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, model;
        double rate;
        int stock;
        ss >> id >> model >> rate >> stock;
        Vehicle car(id, model, rate, stock);
        car.displayInfo();
        cars.push_back(car);
    }
    file.close();
    return cars;
}
vector<Vehicle> LoadBikeData()
{
    vector<Vehicle> bikes;
    ifstream file("bikes.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
        return bikes;
    }
    string line;
    while (getline(file, line))
    {
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
vector<Vehicle> LoadTruckData()
{
    vector<Vehicle> trucks;
    ifstream file("trucks.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
        return trucks;
    }
    string line;
    while (getline(file, line))
    {
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
void vehicleMenu()
{
    int choice;
    bool running = true;
    while (running)
    {
        cout << "Welcome to the Vehicle Rental System!" << endl;
        cout << "Press Enter to continue..." << endl;
        cin.ignore();

        cout << "---Vehicle Management Menu---" << endl;
        cout << "1.Car" << endl;
        cout << "2.Bike" << endl;
        cout << "3.Truck" << endl;
        cout << "4.Return Vehicle" << endl;
        cout << "5.Admin Menu" << endl;
        cin >> choice;
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); 
            cin.ignore(1000, '\n');
            continue;
        }
        switch (choice)
        {
        case 1:
        {
            cout << "Car selected." << endl;
            vector<Vehicle> cars = LoadCarData();
            cout << "select a vehicle to rent (enter vehicle ID): ";
            string vehicleID;
            cin >> vehicleID;
            string selectedModel;
            double rentalRate = 0;
            int stock;
            bool found = false;
            for (const auto &car : cars)
            {
                if (car.getVehicleID() == vehicleID)
                {
                    selectedModel = car.getModel();
                    rentalRate = car.getRentalRate();
                    stock = car.getStock();
                    found = true;
                    break;
                }
            }
            if (stock > 0)
            {
                if (found)
                {
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
                    if (file.is_open())
                    {
                        file << "Renter Name: " << renterName << endl;
                        file << "Contact Number: " << contactNumber << endl;
                        file << "Vehicle ID: " << vehicleID << endl;
                        file << "Model: " << selectedModel << endl;
                        file << "Rental Duration (days): " << days << endl;
                        file << "Total Rental Cost: $" << TotalRate << endl;
                        time_t now = time(nullptr);
                        char *dt = ctime(&now);
                        file << "Rental Date: " << dt;
                        file << "-----------------------------" << endl;
                        file.flush();
                        file.close();
                    }
                    else
                    {
                        cerr << "Error opening rental log file!" << endl;
                    }
                }
                else
                {
                    cout << "Vehicle not found." << endl;
                }
                ofstream file("cars.txt", ios::trunc);
                if (file.is_open())
                {
                    for (const auto &car : cars)
                    {
                        if (car.getVehicleID() == vehicleID)
                        {
                            file << car.getVehicleID() << " " << car.getModel() << " " << car.getRentalRate() << " " << car.getStock() - 1 << endl;
                        }
                        else
                        {
                            file << car.getVehicleID() << " " << car.getModel() << " " << car.getRentalRate() << " " << car.getStock() << endl;
                        }
                    }
                    file.flush();
                    file.close();
                }
                else
                {
                    cerr << "Error opening file to update stock!" << endl;
                }
            }
            break;
        }
        case 2:
        {
            cout << "Bike selected." << endl;
            vector<Vehicle> bikes = LoadBikeData();
            cout << "select a vehicle to rent (enter vehicle ID): ";
            string vehicleID;
            cin >> vehicleID;
            string selectedModel;
            double rentalRate = 0;
            int stock;
            bool found = false;
            for (const auto &bike : bikes)
            {
                if (bike.getVehicleID() == vehicleID)
                {
                    selectedModel = bike.getModel();
                    rentalRate = bike.getRentalRate();
                    stock = bike.getStock();
                    found = true;
                    break;
                }
            }
            if (stock > 0)
            {
                if (found)
                {
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
                    if (file.is_open())
                    {
                        file << "Renter Name: " << renterName << endl;
                        file << "Contact Number: " << contactNumber << endl;
                        file << "Vehicle ID: " << vehicleID << endl;
                        file << "Model: " << selectedModel << endl;
                        file << "Rental Duration (days): " << days << endl;
                        file << "Total Rental Cost: $" << TotalRate << endl;
                        time_t now = time(nullptr);
                        char *dt = ctime(&now);
                        file << "Rental Date: " << dt;
                        file << "-----------------------------" << endl;
                        file.flush();
                        file.close();
                    }
                    else
                    {
                        cerr << "Error opening rental log file!" << endl;
                    }
                }
                else
                {
                    cout << "Vehicle not found." << endl;
                }
                ofstream file("bikes.txt", ios::trunc);
                if (file.is_open())
                {
                    for (const auto &bike : bikes)
                    {
                        if (bike.getVehicleID() == vehicleID)
                        {
                            file << bike.getVehicleID() << " " << bike.getModel() << " " << bike.getRentalRate() << " " << bike.getStock() - 1 << endl;
                        }
                        else
                        {
                            file << bike.getVehicleID() << " " << bike.getModel() << " " << bike.getRentalRate() << " " << bike.getStock() << endl;
                        }
                    }
                    file.flush();
                    file.close();
                }
                else
                {
                    cerr << "Error opening file to update stock!" << endl;
                }
            }
            break;
        }
        case 3:
        {
            cout << "Truck selected." << endl;
            vector<Vehicle> trucks = LoadTruckData();
            cout << "select a vehicle to rent (enter vehicle ID): ";
            string vehicleID;
            cin >> vehicleID;
            string selectedModel;
            double rentalRate = 0;
            int stock;
            bool found = false;
            for (const auto &truck : trucks)
            {
                if (truck.getVehicleID() == vehicleID)
                {
                    selectedModel = truck.getModel();
                    rentalRate = truck.getRentalRate();
                    stock = truck.getStock();
                    found = true;
                    break;
                }
            }
            if (stock > 0)
            {
                if (found)
                {
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
                    if (file.is_open())
                    {
                        file << "Renter Name: " << renterName << endl;
                        file << "Contact Number: " << contactNumber << endl;
                        file << "Vehicle ID: " << vehicleID << endl;
                        file << "Model: " << selectedModel << endl;
                        file << "Rental Duration (days): " << days << endl;
                        file << "Total Rental Cost: $" << TotalRate << endl;
                        time_t now = time(nullptr);
                        char *dt = ctime(&now);
                        file << "Rental Date: " << dt;
                        file << "-----------------------------" << endl;
                        file.flush();
                        file.close();
                    }
                    else
                    {
                        cerr << "Error opening rental log file!" << endl;
                    }
                }
                else
                {
                    cout << "Vehicle not found." << endl;
                }
                ofstream file("trucks.txt", ios::trunc);
                if (file.is_open())
                {
                    for (const auto &truck : trucks)
                    {
                        if (truck.getVehicleID() == vehicleID)
                        {
                            file << truck.getVehicleID() << " " << truck.getModel() << " " << truck.getRentalRate() << " " << truck.getStock() - 1 << endl;
                        }
                        else
                        {
                            file << truck.getVehicleID() << " " << truck.getModel() << " " << truck.getRentalRate() << " " << truck.getStock() << endl;
                        }
                    }
                    file.flush();
                    file.close();
                }
                else
                {
                    cerr << "Error opening file to update stock!" << endl;
                }
            }
            break;
        }
        case 4:
        {
            cout << "Return Vehicle selected." << endl;
            cout << "Enter vehicle ID to return: ";
            string vehicleID;
            cin >> vehicleID;
            if (vehicleID.substr(0, 3) == "CAR")
            {
                vector<Vehicle> cars = LoadCarData();
                ofstream file("cars.txt", ios::trunc);
                if (file.is_open())
                {
                    for (const auto &car : cars)
                    {
                        if (car.getVehicleID() == vehicleID)
                        {
                            file << car.getVehicleID() << " " << car.getModel() << " " << car.getRentalRate() << " " << car.getStock() + 1 << endl;
                        }
                        else
                        {
                            file << car.getVehicleID() << " " << car.getModel() << " " << car.getRentalRate() << " " << car.getStock() << endl;
                        }
                    }
                    file.flush();
                    file.close();
                }
                else
                {
                    cerr << "Error opening file to update stock!" << endl;
                }
            }
            else if (vehicleID.substr(0, 4) == "BIKE")
            {
                vector<Vehicle> bikes = LoadBikeData();
                ofstream file("bikes.txt", ios::trunc);
                if (file.is_open())
                {
                    for (const auto &bike : bikes)
                    {
                        if (bike.getVehicleID() == vehicleID)
                        {
                            file << bike.getVehicleID() << " " << bike.getModel() << " " << bike.getRentalRate() << " " << bike.getStock() + 1 << endl;
                        }
                        else
                        {
                            file << bike.getVehicleID() << " " << bike.getModel() << " " << bike.getRentalRate() << " " << bike.getStock() << endl;
                        }
                    }
                    file.flush();
                    file.close();
                }
                else
                {
                    cerr << "Error opening file to update stock!" << endl;
                }
            }
            else if (vehicleID.substr(0, 5) == "TRUCK")
            {
                vector<Vehicle> trucks = LoadTruckData();
                ofstream file("trucks.txt", ios::trunc);
                if (file.is_open())
                {
                    for (const auto &truck : trucks)
                    {
                        if (truck.getVehicleID() == vehicleID)
                        {
                            file << truck.getVehicleID() << " " << truck.getModel() << " " << truck.getRentalRate() << " " << truck.getStock() + 1 << endl;
                        }
                        else
                        {
                            file << truck.getVehicleID() << " " << truck.getModel() << " " cout << "Vehicle with ID " << vehicleID << " has been returned. Thank you!" << endl
                                 << endl;
                        }
                    }
                    file.flush();
                    file.close();
                }
                else
                {
                    cerr << "Error opening file to update stock!" << endl;
                }
            }
            else
            {
                cout << "Invalid vehicle ID." << endl;
            }
            break;
        }
        case 5:
        {
            cout << "Admin Menu selected." << endl;
            cout << "Enter admin credentials:" << endl;
            cout << "Username: ";
            string username;
            cin >> username;
            cout << "Password: ";
            string password;
            cin >> password;
            if (username == "Employee" && password == "12345678" || username == "Manager" && password == "manager123" ||
                username == "Nautical" && password == "nautyc06")
            {
                cout << "Access granted. Welcome," << username << "!" << endl << endl;
                cout << "1.View rental records" << endl;
                cout << "2.View vehicle inventory" << endl;
                cout << "3.Add new vehicle" << endl;
                cout << "4.Remove vehicle" << endl;
                cout << "5.Total revenue" << endl;
                cout << "6.Log out" << endl << endl;
                cout << "-------------------------------" << endl << endl;
                int AdminChoice;
                cin >> AdminChoice;
                if (!(cin >> AdminChoice)) {
                    cout << "Invalid input. Please enter a number." << endl;
                    cin.clear(); 
                    cin.ignore(1000, '\n');
                    continue;
                }
                switch (AdminChoice)
                {
                case 1:
                    cout << "Rental Records:" << endl;
                    ifstream rentalFile("RentedVehicle.txt");
                    if (rentalFile.is_open())
                    {
                        string record;
                        while (getline(rentalFile, record))
                        {
                            cout << record << endl;
                        }
                        rentalFile.close();
                    }
                    else
                    {
                        cerr << "Error opening rental records file!" << endl;
                    }
                    break;
                case 2:
                    cout << "Vehicle Inventory:" << endl;
                    cout << "1.Cars" << endl;
                    cout << "2.Bikes" << endl;
                    cout << "3.Trucks" << endl;
                    int inventoryChoice;
                    cin >> inventoryChoice;
                    if (!(cin >> inventoryChoice)) {
                        cout << "Invalid input. Please enter a number." << endl;
                        cin.clear(); 
                        cin.ignore(1000, '\n');
                        continue;
                    }
                    switch (inventoryChoice)
                    {
                    case 1:
                        cout << "Cars:" << endl;
                        LoadCarData();
                        break;
                    case 2:
                        cout << "Bikes:" << endl;
                        LoadBikeData();
                        break;
                    case 3:
                        cout << "Trucks:" << endl;
                        LoadTruckData();
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }
                    break;
                case 3:
                    cout <<"Adding New Vehicle" << endl;
                    cout << "Enter vehicle type (Car/Bike/Truck): ";
                    string vehicleType;
                    cin >> vehicleType;
                    cout << "Enter vehicle ID: ";
                    string newVehicleID;
                    cin >> newVehicleID;
                    cout << "Enter model: ";
                    string newModel;
                    cin >> newModel;
                    cout << "Enter rental rate: ";
                    double newRentalRate;
                    cin >> newRentalRate;
                    cout << "Enter stock quantity: ";
                    int newStock;
                    cin >> newStock;
                    ofstream file;
                    if (vehicleType == "Car")
                    {
                        file.open("cars.txt", ios::app);
                    }
                    else if (vehicleType == "Bike")
                    {
                        file.open("bikes.txt", ios::app);
                    }
                    else if (vehicleType == "Truck")
                    {
                        file.open("trucks.txt", ios::app);
                    }
                    else
                    {
                        cout << "Invalid vehicle type." << endl;
                        break;
                    }
                    break;
                case 4:
                    cout << "Removing Vehicle" << endl;
                    cout << "Enter vehicle type (Car/Bike/Truck): ";
                    string vehicleType;
                    cin >> vehicleType;
                    cout << "Enter vehicle ID to remove: ";
                    string removeVehicleID;
                    cin >> removeVehicleID;
                    if (vehicleType == "Car")
                    {
                        vector<Vehicle> cars = LoadCarData();
                        ofstream file("cars.txt", ios::trunc);
                        if (file.is_open())
                        {
                            for (const auto &car : cars)
                            {
                                if (car.getVehicleID() != removeVehicleID)
                                {
                                    file << car.getVehicleID() << " " << car.getModel() << " " << car.getRentalRate() << " " << car.getStock() << endl;
                                }
                            }
                            file.flush();
                            file.close();
                            cout << "Vehicle removed successfully." << endl;
                        }
                        else
                        {
                            cerr << "Error opening file to update inventory!" << endl;
                        }
                    }
                    else if (vehicleType == "Bike")
                    {
                        vector<Vehicle> bikes = LoadBikeData();
                        ofstream file("bikes.txt", ios::trunc);
                        if (file.is_open())
                        {
                            for (const auto &bike : bikes)
                            {
                                if (bike.getVehicleID() != removeVehicleID)
                                {
                                    file << bike.getVehicleID() << " " << bike.getModel() << " " << bike.getRentalRate() << " " << bike.getStock() << endl;
                                }
                            }
                            file.flush();
                            file.close();
                            cout << "Vehicle removed successfully." << endl;
                        }
                        else
                        {
                            cerr << "Error opening file to update inventory!" << endl;
                        }
                    }
                    else if (vehicleType == "Truck")
                    {
                        vector<Vehicle> trucks = LoadTruckData();
                        ofstream file("trucks.txt", ios::trunc);
                        if (file.is_open())
                        {
                            for (const auto &truck : trucks)
                            {
                                if (truck.getVehicleID() != removeVehicleID)
                                {
                                    file << truck.getVehicleID() << " " << truck.getModel() << " " << truck.getRentalRate() << " " << truck.getStock() << endl;
                                }
                            }
                            file.flush();
                            file.close();
                            cout << "Vehicle removed successfully." << endl;
                        }
                        else
                        {
                            cerr << "Error opening file to update inventory!" << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid vehicle type." << endl;
                    }
                    break;
                case 5:
                    double totalRevenue = 0;
                    ifstream rentalFile("RentedVehicle.txt");
                    if (rentalFile.is_open())                    {
                        string line;
                        while (getline(rentalFile, line))
                        {
                            if (line.find("Total Rental Cost: $") != string::npos)
                            {
                                size_t pos = line.find("$");
                                if (pos != string::npos)
                                {
                                    double cost = stod(line.substr(pos + 1));
                                    totalRevenue += cost;
                                }
                            }
                        }
                        rentalFile.close();
                    }
                    else
                    {
                        cerr << "Error opening rental records file!" << endl;
                    }
                    cout << "Total Revenue: $" << totalRevenue << endl;
                    break;
                case 6:
                    cout << "Logging out..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
                ofstream file("admin_log.txt", ios::app);
                time_t now = time(nullptr);
                char buf[20];
                strftime(buf, sizeof(buf), "%Y-%m-%d|%H:%M:%S", localtime(&now));
                if (file.is_open())
                {
                    file << "Admin accessed the system." << endl;
                    file << "------" << "[ " << buf << " ]" << "-------" << endl;
                    file << "Username: " << username << endl;
                    file << "Password: " << password << endl;
                    // Log admin actions based on AdminChoice
                    switch (AdminChoice)
                    {
                    case 1:
                        file << "Action: Viewed rental records" << endl;
                        break;
                    case 2:
                        file << "Action: Viewed vehicle inventory" << endl;
                        break;
                    case 3:
                        file << "Action: Added new vehicle" << endl;
                        break;
                    case 4:
                        file << "Action: Removed vehicle" << endl;
                        break;
                    case 5:
                        file << "Action: Viewed total revenue" << endl;
                        break;
                    case 6:
                        file << "Action: Logged out" << endl;
                        break;
                    default:
                        file << "Action: Invalid choice" << endl;
                    }

                    file << "-----------------------------" << endl;
                    file.flush();
                    file.close();
                }
                else
                {
                    cerr << "Error opening log file!" << endl;
                }
            }
            else
            {
                cout << "Access denied. Invalid credentials." << endl;
            }
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
int main()
{
    vehicleMenu();

    return 0;
}
