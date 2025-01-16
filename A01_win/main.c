/********* main.c ********
	
	Student Name 	= Eshal Kashif
	Student Number	= 101297950
*/

//Complete the includes
#include <stdio.h>
#include <stdlib.h>
#include "a1_functions.h"
#include <stdbool.h>

#define MAX_MILESTONES 5
#define MAX_ACTIVITIES 3
#define MAX_MENU_CHOICES 3



int main()
{
    /** 1-  Display a welcome message **/
    printf("\nWelcome to ABC Company's Project Management Platform\n\n");


    /** 2- Get the project's name and number of milestones **/
    char projName[100];
    unsigned short int numMilestones;
    unsigned short int numActivities;
    int numActivityMilestones[MAX_MILESTONES];
    unsigned short int choice;

    printf("Enter the project name: ");
    scanf("%s", projName);

    printf("\nEnter the number of milestones: ");
    numMilestones = get_input_usi();
    while(numMilestones > MAX_MILESTONES){
        printf("Input must be 1-5. Try again: ");
        numMilestones = get_input_usi();
    }
    
    /** 3- Initialize all milestones and activities.
     * You need an array of milestones. 
     * The capacity of the array must be the max number of milestones the program 
     * can handle as per the instructions **/
    milestone_t milestonesList[MAX_MILESTONES];
    int milestoneIDs[numMilestones];
    int activityIDs[numMilestones*MAX_ACTIVITIES];
    int countIDs = -1;

    //Initializing milestones
    for(int i=0; i < numMilestones; i++){
        printf("\nINITIALIZING MILESTONE %d", i+1);
        printf("\n\nEnter number of activities: ");
        numActivities = get_input_usi();
        while(numActivities > MAX_ACTIVITIES){
            printf("Input must be 1-3. Try again: ");
            numActivities = get_input_usi();
        }
        //Calling milestone function to initialize
        init_milestone(&milestonesList[i], numActivities);

        //Check activity IDs
        for(int k = 0; k < numActivities; k++){
            countIDs++;
            for(int n = 0; n < numMilestones*MAX_ACTIVITIES; n++){
                while(milestonesList[i].activity_list[k].id==activityIDs[n]){
                    printf("Activity %d ID already used. Try again: ", k+1);
                    milestonesList[i].activity_list[k].id = get_input_usi();
                    n=0;
                }
            }
            activityIDs[countIDs] = milestonesList[i].activity_list[k].id;
        }

        //Check if milestones have the same ID
        for(int j = 0; j < numMilestones; j++){
            printf("\n");
            while(milestonesList[i].id==milestoneIDs[j]){
                printf("Milestone %d ID already used. Try again: ", i+1);
                (milestonesList[i]).id = get_input_usi();
                j=0;
            }
        }
        //Add ID and activity info to arrays
        milestoneIDs[i] = milestonesList[i].id;
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
                handle_submenu(milestonesList, numMilestones, numActivityMilestones);
                update_project(milestonesList, numMilestones, numActivityMilestones, &project);
                break;

            case 2:
                print_project_stats(project, milestonesList, numMilestones, numActivityMilestones);
                break;

            case 3:
                cont = false;
                printf("Thank you for using ABC Company's Project Management Platform!");
                break;
        }
    }
    return EXIT_SUCCESS;
}