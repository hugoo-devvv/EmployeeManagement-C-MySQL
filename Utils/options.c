#include "utils.h"

void showSearchOptions(){
    printf("\n1.- Search by id");
    printf("\n2.- Search by name");
    printf("\n3.- Search by department");
    printf("\n4.- Search by gender");
}

void showMainMenu(){
    printf("\nEMPLOYEE MANAGEMENT\n\n");
    printf("1. - Display employee list\n");
    printf("2. - Display department list\n");
    printf("3. - Search for an employee\n");
    printf("4. - Count employees by department\n"); 
    printf("5. - Add employee or department\n");
    printf("6. - Update employee or department\n");
    printf("7. - Delete employee or department\n");
    printf("8. - Exit\n");
}

void showSearchByGenderMenu() {
    printf("1.- MALE (M)\n2.- FEMALE (F)");
}

