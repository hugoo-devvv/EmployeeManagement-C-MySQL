#include "utils.h"

string get_string(){
    size_t len = 0;
    string line = NULL;
    getline(&line, &len, stdin);
    return line;
}

string get_email(const char* prompt){
    string email;

    while(1){
        printf("\n%s", prompt);
        email = get_string();
    
        const char* at = strchr(email, '@');
        const char* pe = strchr(email, '.');

        if(at != NULL && pe != NULL){
            return email;
        }

        printf("\nPlease, enter a valid email. Try again.\n");
        free(email);
    }
}

string get_string_validation(const char* prompt){
    char special_characters[] = {'@', '!', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '[', ']', '{', '}', ';', ':', '\'', '\"', ',', '.', '<', '>', '/', '\\', '|', '`', '~'};
    string name;
    int has_especial;

    while(1){
        printf("\n%s", prompt);
        name = get_string();
        has_especial = 0;

        for(int i = 0; name[i] != '\0'; i++){
            for(int j = 0; j < sizeof(special_characters); j++){
                if(name[i] == special_characters[j]){
                    has_especial = 1;
                    break;
                }
            }
        }
        if(!has_especial){
            return name;
        }
        printf("\nThe name must not have special characters. Try again.\n");
        free(name);
    }
}

int get_int(const char* prompt){
    printf("%s", prompt);

    int value;
    while(scanf("%d", &value) != 1){
        while(getchar() != '\n');
        printf("\nPlease, enter a integer value: ");
    }
    return value;
}

float get_float(const char* prompt){
    printf("%s", prompt);

    float value;
    while(scanf("%f", &value) != 1){
        while(getchar() != '\n');
        printf("\nPlease, enter a decimal value: ");
    }
    return value;
}

int validate_date(Date date){
    if(date.year > 2100 || date.year < 1900){return 0;}
    if(date.month > 12 || date.day <= 0){return 0;}
    if(date.day > 31 || date.day <= 0){return 0;}

    return 1;
}

Date get_date(const char* prompt){
    Date date;

    while(1){
        printf("\n%s", prompt);

        if(scanf("%d-%d-%d", &date.year, &date.month, &date.day) == 3){
            if(validate_date(date)){
                break;
            }else{
                printf("\nInvalid date. try again.\n");
            }
        }else{
                printf("\nIncorrect format, use YYYY-MM-DD format.\n");
            while(getchar() != '\n');
        }
    }
    
    return date;
}