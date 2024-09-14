# EmployeeManagement using C & MySQL

<p>
	A system who give us the posibility of manage and departments who include functionalities such as: 
</p>
- Display list of employees or department
- An advance search for employees and departments
- Counting employees in a determinated department
- Full control of changes in employees or department such as adding, updating, deleting.

## Tecnical specifications

**We are using a string data type**

```c
typedef char* string

<p>  who only is an char pointer, but this might be more undestandable for c++ or another languaje users. In the Utils folder you will found validation functions who are very usefull and make more safest in the database insert or update.</p>

   
   ***you will also look an function called clearEntryBuffer**
   
  ```c
  void cleanEntryBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
  }

This function removes the line break that occurs after inputting a string. This is necessary because when the system reads an integer or another data type, it leaves a newline character in the input buffer. This newline character can interfere with subsequent string inputs, preventing them from being read correctly.

**Connection to database**

You might be see in queries.h is an include to **config.g** this file have the mySQL credentials such as password, port, database name, etc.

```c
mysql_real_connect(connection, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0) == NULL)```

In the parameters in the function i added the config.h #defines who have all the credentials. You should create an config.h file and make your own defines with you credentials.

   
   ## Database specifications
   
   Like i said before i have been using MySQL database in this proyect. I have using two tables who you should create to use this repository. 
   
  This two tables are:
  - Employees
  - Department
  
  **For the department table desing whe have only id and name**
  ```sql
  CREATE TABLE Department (
    Id INT NOT NULL AUTO_INCREMENT,
    Name VARCHAR(25) NOT NULL,
    PRIMARY KEY (Id)
);
  
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
); 