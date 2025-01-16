/*****************
    Student Name 	= Eshal Kashif
    Student Number	= 101297950
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a2_nodes.h"
#include "a2_functions.h"
#include <ctype.h>

// Your solution goes here
#define MAX_CHAR_USER 30
#define MAX_CHAR_PASS 15
#define MIN_CHAR_PASS 8
#define MIN_MENU_CHOICE 1
#define MAX_MENU_CHOICE 5
#define MAX_SUBMENU_CHOICE 3
#define POST_LIMIT 250
#define YES_NO_INPUT 2
#define DISPLAY_POSTS 3



/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}

user_t *add_user(user_t *users, const char *username, const char *password){
    
    //Creating new user node
    user_t *new_user = malloc(sizeof(user_t));
    assert(new_user!=NULL);
    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    new_user->friends=NULL;
    new_user->posts=NULL;
    new_user->next=NULL;
    // Placing new user in alphabetical order 
    user_t *current = users;
    //If no users
    if(current==NULL){
        return new_user;
    }
    //Inserting at head of list
    if(strcmp(username, current->username)<0){
        new_user->next=current;
        users=new_user;
    }else{ //Inserting elsewhere
        for(; current!=NULL && current->next!=NULL; current=current->next){
            if(strcmp(username, current->next->username) < 0){
                break;
            }
        }
        new_user->next = current->next;
        current->next=new_user;
    }
    return users;
}

user_t *find_user(user_t *users, const char *username){
    for(user_t *temp=users; temp!=NULL; temp=temp->next){
        if(strcmp(username, temp->username)==0){
            return temp;
        }
    }
    return NULL;
    
}

friend_t *create_friend(const char *username){
    friend_t *friend = malloc(sizeof(friend_t));
    assert(friend!=NULL);
    strcpy(friend->username, username);
    friend->next=NULL;
    return friend;
}


void add_friend(user_t *user, const char *friend){
    friend_t *new_friend = create_friend(friend);
    //If no friends
    friend_t *current=user->friends;
    if(user->friends==NULL){
        user->friends=new_friend;
    //Place friend alphabetically
    } else{
        //Compare new friend with first friend in list
        if(strcmp(friend, current->username)<0){
            new_friend->next=current;
            user->friends=new_friend;
        //Compare new friend with rest of friends
        } else{
            for(; current!=NULL && current->next!=NULL; current=current->next){
                if(strcmp(friend, current->next->username)<0){
                    break;
                }
            }
            new_friend->next=current->next;
            current->next=new_friend;
        }
    }
}


_Bool delete_friend(user_t *user, char *friend_name){
    friend_t *current=user->friends;
    //Check if user has friends 
    if(user->friends!=NULL){
        //Removing at the head
        if(strcmp(friend_name, current->username)==0){
            user->friends=current->next;
            free(current);
            return true;
        //Removing elsewhere
        } else{
            friend_t *previous = current;
            current=current->next;
            for(; current!=NULL; previous=current, current=current->next){
                if(strcmp(friend_name, current->username)==0){
                    previous->next=current->next;
                    free(current);
                    return true;
                }
            }
        }
        //If friend not found
        return false;
    }else{
        //If no friends
        return false;
    }
}

post_t *create_post(const char *text){
    post_t *post = malloc(sizeof(post_t));
    assert(post!=NULL);
    strcpy(post->content, text);
    post->next=NULL;
    return post;
}

void add_post(user_t *user, const char *text){
    post_t *new_post = create_post(text);
    new_post->next=user->posts;
    user->posts=new_post;
}

_Bool delete_post(user_t *user){
    if(user->posts!=NULL){
        post_t *delete = user->posts;
        user->posts = user->posts->next;
        free(delete);
        return true;
    } else{
        return false;
    }

}

void display_all_user_posts(user_t *user){
    printf("\n%s\'s Posts", user->username);
    int count=0;
    for(post_t *temp=user->posts; temp!=NULL; temp=temp->next){
        count++;
        printf("\n----------------------\
        \n%d - %s\
        \n----------------------", count, temp->content);
    }
}


void display_user_friends(user_t *user){
    int count=0;
    for(friend_t *current=user->friends; current!=NULL; current=current->next){
        count++;
        printf("\n%d - %s", count, current->username);
    }
}

char get_yes_no_input(void){
    char input;
    printf("\nWould you like to display more posts? (Y/N): ");
    scanf(" %c", &input);
    while(tolower(input)!='y' && tolower(input)!='n'){
        printf("\nInvalid choice. Try again: ");
        scanf(" %c", &input);
    }
    return tolower(input);
}

void display_posts_by_n(friend_t *friend, int number){
    printf("\nDisplaying %s\'s Posts", friend->username);
    bool cont = true;
    int count = 1;
    int i =0;
    char input;
    post_t *posts = *friend->posts;
    while(cont){
        while(posts!=NULL && i<3){
            printf("\n%d - %s", count, posts->content);
            posts=posts->next;
            count++;
            i++;
        }
        if(posts==NULL){
            printf("\nNo more posts to display");
            cont=false;
        }else{
             input=get_yes_no_input();
            if(input=='n'){
                cont=false;
            }else{
                i=0;
            }
        }
    }
}

void teardown(user_t *users){
    while(users!=NULL){
        //Free posts
        while(users->posts!=NULL){
            post_t *next_post=users->posts->next;
            free(users->posts);
            users->posts=next_post;
        }
        while(users->friends!=NULL){
            friend_t *next_friend=users->friends->next;
            free(users->friends);
            users->friends=next_friend;
        }
        user_t *next_user=users->next;
        free(users);
        users=next_user;
    }

}


void print_menu(){
    printf("\n**********************\n    MAIN MENU\n**********************\n\
    1. Register a new user\n\
    2. Login with existing user\n\
    3. Exit\n");
}

unsigned short int get_menu_choice(unsigned short int min_choice, unsigned short int max_choice){
	int input;
    printf("\nEnter a choice: ");
	int num = scanf("%d", &input); // Get input and store 
	// If negative input, ask again until valid input is entered
	while(input < min_choice || input > max_choice){
		printf("Invalid choice. Try again: ");
		num = scanf("%d", &input);
	}
	return input;
}


void add_new_post(user_t *user){
    //Ask for text
    printf("\nEnter your post content: ");
    char text[POST_LIMIT];
    scanf(" %[^\n]s", &text);
    create_post(text); //Creating post
    add_post(user, text); //Adding post
    display_all_user_posts(user); //Printing all posts
}

void manage_posts(user_t *user){
    printf("\n----------------------\n Managing %s\'s Posts \n----------------------\n", user->username);
    if(user->friends==NULL){
            printf("Note: No posts available for %s", user->username);
        }
        bool cont = true;
        while(cont){
            printf("\n1. Add a new post\
            \n2. Remove a post\
            \n3. Return to main menu");
            int choice = get_menu_choice(MIN_MENU_CHOICE, MAX_SUBMENU_CHOICE);
            switch(choice){
                case 1:
                    add_new_post(user);
                    break;
                case 2:
                    bool delete = delete_post(user);
                    if(delete){
                        printf("\nPost successfully deleted");
                        display_all_user_posts(user);
                    } else{
                        printf("\n%s has no posts.", user);
                    }
                case 3:
                    cont=false;
                    break;
            }
        }
}

void manage_friends(user_t *user, user_t *users){
    printf("\n----------------------\n Managing %s\'s Friends \n----------------------", user->username);
    bool cont = true;
    char friend_name[MAX_CHAR_PASS];
    while(cont){
        printf("\n\n1. Add a new friend\
        \n2. Remove a friend\
        \n3. Return to main menu\n");
        int choice = get_menu_choice(MIN_MENU_CHOICE, MAX_SUBMENU_CHOICE);
        switch(choice){
            case 1:
                printf("\nEnter a new friend's name: ");
                scanf("%s", &friend_name);
                user_t *friend = find_user(users, friend_name);
                if(friend!=NULL){
                    add_friend(user, friend_name);
                    printf("\nFriend added to list");
                }else{
                    printf("\n---------------------- \n Friend Not A User \n----------------------\n");
                }
                break;
            case 2:
                printf("\nList of %s\'s Friends", user->username);
                display_user_friends(user);
                printf("\nEnter a friends name to delete: ");
                scanf("%s", friend_name);
                bool deleted = delete_friend(user, friend_name);
                if(deleted){
                    printf("\nUpdated List of %s\'s Friends", user->username);
                    display_user_friends(user);
                } else{
                    printf("\n---------------------- \n Friend Not Found \n----------------------\n");
                }
                break;
            case 3:
                cont=false;
                break;
        }
    }
}

char *get_lower(char *user){
    for(int i=0; i<strlen(user); i++){
        user[i]=tolower(user[i]);
    }
    return user;
}

void display_friend_posts(user_t *user, user_t *allusers){
    char friend_name[MAX_CHAR_USER];
    _Bool friend_found=false;
    friend_t *friend;

    display_user_friends(user);
    printf("\nEnter a friend: ");
    scanf("%s", &friend_name);

    for(friend_t *f = user->friends; f!=NULL && !friend_found; f=f->next){
        if(strcmp(f->username, friend_name)==0){
            friend_found=true;
            friend = f;
        }
    }
    if(friend_found){
        user_t *friend_as_user = find_user(allusers, friend_name);
        friend->posts = &(friend_as_user->posts);
        display_posts_by_n(friend, DISPLAY_POSTS);

    }else{
        printf("----------------------\n %s is not your friend\n----------------------", friend_name);
    }

}

void handle_choice_2(user_t *user, const char *username, user_t *allusers){
    _Bool cont=true;
    char pass[MAX_CHAR_PASS];
    char newpass[MAX_CHAR_PASS];
    while(cont){
        printf("\n----------------------\n Welcome %s \n----------------------\n\
        1. Manage profile (change passwords)\n\
        2. Manage posts (add/remove)\n\
        3. Manage friends (add/remove)\n\
        4. Display a friend's posts\n\
        5. Exit ", user);
        int choice = get_menu_choice(MIN_MENU_CHOICE, MAX_MENU_CHOICE);

        switch(choice){
            case 1:
                //Change passwords
                printf("\nEnter a new password (15 char max): ");
                scanf("%s", &newpass);
                while(strlen(newpass)<MIN_CHAR_PASS){
                    printf("\nPassword must be minimum 8 characters: ");
                    scanf("%s", &newpass);
                }
                strcpy(user->password, newpass);

            case 2: 
                //Add/remove posts
                manage_posts(user);
                break;

            case 3:
                //Add/remove friends
                manage_friends(user, allusers);
                break;

            case 4: 
                //Display friends post
                display_friend_posts(user, allusers);
                break;

            case 5:
                cont=false;
                break;
        }
    }

}




