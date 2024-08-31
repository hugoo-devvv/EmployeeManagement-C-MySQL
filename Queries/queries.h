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

void finish_with_error(MYSQL* con);
MYSQL* connection(void);
void printEmployeeHeader(void);
void printBottomLine(void);
void printRow(MYSQL_ROW row);
void printList(MYSQL_RES* result);
void displayFullList(MYSQL* con);

#endif