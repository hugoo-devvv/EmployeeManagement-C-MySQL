#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <mysql/mysql.h>

typedef char* string;

typedef struct { // YYYY-MM-DD Format
    int year;
    int month;
    int day;
}Date;

void cleanEntryBuffer();
string get_string();
string get_email(const char* prompt);
string get_string_validation(const char* prompt);
int get_int(const char* prompt);
float get_float(const char* prompt);
char get_char(const char* prompt);
char get_gender(const char* prompt);
int validate_date(Date date);
Date get_date(const char* prompt);


#endif