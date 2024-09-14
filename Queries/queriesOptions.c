#include "queries.h"

void showSearchOptions(int* option){
    printf("\n1.- Search by id");
    printf("\n2.- Search by name");
    printf("\n3.- Search by department");
    printf("\n4.- Search by gender");
    *option = get_int("Enter option: ");
}

void showMainMenu(int* option){
    printf("\n\nEMPLOYEE MANAGEMENT\n\n");
    printf("1. - Display employee list\n");
    printf("2. - Display department list\n");
    printf("3. - Search for an employee\n");
    printf("4. - Count employees by department\n"); 
    printf("5. - Add employee or department\n");
    printf("6. - Update employee or department\n");
    printf("7. - Delete employee or department\n");
    printf("8. - Exit\n");
    *option = get_int("Enter option: ");
}

void showSearchByGenderMenu(char* option) {
    printf("- MALE (M)\n- FEMALE (F)");
    *option = get_gender("Enter option: ");
}

void showCrudOptions(int* option){
    printf("\nSELECT WICH OPTION YOU WISH TO MODIFY\n");
    printf("\n1.- Employee");
    printf("\n2.- Department");
    *option = get_int("Enter option: ");
}

void showUpdateOptions(int* option) {
    printf("\nSELECT WICH OPTION YOU WISH TO UPDATE\n");
    printf("\n1 .- Name");
    printf("\n2 .- Lastname");
    printf("\n3 .- Sex");
    printf("\n4 .- Address");
    printf("\n5 .- Department ID");
    printf("\n6 .- Phone");
    printf("\n7 .- Entry Date");
    *option = get_int("Enter option: ");
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

void updateEmployeeSwitchOptions(MYSQL* connection) {
    int id = searchEmployeeForUpdates(connection);
    int option;
    showUpdateOptions(&option);
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
    int id, option;
    showCrudOptions(&option);
    switch(option) {
        case 1:
            updateEmployeeSwitchOptions(connection);
        break;
        case 2:
            id = searchDepartmentListForUpdates(connection);
            updateDepartmentName(connection, id);
        break;
        default:
            printf("\nEnter a valid option.");
        break;
    }
}

void deleteElementsOptions(MYSQL* connection) {
    int option;
    showCrudOptions(&option);
    
    switch(option) {
        case 1:
            deleteEmployeeFromDatabase(connection);
            break;
        case 2:
            deleteDepartmentFromDatabase(connection);
            break;
        default:
            printf("\nEnter a valid option.");
            break;
    }
}

void showMainOptions(MYSQL* connection, int option) {
    switch(option){
            case 1:
                showEmployeeList(connection);
            break;
            case 2:
                showDepartmentList(connection);
            break;
            case 3:
                searchOptions(connection);
            break;
            case 4:
                countEmployeesInDepartment(connection);
            break;
            case 5:
                addElementOptions(connection);
            break;
            case 6:
                updateElementOptions(connection);
            break;
            case 7:
                deleteElementsOptions(connection);
            break;
            case 8:
                printf("\nLeaving program...\n");
                mysql_close(connection);
            break;
            default:
                printf("\nPlease enter a valid option, try again.\n");
            break;
        }
}