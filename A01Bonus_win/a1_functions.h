/********* a1_functions.h ********
	
	Student Name 	= Eshal Kashif
	Student Number	= 101297950
*/

/* BONUS TASK 5 EXPLANATION
Milestone IDs:
-Changed function delcaration to pass array of initialized IDs to init_milestone
-Before, if user entered non-unique ID, they were prompted to change it after ALL
milestones were initialized 
-Now, if the user enters a non-unique ID, they are prompted immediately to enter a different one
-Improves organization and logical flow, as ID can now be checked while initializing a milestone,
rather than after 

Activity IDs:
-Since there is no specified max num of activity IDs, I used a linked list to store IDs
-Memory is allocated on the heap, saves data space and increases organization
-Can dynamically iterate through array to check for unique IDs within the 
init_activity function 
-Can update linked list of IDs and add as many IDs as needed, so no need to declare 
an array with too little or too much space
-Before, we were declaring an array with the maximum number of activities, leading to some 
space not being used, increasing storage and data usage
-Now we can create a linked list that is the sufficient in size, with no excess or limit to 
storage
*/

#include <stdbool.h>
#include "a1_data_structures.h"


/********** DON'T MODIFY - FROM HERE **********/
/* 
   Get unsigned short integer user input.
   The value entered by the user must be positive.
   If the user enters a negative value, the function asks user to re-enter a positive value.
*/
unsigned short int get_input_usi(void);

/*
   Get float user input. The value must be positive.
   The value entered by the user must be positive.
   If the user enters a negative value, the function asks user to re-enter a positive value.
*/
float get_input_f(void);

/* 
   Initialize all fields in an activity as per the instructions (3)
*/
void init_activity(activity_t * activity_to_int, node_t *head);
/* 
   Initialize all fields in the milestone as per the instructions (3)
   The implementation of your function MUST call the function init_activity.
*/
void init_milestone(milestone_t * milestone_to_int, unsigned short int num_activities, int milestoneIDs[], int k, node_t *head);


/* 
   Initialize all fields in the project as per the instructions (4)
   number_activities contains the number of activities per milestone
*/
project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int * number_activities);


/* 
   Print the main menu as per the instructions (5)
*/
void print_main_menu(void);

/*
   Print out milestone stats as per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void print_milestone_stats(const milestone_t * list_milestones, int num_milestones, const int * number_activities);

/*
   Print out project stats as per the instructions (6)
   number_activities contains the number of activities per milestone
   The implementation MUST call print_stats_milestone
*/
void print_project_stats(project_t details, const milestone_t * list_milestones, int num_milestones, const int * number_activities);

/*
   Update activity per the instructions (6)
*/
void update_activity(activity_t * activity_to_update);
/*
   Update milestone per the instructions (6)
*/
void update_milestone(milestone_t * milestone_to_update, int activities_in_milestone);

/*
   Update project per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void update_project(const milestone_t * milestone_array, int num_milestones, const int * number_activities, project_t * my_project);

/********** DON'T MODIFY - UNTIL HERE **********/

void handle_submenu(milestone_t * milestone_array, int num_milestones, const int * number_activities);

_Bool activities_completed(milestone_t * milestone_array, int num_milestones, const int * number_activities);

void free_data(milestone_t *milestone_array, int num_milestones, node_t *head);





