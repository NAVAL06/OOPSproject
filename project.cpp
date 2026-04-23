#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <cstdlib>

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
    double getRentalRate() const { return rentalRate; }
    string getVehicleID() const { return vehicleID; }
    string getModel() const { return model; }
    int getStock() const { return stock; }
};

vector<Vehicle> LoadCarData(bool display = false)
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
        if (display)
        {
            car.displayInfo();
        }
        cars.push_back(car);
    }
    file.close();
    return cars;
}

vector<Vehicle> LoadBikeData(bool display = false)
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
        if (display)
        {
            bike.displayInfo();
        }
        bikes.push_back(bike);
    }
    file.close();
    return bikes;
}

vector<Vehicle> LoadTruckData(bool display = false)
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
        if (display)
        {
            truck.displayInfo();
        }
        trucks.push_back(truck);
    }
    file.close();
    return trucks;
}

void loadingBar()
{
    cout << "[";
    for (int i = 0; i < 20; ++i)
    {
        cout << "#" << flush;
        this_thread::sleep_for(chrono::milliseconds(150));
    }
    cout << "]" << endl;
}

void delay(int dt)
{
    cout << "\n";
    for (int i = 0; i < 20; ++i)
    {
        cout << "." << flush;
        this_thread::sleep_for(chrono::milliseconds(dt));
    }
    cout << "" << endl;
}

void vehicleMenu()
{
    int choice;
    bool running = true;
    while (running)
    {

        cout << "\nWelcome to the Vehicle Rental System!" << endl;
        cout << "-----------------------------" << endl;
        cout << "---Vehicle Management Menu---" << endl;
        cout << "1.Car" << endl;
        cout << "2.Bike" << endl;
        cout << "3.Truck" << endl;
        cout << "4.Return Vehicle" << endl;
        cout << "5.Admin Menu" << endl;
        cout << "------------------------------" << endl
             << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        delay(100);
        switch (choice)
        {
        case 1:

        {
            cout << "Car selected." << endl
                 << endl;
            vector<Vehicle> cars = LoadCarData(true);
            cout << "select a vehicle to rent (enter vehicle ID): ";
            string vehicleID;
            cin >> vehicleID;
            string selectedModel;
            double rentalRate = 0;
            int stock = 0;
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
            if (found && stock > 0)
            {
                cout << "You have selected vehicle : " << vehicleID << " | " << selectedModel << ". Proceeding to rental process..." << endl
                     << endl;
                cout << "Enter rental duration in days: ";
                int days;
                cin >> days;
                double TotalRate = days * rentalRate;
                cout << "Total rental cost: $" << TotalRate << endl
                     << endl;
                cout << "Enter name for the rental agreement: ";
                string renterName;
                cin >> renterName;
                cout << "Enter contact number: ";
                string contactNumber;
                cin >> contactNumber;
                int ticket = rand() % 9000 + 1000;
                cout << "Making A ticket For You ";
                delay(50);
                cout << "Your Ticket No: C" << ticket << endl;

                ofstream file("RentedVehicle.txt", ios::app);
                if (file.is_open())
                {
                    file << "Ticket: " << "C" << ticket << endl;
                    file << "Renter Name: " << renterName << endl;
                    file << "Vehicle ID: " << vehicleID << endl;
                    file << "Contact Number: " << contactNumber << endl;
                    file << "Model: " << selectedModel << endl;
                    file << "Rental Duration (days): " << days << endl;
                    file << "Total Rental Cost: $" << TotalRate << endl;
                    time_t now = time(nullptr);
                    char *dt = ctime(&now);
                    file << "Rental Date: " << dt;
                    file << "-----------------------------" << endl;
                    file.close();
                }

                ofstream updateFile("cars.txt", ios::trunc);
                for (const auto &car : cars)
                {
                    int finalStock = (car.getVehicleID() == vehicleID) ? car.getStock() - 1 : car.getStock();
                    updateFile << car.getVehicleID() << " " << car.getModel() << " " << car.getRentalRate() << " " << finalStock << endl;
                }
                updateFile.close();
            }
            else
            {
                cout << "Vehicle not found or out of stock." << endl;
            }
            break;
        }
        case 2:
        {
            cout << "Bike selected." << endl
                 << endl;
            vector<Vehicle> bikes = LoadBikeData(true);
            cout << "select a vehicle to rent (enter vehicle ID): ";
            string vehicleID;
            cin >> vehicleID;
            string selectedModel;
            double rentalRate = 0;
            int stock = 0;
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
            if (found && stock > 0)
            {
                cout << "You have selected vehicle : " << vehicleID << " | " << selectedModel << ". Proceeding to rental process..." << endl
                     << endl;
                cout << "Enter rental duration in days: ";
                int days;
                cin >> days;
                double TotalRate = days * rentalRate;
                cout << "Total rental cost: $" << TotalRate << endl
                     << endl;
                cout << "Enter name for the rental agreement: ";
                string renterName;
                cin >> renterName;
                cout << "Enter contact number: ";
                string contactNumber;
                cin >> contactNumber;
                int ticket = rand() % 9000 + 1000;
                cout << "Making A ticket For You ";
                delay(50);
                cout << "Your Ticket No: B" << ticket << endl;

                ofstream file("RentedVehicle.txt", ios::app);
                if (file.is_open())
                {
                    file << "Ticket: " << "B" << ticket << endl;
                    file << "Renter Name: " << renterName << endl;
                    file << "Vehicle ID: " << vehicleID << endl;
                    file << "Contact Number: " << contactNumber << endl;
                    file << "Model: " << selectedModel << endl;
                    file << "Rental Duration (days): " << days << endl;
                    file << "Total Rental Cost: $" << TotalRate << endl;
                    time_t now = time(nullptr);
                    char *dt = ctime(&now);
                    file << "Rental Date: " << dt;
                    file << "-----------------------------" << endl;
                    file.close();
                }

                ofstream updateFile("bikes.txt", ios::trunc);
                for (const auto &bike : bikes)
                {
                    int finalStock = (bike.getVehicleID() == vehicleID) ? bike.getStock() - 1 : bike.getStock();
                    updateFile << bike.getVehicleID() << " " << bike.getModel() << " " << bike.getRentalRate() << " " << finalStock << endl;
                }
                updateFile.close();
            }
            break;
        }
        case 3:
        {
            cout << "Truck selected." << endl;
            vector<Vehicle> trucks = LoadTruckData(true);
            cout << "select a vehicle ID: ";
            string vehicleID;
            cin >> vehicleID;
            string selectedModel;
            double rentalRate = 0;
            int stock = 0;
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
            if (found && stock > 0)
            {
                cout << "You have selected vehicle : " << vehicleID << " | " << selectedModel << ". Proceeding to rental process..." << endl
                     << endl;
                cout << "Enter rental duration in days: ";
                int days;
                cin >> days;
                double TotalRate = days * rentalRate;
                cout << "Total rental cost: $" << TotalRate << endl
                     << endl;
                cout << "Enter name for the rental agreement: ";
                string renterName;
                cin >> renterName;
                cout << "Enter contact number: ";
                string contactNumber;
                cin >> contactNumber;
                int ticket = rand() % 9000 + 1000;
                cout << "Making A ticket For You ";
                delay(50);
                cout << "Your Ticket No: T" << ticket << endl;

                ofstream file("RentedVehicle.txt", ios::app);
                if (file.is_open())
                {
                    file << "Ticket: " << "T" << ticket << endl;
                    file << "Renter Name: " << renterName << endl;
                    file << "Vehicle ID: " << vehicleID << endl;
                    file << "Contact Number: " << contactNumber << endl;
                    file << "Model: " << selectedModel << endl;
                    file << "Rental Duration (days): " << days << endl;
                    file << "Total Rental Cost: $" << TotalRate << endl;
                    time_t now = time(nullptr);
                    char *dt = ctime(&now);
                    file << "Rental Date: " << dt;
                    file << "-----------------------------" << endl;
                    file.close();
                }

                ofstream updateFile("trucks.txt", ios::trunc);
                for (const auto &truck : trucks)
                {
                    int finalStock = (truck.getVehicleID() == vehicleID) ? truck.getStock() - 1 : truck.getStock();
                    updateFile << truck.getVehicleID() << " " << truck.getModel() << " " << truck.getRentalRate() << " " << finalStock << endl;
                }
                updateFile.close();
            }
            break;
        }
        case 4:
        {
            cout << "Return Vehicle selected.\nEnter Ticket No: ";
            string ticketNo;
            cin >> ticketNo;
            ifstream rentalFile("RentedVehicle.txt");
            string line;
            string renterName, vehicleID;
            bool found = false;
            while (getline(rentalFile, line))
            {
                if (line.find("Ticket: " + ticketNo) != string::npos)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Ticket not found." << endl;
                break;
            }

            ifstream details("RentedVehicle.txt");
            vector<string> remainingTickets;
            bool skipTicket = false;

            while (getline(details, line))
            {
                if (line.find("Ticket: " + ticketNo) != string::npos)
                {
                    skipTicket = true;
                }

                if (skipTicket)
                {
                    if (line.find("Renter Name: ") != string::npos)
                    {
                        renterName = line.substr(line.find(": ") + 2);
                    }
                    else if (line.find("Vehicle ID: ") != string::npos)
                    {
                        vehicleID = line.substr(line.find(": ") + 2);
                    }
                    if (line.find("-----------------------------") != string::npos)
                    {
                        skipTicket = false;
                    }
                }
                else
                {
                    remainingTickets.push_back(line);
                }
            }
            details.close();
            ofstream rewriteFile("RentedVehicle.txt", ios::trunc);
            for (const string &l : remainingTickets)
            {
                rewriteFile << l << endl;
            }
            rewriteFile.close();
            ofstream returnFile("ReturnedVehicle.txt", ios::app);
            returnFile << "Returned Vehicle ID: " << vehicleID << endl;
            returnFile << "Renter Name: " << renterName << endl;
            time_t now = time(nullptr);
            char *dt = ctime(&now);
            returnFile << "Return Date: " << dt;
            returnFile << "-----------------------------" << endl;
            returnFile.close();
            if (vehicleID.substr(0, 1) == "C")
            {
                vector<Vehicle> cars = LoadCarData(false);
                ofstream file("cars.txt", ios::trunc);
                for (const auto &car : cars)
                {
                    int newStock = (car.getVehicleID() == vehicleID) ? car.getStock() + 1 : car.getStock();
                    file << car.getVehicleID() << " " << car.getModel() << " " << car.getRentalRate() << " " << newStock << endl;
                }
                file.close();
            }
            else if (vehicleID.substr(0, 1) == "B")
            {
                vector<Vehicle> bikes = LoadBikeData(false);
                ofstream file("bikes.txt", ios::trunc);
                for (const auto &bike : bikes)
                {
                    int newStock = (bike.getVehicleID() == vehicleID) ? bike.getStock() + 1 : bike.getStock();
                    file << bike.getVehicleID() << " " << bike.getModel() << " " << bike.getRentalRate() << " " << newStock << endl;
                }
                file.close();
            }
            else if (vehicleID.substr(0, 1) == "T")
            {
                vector<Vehicle> trucks = LoadTruckData(false);
                ofstream file("trucks.txt", ios::trunc);
                for (const auto &truck : trucks)
                {
                    int newStock = (truck.getVehicleID() == vehicleID) ? truck.getStock() + 1 : truck.getStock();
                    file << truck.getVehicleID() << " " << truck.getModel() << " " << truck.getRentalRate() << " " << newStock << endl;
                }
                file.close();
            }
            cout << "ThankYou for returning the vehicle" << renterName << endl;
            break;
        }
        case 5:
        {
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if ((username == "Employee" && password == "12345678") ||
                (username == "Manager" && password == "manager123") ||
                (username == "Nautical" && password == "nautyc06"))
            {
                cout << "Access granted." << endl;
                cout << " 1.Records\n 2.Inventory\n 3.Add\n 4.Remove\n 5.Revenue\n 6.Logout" << endl;
                int AdminChoice;
                cin >> AdminChoice;
                do
                {
                    switch (AdminChoice)
                    {
                    case 1:
                    {
                        ifstream rentalFile("RentedVehicle.txt");
                        string record;
                        while (getline(rentalFile, record))
                            cout << record << endl;
                        rentalFile.close();
                        break;
                    }
                    case 2:
                    {
                        LoadCarData(true);
                        LoadBikeData(true);
                        LoadTruckData(true);
                        break;
                    }
                    case 5:
                    {
                        double totalRevenue = 0;
                        ifstream rentalFile("RentedVehicle.txt");
                        string line;
                        while (getline(rentalFile, line))
                        {
                            if (line.find("Total Rental Cost: $") != string::npos)
                            {
                                totalRevenue += stod(line.substr(line.find("$") + 1));
                            }
                        }
                        std::cout << "Total Revenue: $" << totalRevenue << endl;
                        rentalFile.close();
                        break;
                    }
                    }
                } while (AdminChoice != 6);
                ofstream logFile("admin_log.txt", ios::app);
                if (logFile.is_open())
                {
                    logFile << "Admin: " << username << endl;
                    logFile << "---------" << ctime(nullptr) << "---------" << endl;
                    if (AdminChoice == 1)
                    {
                        logFile << "Viewed the Records" << endl;
                    }
                    else if (AdminChoice == 2)
                    {
                        logFile << "Checked the Inventory" << endl;
                    }
                    else if (AdminChoice == 3)
                    {
                        logFile << "Added a Vehicle" << endl;
                    }
                    else if (AdminChoice == 4)
                    {
                        logFile << "Removed a Vehicle" << endl;
                    }
                    else if (AdminChoice == 5)
                    {
                        logFile << "Checked the Revenue" << endl;
                    }
                    else
                    {
                        logFile << "Logged Out At: " << ctime(nullptr);
                    }
                }
            }
            else
            {
                std::cout << "Access denied." << endl;
            }
            break;
        }
            loadingBar();
            std::cout << "Do you want to continue? (y/n): ";
            char cont;
            std::cin >> cont;
            if (cont == 'n' || cont == 'N')
            {
                running = false;
            }
        }
    }
}

void ThankYouMessage()
{
    delay(100);
    std::cout << "\nThank you for using the Vehicle Rental System!" << endl;
    std::cout << "Have a great day!" << endl;
}

int main()
{
    loadingBar();
    vehicleMenu();
    ThankYouMessage();
    return 0;
}