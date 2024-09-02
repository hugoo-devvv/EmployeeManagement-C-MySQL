#include "queries.h"

void handleDatabaseError(MYSQL* connection) {
    fprintf(stderr, "%s\n", mysql_error(connection));
    mysql_close(connection);
    exit(EXIT_FAILURE);
}

MYSQL* createDatabaseConnection(void) {
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

void printTableHeader(const char* columnHeaders[], int columnCount) {
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

void executeAndDisplayQuery(MYSQL* connection, const char* query, const char* columnHeaders[], int columnCount) {
    if (mysql_query(connection, query)) {
        handleDatabaseError(connection);
    }

    MYSQL_RES* result = mysql_store_result(connection);
    if (result == NULL) {
        handleDatabaseError(connection);
    }

    printTableHeader(columnHeaders, columnCount);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printTableRow(row, columnCount);
    }
    printTableBottomLine(columnCount);

    mysql_free_result(result);
}

void showEmployeeList(MYSQL* connection) {
    const char* employeeHeaders[] = {"Id", "Name", "Lastname", "Sex", "Address", "DepartmentId", "Phone", "EntryDate"};
    executeAndDisplayQuery(connection, "SELECT * FROM Employees", employeeHeaders, 8);
}

void showDepartmentList(MYSQL* connection) {
    const char* departmentHeaders[] = {"Id", "Name"};
    executeAndDisplayQuery(connection, "SELECT * FROM Department", departmentHeaders, 2);
}

