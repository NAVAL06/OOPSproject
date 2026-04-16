# OOPSproject
## Project Description

Vehicle Rental Management System (v2.0)
Project Overview
The Vehicle Rental Management System is a terminal-based C++ application designed to manage the lifecycle of vehicle rentals. The system provides a dual-interface approach: a customer-facing portal for renting and returning vehicles, and an administrative dashboard for inventory control, financial auditing, and security logging.

Core Features
1. Customer Operations
Automated Inventory Check: Validates stock levels before permitting a rental transaction.

Cost Calculation: Automatically computes total rental fees based on duration and model rates.

Return Processing: Integrated logic to restock vehicles into the database upon return.

Transaction Records: Generates detailed rental agreements in RentedVehicle.txt including renter metadata and timestamps.

2. Administrative Suite
Full CRUD Functionality: Admins can add new vehicles or remove existing stock directly through the interface.

Financial Reporting: Parses rental logs to calculate and display total revenue.

Inventory Monitoring: Real-time viewing of fleet status for all categories (Cars, Bikes, Trucks).

Audit Trail: Logs specific admin actions (logins, inventory changes, revenue checks) to admin_log.txt.

Technical Improvements in Version 2.0
Flow Control: Replaced legacy "goto" statements with structured "while" loops and boolean flags to ensure clean program termination and scope management.

Input Validation: Implemented stream error handling using cin.clear() and cin.ignore() to prevent system crashes and infinite loops caused by invalid data types.

Data Persistence: Utilizes fstream for flat-file database management, employing ios::trunc for inventory updates and ios::app for historical logging.

Object-Oriented Design: Features a Vehicle base class with protected members and public accessors to maintain data encapsulation.

System Architecture
File Requirements
The following flat-file databases must be present in the execution directory:

cars.txt / bikes.txt / trucks.txt: Primary inventory files using the format: [VehicleID] [Model] [Rate] [Stock].

RentedVehicle.txt: Log of all completed rental transactions.

admin_log.txt: Security log for administrative sessions.

Technical Specifications
Language: C++

Standard: C++11 or higher

Libraries: iostream, string, vector, fstream, sstream, ctime

Compilation and Execution
Compile the source code using a standard C++ compiler:

```bash
g++ main.cpp -o RentalSystem
Run the executable:

Bash
./RentalSystem
=======
# Vehicle Rental System

A C++ based console application designed to manage the rental process for different types of vehicles including cars, bikes, and trucks. The system handles real-time stock updates, rental cost calculation, and administrative logging through file-based data persistence.

## Features

* **Vehicle Management**: Specialized loading functions for Cars, Bikes, and Trucks from external data files.
* **Automated Calculations**: Computes total rental costs based on the model's specific daily rate and the requested duration.
* **Inventory Tracking**: Automatically decrements stock levels in the source files (`cars.txt`, `bikes.txt`, etc.) upon a successful transaction.
* **Rental Agreements**: Generates a `RentedVehicle.txt` log containing the renter's name, contact information, and specific vehicle details.
* **Admin Authentication**: Multi-user login system for Employees and Managers with specific credential validation.
* **Security Logging**: Tracks every successful admin login with a precise timestamp in `admin_log.txt`.

## Technical Implementation

* **Language**: C++
* **File Handling**: Utilizes `ifstream` for data retrieval and `ofstream` with `ios::app` and `ios::trunc` modes for record keeping and stock updates.
* **Data Parsing**: Employs `stringstream` to parse space-separated values from flat-file databases.
* **Time Library**: Uses `<ctime>` to fetch and format system time for administrative auditing.
* **Object-Oriented Structure**: Features a `Vehicle` base class to encapsulate ID, model, rate, and stock data.

## File Requirements

For the program to initialize correctly, the following files should be present in the root directory:

1. **cars.txt** / **bikes.txt** / **trucks.txt**: Used for inventory.
   * Format: `[ID] [Model] [Rate] [Stock]`
2. **RentedVehicle.txt**: Automatically created to store rental agreements.
3. **admin_log.txt**: Automatically created to log admin access.

## Compilation and Usage

To compile the system using a standard C++ compiler (such as g++):

```bash
g++ main.cpp -o RentalSystem
./RentalSystem
```

---
>>>>>>> 0d204be476483369057cd4bf8e54ab1d653a04e2
