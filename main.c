#include "Queries/queries.h"

void displayMenu(){
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

int main(){

    int opt;
    MYSQL* con = createDatabaseConnection();
        
    do{
        displayMenu();
        opt = get_int("Enter your option: ");

        switch(opt){
            case 1:
                showEmployeeList(con);
            break;
            case 2:
                showDepartmentList(con);
            break;
            case 8:
                printf("\nExit program...\n");
                mysql_close(con);
            break;
            default:
                printf("\nPlease enter a valid option, try again.\n");
            break;
        }
       

    }while(opt != 8);

    return 0;

}