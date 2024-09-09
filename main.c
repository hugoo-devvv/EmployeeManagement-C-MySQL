#include "Queries/queries.h"

int main(){

    int option;
    MYSQL* con = createDatabaseConnection();
        
    do{
        showMainMenu();
        option = get_int("Enter your option: ");

        switch(option){
            case 1:
                showEmployeeList(con);
            break;
            case 2:
                showDepartmentList(con);
            break;
            case 3:
                searchOptions(con);
            break;
            case 4:
                countEmployeesInDepartment(con);
            break;
            case 5:
                addElementOptions(con);
            break;
            case 6:
                updateElementOptions(con);
            break;
            case 7:
                deleteElementsOptions(con);
            break;
            case 8:
                printf("\nExit program...\n");
                mysql_close(con);
            break;
            default:
                printf("\nPlease enter a valid option, try again.\n");
            break;
        }
       

    }while(option != 8);

    return 0;

}