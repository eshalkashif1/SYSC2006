/********* main.c ********
	
	Student Name 	= Eshal Kashif
	Student Number	= 101297950
*/

//Complete the includes
#include <stdio.h>
#include <stdlib.h>
#include "a1_functions.h"
#include <stdbool.h>
#include <assert.h>


#define MAX_MENU_CHOICES 3

int main()
{
    /** 1-  Display a welcome message **/
    printf("\nWelcome to ABC Company's Project Management Platform\n\n");


    /** 2- Get the project's name and number of milestones **/
    char projName[100];
    unsigned short int numMilestones;
    unsigned short int numActivities;
    unsigned short int choice;

    printf("Enter the project name: ");
    scanf("%s", projName);

    printf("\nEnter the number of milestones: ");
    numMilestones = get_input_usi();
    
    /** 3- Initialize all milestones and activities.
     * You need an array of milestones. 
     * The capacity of the array must be the max number of milestones the program 
     * can handle as per the instructions **/
    milestone_t *milestonesList = malloc(sizeof(milestone_t)*numMilestones);
    assert(milestonesList != NULL);
    int milestoneIDs[numMilestones];
    //int activityIDs[numMilestones*MAX_ACTIVITIES];
    int numActivityMilestones[numMilestones];
    int countIDs = -1;
    node_t *head = malloc(sizeof(node_t));
    assert(head!=NULL);
    head->next = NULL;

    //Initializing milestones
    for(int i=0; i < numMilestones; i++){
        printf("\nINITIALIZING MILESTONE %d", i+1);
        printf("\n\nEnter number of activities: ");
        numActivities = get_input_usi();
        milestonesList[i].activity_list = malloc(sizeof(activity_t)*numActivities);
        assert(milestonesList[i].activity_list!=NULL);
        //Calling milestone function to initialize
        init_milestone(&milestonesList[i], numActivities, milestoneIDs, i, head);

        numActivityMilestones[i]=numActivities;
        
    }

    /** 4- Initialize the project **/
    project_t project = init_project(projName, milestonesList, numMilestones, numActivityMilestones);

    //Loop continues until user enters case 3
    bool cont = true;

    while(cont){
    /** 5- Print the main menu **/
        print_main_menu();

    /** 6- Get user choice and handle it as per the instructions**/
    
        printf("\n\nEnter a choice: ");
        choice = get_input_usi();
        while(choice > MAX_MENU_CHOICES){
            printf("Input must be 1-3. Try again: ");
            choice = get_input_usi();
        }

        switch(choice){
            case 1:
                //Bonus Task 3
                _Bool activities_complete = activities_completed(milestonesList, numMilestones, numActivityMilestones);
                if(activities_complete){
                    printf("\nAll acitivites completed.");
                }
                else{
                    handle_submenu(milestonesList, numMilestones, numActivityMilestones);
                    update_project(milestonesList, numMilestones, numActivityMilestones, &project);
                }
                break;

            case 2:
                print_project_stats(project, milestonesList, numMilestones, numActivityMilestones);
                break;

            case 3:
                cont = false;
                free_data(milestonesList, numMilestones, head);
                printf("Thank you for using ABC Company's Project Management Platform!");
                break;
        }
    }
    return EXIT_SUCCESS;
}