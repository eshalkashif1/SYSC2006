/********* main.c ********
    Student Name 	= Eshal Kashif
    Student Number	= 101297950
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"
#include <ctype.h>

#define MAX_CHAR_USER 30
#define MAX_CHAR_PASS 15
#define MIN_MENU_CHOICE 1
#define MAX_MENU_CHOICE 3
#define DISPLAY_POSTS 3
#define MIN_CHAR_PASS 8



int main()
{
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);

    printf("\nWelcome to TextBook - A Text-Based Version of FaceBook!\n");
    char user[MAX_CHAR_USER];
    const char pass[MAX_CHAR_PASS];
    const char new_pass[MAX_CHAR_PASS];
    bool cont = true;

    while(cont){
        print_menu();
        unsigned short int choice = get_menu_choice(MIN_MENU_CHOICE, MAX_MENU_CHOICE);

        switch(choice){
            case 1:
                //Registering user 
                printf("\nEnter a username: ");
                scanf("%s", &user);
                strcpy(user, get_lower(user));
                while(find_user(users, user)!=NULL){
                    printf("\nUser already exists. Try again: ");
                    scanf("%s", &user);
                    strcpy(user, get_lower(user));
                }
                printf("\nEnter a password (15 char max): ");
                scanf("%s", &pass);
                //Dealing with valid passwords
                while(strlen(pass)<MIN_CHAR_PASS){
                  printf("\nPassword must be minimum 8 characters: ");
                  scanf("%s", &pass);
                }
                users = add_user(users, user, pass);
                break;

            case 2:
                printf("\nEnter a username: ");
                scanf("%s", &user);
                strcpy(user, get_lower(user));
                user_t *mainuser=find_user(users, user);
                if(mainuser==NULL){
                    printf("\n----------------------\n User Not Found \n----------------------");
                }else{
                    printf("\nEnter the password: ");
                    scanf("%s", &pass);
                    if(strcmp(pass, mainuser->password)==0){
                        handle_choice_2(mainuser, user, users);
                    }else{
                        printf("\n----------------------\n Incorrect Password \n----------------------");
                    }
                }
                break;

            case 3:
                //Exit
                printf("\nThank you for using TextBook!");
                teardown(users);
                users=NULL;
                cont=false;
                break;
        }
    }
    return EXIT_SUCCESS;
}
