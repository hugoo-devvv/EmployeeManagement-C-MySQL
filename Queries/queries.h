#ifndef QUERIES_H
#define QUERIES_H

    #include "../Utils/config.h"
    #include "../Utils/utils.h"
    #include <mysql/mysql.h>

typedef struct {

    string name;
    string lastname;
    char sex;
    string address;
    int departamentId;
    int phone;
    Date entryDate;

}Employee;

void handleDatabaseError(MYSQL* connection);
MYSQL* createDatabaseConnection();
void printTableHeader(string columnHeaders[], int columnCount);
void printTableBottomLine(int columnCount);
void printTableRow(MYSQL_ROW row, int columnCount);
void executeAndDisplayQuery(MYSQL* connection, string query, string columnHeaders[], int columnCount);
string* employeeHeaders();
string* departmentHeaders();
void showEmployeeList(MYSQL* connection);
void showDepartmentList(MYSQL* connection);
void searchByName(MYSQL* connection);
void searchOptionsCase(int option, MYSQL* connection);
void searchOptions(MYSQL* connection);
void searchByDepartment(MYSQL* connection);
int searchByDepartmentOptions(MYSQL* connection);
void countEmployeesInDepartment(MYSQL* connection);
void addElementOptions(MYSQL* connection);
void addEmployee(MYSQL* connection);

#endif