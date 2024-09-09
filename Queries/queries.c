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

void displayEmployeeQueryAndHeader(MYSQL* connection, string query) {
    string* header = employeeHeaders();
    executeAndDisplayQuery(connection, query, header, 8);
}

void displayDepartmentQueryAndHeader(MYSQL* connection, string query) {
    string* header = departmentHeaders();
    executeAndDisplayQuery(connection, query, header, 2);
}

void getQuery(MYSQL* connection, string query) {
    if (mysql_query(connection, query)) {
        handleDatabaseError(connection);
    }
}

void executeAndDisplayQuery(MYSQL* connection, string query, string columnHeaders[], int columnCount) {

    getQuery(connection, query);

    MYSQL_RES* result = mysql_store_result(connection);
    if (result == NULL) {
        handleDatabaseError(connection);
    }

    int num_rows = mysql_num_rows(result);
    if(num_rows == 0) {
        printf("\nNo records found.");
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

void searchById(MYSQL* connection, int id) {
    char query[256];
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
    int id;
    switch (option) {
    case 1:
        id = get_int("\nEnter id: ");
        searchById(connection, id);
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

Employee getEmployeeData (MYSQL* connection) {
    Employee e;

    getchar();
    e.name = get_string_validation("Enter the name: ");
    e.lastname = get_string_validation("Enter the lastname: ");
    e.sex = get_gender("Enter the gender (M / F): ");
    getchar();
    e.address = get_string_validation("Enter the address: ");
    while(1) {
        e.departmentId = get_int("Enter the department id (Enter 0 if you want to see the departments): ");
        if(e.departmentId == 0) {
            showDepartmentList(connection);
        }else {
            break;
        }
    }
    getchar();
    e.phone = get_string_validation("Enter the phone number: ");
    e.entryDate = get_date("Enter the entry date (Format: YYYY-MM-DD): ");

    return e;
}

string getDepartmentData (MYSQL* connection) {
    getchar();
    string name = get_string_validation("Enter the department name: ");

    return name;
}

void insertDepartmentInDatabase (MYSQL* connection) {
    char query[255];
    string name = getDepartmentData(connection);
    snprintf(query, sizeof(query), "INSERT INTO Department (Name) VALUES ('%s')", name);
    getQuery(connection, query);
}

void insertEmployeeInDatabase(MYSQL* connection, Employee e) {
    char query[255];
    snprintf(query, sizeof(query),
             "INSERT INTO Employees (Name, Lastname, Sex, address, DepartamentId, Phone, EntryDate) "
             "VALUES ('%s', '%s', '%c', '%s', %d, %s, '%d-%d-%d');",
             e.name, e.lastname, e.sex, e.address, e.departmentId, e.phone, e.entryDate.year, e.entryDate.month, e.entryDate.day);

    getQuery(connection, query);
}

void addElementOptions(MYSQL* connection) {
    int option = showCrudOptions();
    if(option == 1) {
        Employee newEmployee = getEmployeeData(connection);
        insertEmployeeInDatabase(connection, newEmployee);
    } else if(option == 2) {
        insertDepartmentInDatabase(connection);
    }else {
        printf("\nEnter a valid option.\n");
        return;
    }
}

int searchEmployeeForUpdates(MYSQL* connection) {
    char option;
    while(1) {
        int id = get_int("Enter employeer id: ");
        searchById(connection, id);
        option = get_char("\nThis is the employeer? (Y/N): ");
        if (option == 'Y') {
            return id;
        }
    }
}

void updateEmployeeName(MYSQL* connection, int id) {
    getchar();
    string name = get_string_validation("Enter new name: ");
    char query[256];
    snprintf(query, sizeof(query), "UPDATE Employees SET Name = '%s' WHERE Id = %d", name, id);
    getQuery(connection, query);
    free(name);
}

void updateEmployeeLastname(MYSQL* connection, int id) {
    getchar();
    string lastname = get_string_validation("Enter the new lastname: ");
    char query[256];
    snprintf(query, sizeof(query), "UPDATE Employees SET Lastname = '%s' WHERE Id = %d", lastname, id);
    getQuery(connection, query);
    free(lastname);
}

void updateEmployeeGender(MYSQL* connection, int id) {
    getchar();
    char gender = get_gender("Enter the new gender (M / F): ");
    char query[256];
    snprintf(query, sizeof(query), "UPDATE Employees SET Sex = '%c' WHERE Id = %d", gender, id);
    getQuery(connection, query);
}

void updateEmployeeAddress(MYSQL* connection, int id) {
    getchar();
    string address = get_string_validation("Enter the new address: ");
    char query[256];
    snprintf(query, sizeof(query), "UPDATE Employees SET Address = '%s' WHERE Id = %d", address, id);
    getQuery(connection, query);
    free(address);
}

void updateEmployeeDepartmentId(MYSQL* connection, int id) {
    int departmentId = get_int("Enter the new department id: ");
    char query[256];
    snprintf(query, sizeof(query), "UPDATE Employees SET DepartamentId = %d WHERE Id = %d", departmentId, id);
    getQuery(connection, query);
}

void updateEmployeePhone(MYSQL* connection, int id) {
    int phone = get_int("Enter the new phone: ");
    char query[256];
    snprintf(query, sizeof(query), "UPDATE Employees SET Phone = %d WHERE Id = %d", phone, id);
    getQuery(connection, query);
}

void updateEmployeeEntryDate(MYSQL* connection, int id) {
    Date entryDate = get_date("Enter the new entry date: ");
    char query[256];
    snprintf(query, sizeof(query), "UPDATE Employees SET EntryDate = '%d-%d-%d' WHERE Id = %d", entryDate.year, entryDate.month, entryDate.day, id);
    getQuery(connection, query);
}

void updateEmployeeSwitchOptions(MYSQL* connection) {
    int id = searchEmployeeForUpdates(connection);
    int option = showUpdateOptions();
    switch(option) {
        case 1:
            updateEmployeeName(connection, id);
        break;
        case 2:
            updateEmployeeLastname(connection, id);
        break;
        case 3:
            updateEmployeeGender(connection, id);
        break;
        case 4:
            updateEmployeeAddress(connection, id);
        break;
        case 5:
            updateEmployeeDepartmentId(connection, id);
        break;
        case 6:
            updateEmployeePhone(connection, id);
        break;
        case 7:
            updateEmployeeEntryDate(connection, id);
        break;
        default:
            printf("\nEnter a valid option.\n");
        break;
    }
}

void updateElementOptions(MYSQL* connection) {
    int option = showCrudOptions();
    if(option == 1) {
        updateEmployeeSwitchOptions(connection);
    }

}

/*

    TO-DO  finish update funcions

*/


// To compile gcc -o main Queries/queries.c main.c Utils/utils.c Utils/options.c -lmysqlclient