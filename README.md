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
