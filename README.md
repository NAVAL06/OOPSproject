# OOPSproject
## Project Description

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
