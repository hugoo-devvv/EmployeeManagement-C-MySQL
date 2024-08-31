#include "Queries/queries.h"

void displayMenu(){
    printf("\nEMPLOYEE MANAGEMENT\n");
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
    MYSQL* con = connection();
        
    do{
        displayMenu();
        opt = get_int("Enter your option (1-7): ");

        switch(opt){
            case 1:
                displayFullList(con);
            break;
            case 8:
                printf("\nExit program...\n");
            break;
            default:
                printf("\nPlease enter a valid option, try again.\n");
            break;
        }
       

    }while(opt != 8);


}