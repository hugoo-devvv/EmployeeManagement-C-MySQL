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
MYSQL* createDatabaseConnection(void);
void printTableHeader(const char* columnHeaders[], int columnCount);
void printTableBottomLine(int columnCount);
void printTableRow(MYSQL_ROW row, int columnCount);
void executeAndDisplayQuery(MYSQL* connection, const char* query, const char* columnHeaders[], int columnCount);
void showEmployeeList(MYSQL* connection);
void showDepartmentList(MYSQL* connection);

#endif