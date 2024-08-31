#include "queries.h"

void finish_with_error(MYSQL* con){
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

MYSQL* connection(){

    MYSQL* con = mysql_init(NULL);
    if(!con){
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }

    if(!mysql_real_connect(con, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0)){
        finish_with_error(con);
    }

    return con;

}

void printEmployeeHeader(){
    printf("\n");
    printf("+----+--------+----------+-----+--------------------------+---------------+---------+------------+\n");
    printf("| Id | Name   | Lastname | Sex | Address                  | DepartamentId | Phone   | EntryDate  |\n");
    printf("+----+--------+----------+-----+--------------------------+---------------+---------+------------+\n");
}

void printBottomLine(){
    printf("+----+--------+----------+-----+--------------------------+---------------+---------+------------+\n");
}

void printRow(MYSQL_ROW row) {
    printf("| %-2s | %-6s | %-8s | %-4c | %-24s | %-13s | %-7s | %-10s |\n",
           row[0] ? row[0] : "NULL",
           row[1] ? row[1] : "NULL",
           row[2] ? row[2] : "NULL",
           row[3] ? row[3][0] : 'N',
           row[4] ? row[4] : "NULL",
           row[5] ? row[5] : "NULL",
           row[6] ? row[6] : "NULL",
           row[7] ? row[7] : "NULL");
}

void printList(MYSQL_RES* result){

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while((row = mysql_fetch_row(result))){
        printRow(row);
    }
    mysql_free_result(result);
}

void displayFullList(MYSQL* con){
    if(mysql_query(con, "SELECT * FROM Employees")){
        finish_with_error(con);
    }

    MYSQL_RES* result = mysql_store_result(con);
    if(!result){
        finish_with_error(con);
    }

    printEmployeeHeader();
    printList(result);
    printBottomLine();
}
