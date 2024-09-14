# Employee Management System using C & MySQL

## Overview

The Employee Management System is a C application that provides functionalities for managing employees and departments. It includes:

- Displaying lists of employees or departments.
- Performing advanced searches for employees and departments.
- Counting the number of employees in a specific department.
- Full control over changes in employees or departments, including adding, updating, and deleting records.

## Technical Specifications

### String Data Type

In this project, `string` is defined as:

```c
typedef char* string;

This is essentially a pointer to char, which may be more familiar to C++ or other language users.

   
   ## you will also look an function called clearEntryBuffer
   
  ```c
  void cleanEntryBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
  }```

This function removes the line break that occurs after inputting a string. This is necessary because when the system reads an integer or another data type, it leaves a newline character in the input buffer. This newline character can interfere with subsequent string inputs, preventing them from being read correctly.

**Connection to database**

You might be see in queries.h is an include to **config.g** this file have the mySQL credentials such as password, port, database name, etc.

```c
mysql_real_connect(connection, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0) == NULL)```

In the parameters in the function i added the config.h "#defines" who have all the credentials. You should create an config.h file and make your own defines with you credentials.

   
   ## Database specifications
   
   Like i said before i've been using MySQL database in this proyect. I've using two tables who you should create to use this repository. 
   
  This two tables are:
  - Employees
  - Department
  
  **For the department table desing whe have only id and name**
  ```sql
  CREATE TABLE Department (
    Id INT NOT NULL AUTO_INCREMENT,
    Name VARCHAR(25) NOT NULL,
    PRIMARY KEY (Id)
);```
  
  **For employees table desing we have an forgein key connected in id of department**
  ```sql
CREATE TABLE Employees (
    Id INT NOT NULL AUTO_INCREMENT,
    Name VARCHAR(25) NOT NULL,
    Lastname VARCHAR(30) NOT NULL,
    Sex CHAR(1) NOT NULL,
    Address VARCHAR(255) NOT NULL,
    DepartmentID INT,
    Phone VARCHAR(15),
    EntryDate DATE,
    PRIMARY KEY (Id),
    FOREIGN KEY (DepartmentID) REFERENCES Department(Id)
);```
 