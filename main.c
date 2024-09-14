#include "Queries/queries.h"

int main(){

    int option;
    MYSQL* connection = createDatabaseConnection();
        
    do{
        showMainMenu(&option);
        showMainMenuOptions(connection, option);
    }while(option != 8);

    return 0;

}