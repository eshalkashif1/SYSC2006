/********* main.c ********
    Student Name 	= Eshal Kashif
    Student Number	= 101297970
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

#define MAX_CHAR_USER 30
#define MAX_CHAR_PASS 15
#define MIN_MENU_CHOICE 1
#define MAX_MENU_CHOICE 6
#define DISPLAY_POSTS 3

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
    const char user[MAX_CHAR_USER];
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
                printf("\nEnter a password (15 char max): ");
                scanf("%s", &pass);
                users = add_user(users, user, pass);
                break;

            case 2:
                //Change password 
                printf("\nEnter a username to update password: ");
                scanf("%s", &user);
                user_t *finding_user = find_user(users, user);
                if(finding_user!=NULL){
                    printf("\nEnter the password: ");
                    scanf("%s", &pass);
                    if(strcmp(pass, finding_user->password)==0){
                        printf("\nEnter a new password (15 char max): ");
                        scanf("%s", &new_pass);
                        strcpy(finding_user->password, new_pass);
                    }
                    else {
                        printf("\n----------------------\n Incorrect Password \n----------------------");
                    }
                } else{
                    printf("\n----------------------\n User Not Found \n----------------------");
                }
                break;

            case 3:
                //Add/Remove posts
                manage_posts(users);
                break;

            case 4:
                //Manage user's friends
                manage_friends(users);
                break;
            
            case 5: 
                //Display n posts
                printf("\nEnter a username to display posts: ");
                scanf("%s", &user);
                finding_user=find_user(users, user);
                if(finding_user==NULL){
                    printf("\n----------------------\n User Not Found \n----------------------");
                } else{
                    display_posts_by_n(finding_user, DISPLAY_POSTS);
                }
                break;

            //Exit
            case 6:
                printf("\nThank you for using TextBook!");
                teardown(users);
                users=NULL;
                cont=false;
                break;
        }
    }

    return EXIT_SUCCESS;
}
