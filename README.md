# Employee Management System using C & MySQL

## Overview

The **Employee Management System** is a C application designed to manage employees and departments within an organization. The system provides the following key features:

- Displaying lists of employees or departments.
- Performing advanced searches for employees or departments.
- Counting the number of employees in a specific department.
- Full control over changes in employees and departments, including adding, updating, and deleting records.

## Technical Specifications

### String Data Type

In this project, a custom string data type is defined to simplify the handling of character arrays. This helps make the code easier to understand for users familiar with other programming languages, such as C++.

### Input Handling

The system includes a function to clear the input buffer, which is necessary to prevent errors when reading user input. This is particularly useful when switching between different types of input (e.g., from integers to strings), as leftover newline characters can interfere with subsequent inputs.

### Database Connection

The application connects to a MySQL database using credentials that are stored in a configuration file. This file contains details such as the database host, username, password, database name, and port. Users must create their own configuration file and input their MySQL credentials to establish a connection to the database.

## Database Specifications

The system relies on two MySQL tables: **Department** and **Employees**.

- The **Department** table contains the department's unique ID and name.
- The **Employees** table stores employee details such as name, last name, sex, address, department ID (as a foreign key), phone number, and entry date.

## Setup Instructions

1. **Clone the Repository**: Clone the project repository to your local machine.
   
2. **Create the Database**: Set up the required MySQL tables (`Department` and `Employees`) using the provided SQL scripts.

3. **Configure Database Credentials**: Create a configuration file with your MySQL credentials, which will be used to connect to the database.

4. **Compile and Run**: Compile the application using a C compiler and ensure you have the MySQL client libraries installed.

## Usage

After setting up the database and configuring the application, you can perform the following actions within the system:

- View a list of all employees or departments.
- Search for specific employees or departments based on various criteria.
- Count the number of employees in a particular department.
- Add new employees or departments, update existing records, or delete entries.

