// Vehicle Rental System

/* This program simulates a vehicle rental system where users can rent cars, bikes, and trucks.
 It includes features for managing inventory, processing rentals and returns, and an admin menu for managing records and revenue.*/

// Include necessary libraries
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <windows.h>

using namespace std;
// Function to set text color in the console
void TextColour(int colour){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}

// Helper function to print text with a typing effect
void typeText(const string& text, int delayMs = 30)
{
    for (char c : text)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
    cout << endl;
}

// Vehicle class
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

// Car class
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

// Bike class
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

// Truck class
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

// Show cursor function
void showCursor(bool show) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = show;
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Loading Bar function
void loadingBar(int x,int y)
{ 
    showCursor(false);
    for (int i = 0; i <=100; i++){
        std::cout << "\r";
        
        int progress = i/x;
        for (int j = 0; j < y; ++j){
            if (j < progress) cout << "█";
            else cout << "▒";
        }
        std::cout <<  "" << i << "%" << flush; 
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    std::cout << endl;
    showCursor(true);
}

// Delay function for simulating processing time without output
void delayBlank(int dt)
{
    this_thread::sleep_for(chrono::milliseconds(dt));
}

// Delay function for simulating processing time
void delay(int dt)
{
    showCursor(false);
    cout << "";
    for (int i = 0; i < 20; ++i)
    {
        cout << "." << flush;
        this_thread::sleep_for(chrono::milliseconds(dt));
    }
    cout << "" << endl;
    showCursor(true);
}

// Main menu function
void vehicleMenu()
{
    int choice;
    bool running = true;
    while (running)
    {

        typeText("\nWelcome to the Vehicle Rental System!");
        delayBlank(100);
        typeText("-----------------------------\n");
        cout << "---Vehicle Management Menu---" << endl;
        cout << "1.Car" << endl;
        cout << "2.Bike" << endl;
        cout << "3.Truck" << endl;
        cout << "4.Return Vehicle" << endl;
        cout << "5.Admin Menu" << endl;
        typeText("------------------------------\n");
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        delayBlank(100);
        switch (choice)
        {
        case 1:// Car Rental Process

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
                cout << "\nYou have selected vehicle : " << vehicleID << " | " << selectedModel << ". Proceeding to rental process..." << endl
                     << endl;
                delayBlank(100);
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
                delayBlank(300);
                cout << "Your Ticket No: C" ;
                TextColour(12);
                cout<< ticket << endl;
                TextColour(7);
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
            loadingBar (10,10);
            cout << endl;
            break;
        }
        case 2:// Bike Rental Process
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
                delayBlank(300);
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
            else
            {
                cout << "Vehicle not found or out of stock." << endl;
            }
            loadingBar (10,10);
            cout << endl;
            break;
        }
        case 3:// Truck Rental Process
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
                delayBlank(300);
                TextColour(12);
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
            else
            {
                cout << "Vehicle not found or out of stock." << endl;
            }
            loadingBar (10,10);
            cout << endl;
            break;
        }
        case 4:// Return Vehicle Process
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
            TextColour(10);
            cout << "ThankYou for returning the vehicle" << renterName << endl;
            TextColour(7);
            loadingBar (10,10);
            cout << endl;
            break;
        }
        case 5:// Admin Menu
        {
            TextColour(10);
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            TextColour(7);

            if ((username == "Employee" && password == "12345678") ||
                (username == "Manager" && password == "manager123") ||
                (username == "Nautical" && password == "nautyc06"))
            {
                TextColour(10);
                cout << "Verifying credentials" << endl;
                delayBlank(500);
                cout << "Access granted." << endl;
                bool adminRunning = true;

                while (adminRunning)
                {
                    TextColour(10);
                    cout << " 1.Records\n 2.Inventory\n 3.Add\n 4.Remove\n 5.Revenue\n 6.Logout" << endl;
                    int AdminChoice;
                    cin >> AdminChoice;

                ofstream logFile;
                logFile.open("admin_log.txt", ios::app);
                logFile << "Admin: " << username << endl;
                time_t now = time(nullptr);
                logFile << "Logged in at: " << ctime(&now) << endl;
                    switch (AdminChoice)
                    {
                    case 1:// View Records
                    {
                        ifstream rentalFile("RentedVehicle.txt");
                        string record;
                        while (getline(rentalFile, record))
                            cout << record << endl;
                        rentalFile.close();
                        logFile << "Viewed the Records" << endl;
                        cout << "Do You want to go back? (y/n): ";
                        char cont;
                        cin >> cont;
                        if (cont == 'n' || cont == 'N') {
                            adminRunning = false;
                            cout << "Going back to admin menu..." << endl;
                            delay (50);
                        }
                        break;
                    }
                    case 2:// Check Inventory
                    {
                        LoadCarData(true);
                        LoadBikeData(true);
                        LoadTruckData(true);
                        logFile << "Checked the Inventory" << endl;
                        cout << "Do You want to go back? (y/n): ";
                        char cont;
                        cin >> cont;
                        if (cont == 'n' || cont == 'N') {
                            adminRunning = false;
                            cout << "Going back to admin menu..." << endl;
                            delay (50);
                        }
                        break;
                    }
                    case 3:// Add Vehicle
                    {
                        string type, id, model;
                        double rate;
                        int stock;
                        cout << "Enter vehicle type (Car/Bike/Truck): ";
                        cin >> type;
                        cout << "Enter vehicle ID: ";
                        cin >> id;
                        cout << "Enter model: ";
                        cin >> model;
                        cout << "Enter rental rate: ";
                        cin >> rate;
                        cout << "Enter stock: ";
                        cin >> stock;

                        ofstream file(type + "s.txt", ios::app);
                        if (file.is_open())
                        {
                            file << id << " " << model << " " << rate << " " << stock << endl;
                            file.close();
                            cout << "Vehicle added successfully." << endl;
                        }
                        else
                        {
                            cout << "Error opening file!" << endl;
                        }
                        logFile << "Added a Vehicle" << endl;
                        cout << "Do You want to go back? (y/n): ";
                        char cont;
                        cin >> cont;
                        if (cont == 'n' || cont == 'N') {
                            adminRunning = false;
                            cout << "Going back to admin menu..." << endl;
                            delay (50);
                        }
                        break;
                        
                    }
                    case 4:// Remove Vehicle
                    {
                        string type, id;
                        cout << "Enter vehicle type (Car/Bike/Truck): ";
                        cin >> type;
                        cout << "Enter vehicle ID to remove: ";
                        cin >> id;
                        string filename = type + "s.txt";
                        ifstream file(filename);
                        vector<string> lines;
                        string line;
                        while (getline(file, line))
                        {
                            if (line.find(id) == string::npos)
                            {
                                lines.push_back(line);
                            }
                        }
                        file.close();
                        ofstream outFile(filename, ios::trunc);
                        for (const string &l : lines)
                        {
                            outFile << l << endl;
                        }
                        outFile.close();
                        cout << "Vehicle removed successfully." << endl;
                        logFile << "Removed Vehicle" << id << endl;
                        cout << "Do You want to go back? (y/n): ";
                        char cont;
                        cin >> cont;
                        if (cont == 'n' || cont == 'N') {
                            adminRunning = false;
                            cout << "Going back to admin menu..." << endl;
                            delay (50);
                        }
                        break;

                    }
                    case 5:// Check Revenue
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
                        logFile << "Checked the Revenue" << endl;
                        cout << "Do You want to go back? (y/n): ";
                        char cont;
                        cin >> cont;
                        if (cont == 'n' || cont == 'N') {
                            adminRunning = false;
                            delay (50);
                        }
                        else {
                            cout << "Going back to admin menu..." << endl;
                            delay (50);
                        }
                        break;
                    }
                    case 6:// Logout
                    {
                        cout << "Logging out...";
                        delay(50);
                        logFile << "Logged out" << endl;
                        logFile << "-----------------------------" << endl;
                        adminRunning = false;
                        break;
                    }
                    default:
                    {
                        cout << "Invalid choice." << endl;
                        adminRunning = false;
                        break;
                    }
                    }
                    logFile.close();
                    TextColour(7);
                }
            }
            else
            {
                TextColour(12);
                cout << "Invalid credentials." << endl;
                std::cout << "Access denied." << endl;
                TextColour(7);
            }
            break;
        }
        default:
        {
            cout << "Invalid choice." << endl;
            break;
        }
        } // End of switch statement
        TextColour(10);
        std::cout << "Do you want to Go Back To Main Menu? (y/n): ";
        TextColour(7);
        char back;
        std::cin >> back;
        if (back != 'y' && back != 'Y')
        {
            running = false;
        }
    }
}// End of vehicleMenu function

// Thank you message function
void ThankYouMessage()
{
    delay(100);
    cout << "\n";
    typeText("Thank you for using the Vehicle Rental System!");
    typeText("Have a great day!");
    delay(100);
    typeText("Goodbye!");
    delay(100);
}

// Main function
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    loadingBar(5,20);
    vehicleMenu();
    ThankYouMessage();
    return 0;
}