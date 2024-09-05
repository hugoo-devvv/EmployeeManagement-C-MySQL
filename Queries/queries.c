#include "queries.h"

void handleDatabaseError(MYSQL* connection) {
    fprintf(stderr, "%s\n", mysql_error(connection));
    mysql_close(connection);
    exit(EXIT_FAILURE);
}

MYSQL* createDatabaseConnection() {
    MYSQL* connection = mysql_init(NULL);
    if (connection == NULL) {
        fprintf(stderr, "%s\n", mysql_error(connection));
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(connection, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0) == NULL) {
        handleDatabaseError(connection);
    }

    return connection;
}

void printTableHeader(string columnHeaders[], int columnCount) {
    printf("\n");
    printf("+");
    for (int i = 0; i < columnCount; i++) {
        printf("%-*s+", 16, "----------------");
    }
    printf("\n|");
    for (int i = 0; i < columnCount; i++) {
        printf(" %-*s|", 15, columnHeaders[i]);
    }
    printf("\n+");
    for (int i = 0; i < columnCount; i++) {
        printf("%-*s+", 15, "----------------");
    }
    printf("\n");
}

void printTableBottomLine(int columnCount) {
    printf("+");
    for (int i = 0; i < columnCount; i++) {
        printf("%-*s+", 15, "----------------");
    }
    printf("\n");
}

void printTableRow(MYSQL_ROW row, int columnCount) {
    printf("|");
    for (int i = 0; i < columnCount; i++) {
        printf("%-*s |", 15, row[i] ? row[i] : "NULL");
    }
    printf("\n");
}

void getQuery(MYSQL* connection, string query) {
    if (mysql_query(connection, query)) {
        handleDatabaseError(connection);
    }
}

void displayEmployeeQueryAndHeader(MYSQL* connection, string query) {
    string* header = employeeHeaders();
    executeAndDisplayQuery(connection, query, header, 8);
}

void displayDepartmentQueryAndHeader(MYSQL* connection, string query) {
    string* header = departmentHeaders();
    executeAndDisplayQuery(connection, query, header, 2);
}

void executeAndDisplayQuery(MYSQL* connection, string query, string columnHeaders[], int columnCount) {

    getQuery(connection, query);

    MYSQL_RES* result = mysql_store_result(connection);
    if (result == NULL) {
        handleDatabaseError(connection);
    }

    int num_rows = mysql_num_rows(result);
    if(num_rows == 0) {
        printf("\nNo records found.\n");
        mysql_free_result(result);
        return;
    }

    printTableHeader(columnHeaders, columnCount);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printTableRow(row, columnCount);
    }
    printTableBottomLine(columnCount);

    mysql_free_result(result);
}

string* employeeHeaders() {
    static string headers[] = {"Id", "Name", "Lastname", "Sex", "Address", "DepartmentId", "Phone", "EntryDate"};
    return headers;
}

string* departmentHeaders() {
    static string headers[] = {"Id", "Name"};
    return headers;
}

void showEmployeeList(MYSQL* connection) {
    string* header = employeeHeaders();
    executeAndDisplayQuery(connection, "SELECT * FROM Employees", header, 8);
}

void showDepartmentList(MYSQL* connection) {
    string* header = departmentHeaders();
    executeAndDisplayQuery(connection, "SELECT * FROM Department", header, 2);
}

void searchById(MYSQL* connection) {
    char query[256];
    int id = get_int("Enter the id: ");
    snprintf(query,sizeof(query),"SELECT * FROM Employees WHERE Id = %d", id);
    displayEmployeeQueryAndHeader(connection, query);
}

void searchByName(MYSQL* connection) {
    char query[256];
    getchar();
    string name = get_string_validation("Enter the name: ");
    snprintf(query,sizeof(query),"SELECT * FROM Employees WHERE Name = '%s'", name);
    free(name);
    displayEmployeeQueryAndHeader(connection, query);
}

int searchByDepartmentOptions(MYSQL* connection) {
    showDepartmentList(connection);
    while(1){
        int option = get_int("Choose the department: ");
        if(option != 0 && option > 0) {return option;}
        printf("\nPlease, enter a valid id.\n");
    }
}

void searchByDepartment(MYSQL* connection) {
    int id = searchByDepartmentOptions(connection);

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM Employees WHERE DepartamentID = %d", id);
    displayEmployeeQueryAndHeader(connection, query);
}

char searchByGenderOptions() {
    showSearchByGenderMenu(); 
    while(1){
        char option = get_char("Enter your option: ");
        if(option == 'M' || option == 'F') {return option;}
        printf("\nPlease enter a valid sex.\n");
    }
}

void searchByGender(MYSQL* connection) {
    char gender = searchByGenderOptions(connection);

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM Employees WHERE Sex = '%c'", gender); 
    displayEmployeeQueryAndHeader(connection, query);  
}

void searchOptionsCase(int option, MYSQL* connection) {
    switch (option) {
    case 1:
        searchById(connection);
        break;
    case 2:
        searchByName(connection);
        break;
    case 3:
        searchByDepartment(connection);
        break;
    case 4:
        searchByGender(connection);
        break;
    default:
        printf("\nPlease, enter a valid option.\n");
        break;
    }
}

void searchOptions(MYSQL* connection) {
    showSearchOptions();
    int option = get_int("\nEnter your option: ");
    searchOptionsCase(option, connection);
}

void countEmployeesInDepartment(MYSQL* connection) {
    int id = searchByDepartmentOptions(connection);

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) AS TOTAL FROM Employees WHERE DepartamentID = %d", id);
    string header[] = {"TOTAL"};
    executeAndDisplayQuery(connection, query, header, 1);
}

void addEmployee(MYSQL* connection) {
    getchar();
    string name = get_string_validation("Enter the name: ");
    string lastname = get_string_validation("Enter the lastname: ");
    char sex = get_char("Enter the gender (M or F): ");
    getchar();
    string address = get_string_validation("Enter the address: ");
    int departmentId;
    while(1) {
        departmentId = get_int("Enter the department id (Enter 0 if you want to see the departments): ");
        if(departmentId == 0) {showDepartmentList(connection);} else {break;}
    }
    int phone = get_int("Enter the phone number: ");
    Date entryDate = get_date("Enter the entry date (Format YYYY-MM-DD): "); 

    char query[256];

    snprintf(query, sizeof(query),
        "INSERT INTO Employees (Name, Lastname, Sex, Address, departamentId, Phone, EntryDate) "
        "VALUES ('%s', '%s', '%c', '%s', %d, %d, '%d-%d-%d')", name, lastname, sex, address, departmentId, phone, entryDate.year, entryDate.month, entryDate.day);

    getQuery(connection, query);
}

void addElementOptions(MYSQL* connection) {
    showCrudOptions();
    int option = get_int("Enter your option: ");
    if(option == 1) {
        addEmployee(connection);
    }
}
