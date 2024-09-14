#ifndef QUERIES_H
#define QUERIES_H

    #include "../Utils/config.h" // MySQL credentials
    #include "../Utils/utils.h"

typedef struct {

    string name;
    string lastname;
    char sex;
    string address;
    int departmentId;
    string phone;
    Date entryDate;

}Employee;

void handleDatabaseError(MYSQL* connection);
MYSQL* createDatabaseConnection();
void printTableHeader(string columnHeaders[], int columnCount);
void printTableBottomLine(int columnCount);
void printTableRow(MYSQL_ROW row, int columnCount);
void displayEmployeeQueryAndHeader(MYSQL* connection, string query);
void displayDepartmentQueryAndHeader(MYSQL* connection, string query);
void getQuery(MYSQL* connection, string query);
void executeAndDisplayQuery(MYSQL* connection, string query, string columnHeaders[], int columnCount);
string* employeeHeaders();
string* departmentHeaders();
void showEmployeeList(MYSQL* connection);
void showDepartmentList(MYSQL* connection);
void searchById(MYSQL* connection, int id);
void searchByName(MYSQL* connection);
int searchByDepartmentOptions(MYSQL* connection);
void searchByDepartment(MYSQL* connection);
char searchByGenderOptions();
void searchByGender(MYSQL* connection);
void searchOptions(MYSQL* connection);
void countEmployeesInDepartment(MYSQL* connection);
Employee getEmployeeData(MYSQL* connection);
string getDepartmentData(MYSQL* connection);
void insertDepartmentInDatabase(MYSQL* connection);
void insertEmployeeInDatabase(MYSQL* connection, Employee e);
void addElementOptions(MYSQL* connection);
int searchEmployeeForUpdates(MYSQL* connection);
void updateEmployeeName(MYSQL* connection, int id);
void updateEmployeeLastname(MYSQL* connection, int id);
void updateEmployeeGender(MYSQL* connection, int id);
void updateEmployeeAddress(MYSQL* connection, int id);
void updateEmployeeDepartmentId(MYSQL* connection, int id);
void updateEmployeePhone(MYSQL* connection, int id);
void updateEmployeeEntryDate(MYSQL* connection, int id);
int searchDepartmentListForUpdates(MYSQL* connection);
void updateDepartmentName(MYSQL* connection, int id);
void updateElementOptions(MYSQL* connection);
void deleteEmployeeFromDatabase(MYSQL* connection);
void deleteDepartmentFromDatabase(MYSQL* connection);
void deleteElementsOptions(MYSQL* connection);
void showSearchOptions(int* option);
void showMainMenu(int* option);
void showSearchByGenderMenu(char* option);
void showCrudOptions(int* option);
void showUpdateOptions(int* option);
void searchOptionsCase(int option, MYSQL* connection);
void updateEmployeeSwitchOptions(MYSQL* connection);
void showMainOptions(MYSQL* connection, int option);


#endif