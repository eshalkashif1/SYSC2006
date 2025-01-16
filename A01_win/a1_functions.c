/********* a1_functions.c ********
	
	Student Name 	= Eshal Kashif
	Student Number	= 101297950
*/
#include <stdlib.h>  
#include <stdio.h>   
#include <stdbool.h>
#include "a1_functions.h"
#include <string.h>
#include <math.h>

#define AVG_HOURLY 30.00
#define INIT_COST 0.0
#define INIT_DURATION 0
#define INIT_COMPLETION false
#define DAY 8

//Getting integer input
unsigned short int get_input_usi(void){
	int input;
	int num = scanf("%d", &input); // Get input and store 
	// If negative input, ask again until valid input is entered
	while(input < 1){
		printf("Must be positive input. Try again: ");
		num = scanf("%d", &input);
	}
	return input;
}

//Getting float input
float get_input_f(void){
	float input;
	float num = scanf("%f", &input);
	while(input < 0){
		printf("Must be positive input. Try again: ");
		num = scanf("%f", &input);
	}
	return input;
}

void init_activity(activity_t * activity_to_int){
	char name[100];
	int id;
	int planned_duration = 0;

	//Ask  for activity name
	printf("\nEnter activity name: ");
	scanf("%s", name);
	//Ask for acitivty ID
	printf("\nEnter activity ID: ");
	activity_to_int->id = get_input_usi();
	//Ask for planned duration
	printf("\nEnter the planned duration: ");
	planned_duration = get_input_usi();

	//Initialize
	strcpy(activity_to_int->name, name);
	activity_to_int->planned_duration = planned_duration;
	activity_to_int->planned_cost = (activity_to_int->planned_duration)*(AVG_HOURLY);
	activity_to_int->actual_cost = INIT_COST;
	activity_to_int->completed = INIT_COMPLETION;
	activity_to_int->actual_duration = INIT_DURATION;
}

void init_milestone(milestone_t * milestone_to_int, unsigned short int num_activities){
	char name[100];
	int id;

	//Ask for milestone name
	printf("\nEnter milestone name: ");
	scanf("%s", name);
	//Ask for milestone ID
	printf("\nEnter milestone ID: ");
	milestone_to_int->id = get_input_usi();
	//Initialize activities
	for(int i = 0; i < num_activities; i++){
		printf("\nINITIALIZING ACTIVITY %d\n", i+1);
		init_activity(&milestone_to_int->activity_list[i]);
	}
	//Initialize
	strcpy(milestone_to_int->name, name);
	milestone_to_int->completed = INIT_COMPLETION;
	milestone_to_int->actual_cost = INIT_COST;
	milestone_to_int->actual_duration = INIT_DURATION;
}

project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int * number_activities){
	float planned_cost = 0.0;
	unsigned short int planned_duration = 0;
	project_t project;

	//Planned cost and total hours (duration)
	for(int i = 0; i < number_milestones; i++){
		for(int j = 0; j < number_activities[i]; j++){
			planned_cost += milestone_list[i].activity_list[j].planned_cost;
			planned_duration += milestone_list[i].activity_list[j].planned_duration;
		}
	}
	
	//Initialize
	strcpy(project.name, name);
	project.actual_cost = INIT_COST;
	project.planned_cost = planned_cost;
	project.planned_duration = planned_duration/DAY;
	project.actual_duration = INIT_DURATION;
	project.completed = INIT_COMPLETION;
	return project;
}

void print_main_menu(void){
	printf("\n\nMAIN MENU OPTIONS\n1. Update Activity\n2. Print Stats\n3. Exit");
}

void print_milestone_stats(const milestone_t * list_milestones, int num_milestones, const int * number_activities){
	for(int i = 0; i < num_milestones; i++){
		printf("\n\nMILESTONE %s\n", list_milestones[i].name);
		//If milestone is marked as complete, print the following
		if(list_milestones[i].completed){
			float actual_cost = list_milestones[i].actual_cost;
			int duration_days = list_milestones[i].actual_duration;
			printf("Status: Completed");
			printf("\n$%.2f %s", fabs(actual_cost), actual_cost >=0 ? "over budget":"under budget");
			printf("\n%d days %s", abs(duration_days), duration_days >= 0 ? "delayed":"early");
		}
		else{
			int activities_completed = 0;
			float total_cost = 0.0;
			int total_duration = 0;
			for(int j = 0; j < number_activities[i]; j++){
				if(list_milestones[i].activity_list[j].completed){
					activities_completed++;
				}
				total_duration += list_milestones[i].activity_list[j].planned_duration;
				total_cost += list_milestones[i].activity_list[j].planned_cost;
			}
			printf("Status: Incompleted");
			printf("\n%d/%d activites completed", activities_completed, number_activities[i]);
			printf("\nPlanned duration: %d hours", total_duration);
			printf("\nPlanned cost: $%.2f", total_cost);
		}
	}
}


void print_project_stats(project_t details, const milestone_t * list_milestones, int num_milestones, const int * number_activities){
	printf("\nPROJECT %s", details.name);
	if(details.completed){
		int total_cost = (details.actual_cost - details.planned_cost);
		int total_duration = (details.actual_duration - details.planned_duration);
		printf("\nStatus: Completed");
		printf("\n$%d %s", abs(total_cost), total_cost > 0 ? "over budget":"under budget");
		printf("\n%d days %s", abs(total_duration), total_duration > 0 ? "delayed":"early");
	}
	else{
		print_milestone_stats(list_milestones, num_milestones, number_activities);
	}
}

void update_activity(activity_t * activity_to_update){
	char completed_input;
	int actual_duration;
	//Getting inputs
	printf("\nEnter the actual duration: ");
	actual_duration = get_input_usi();
	printf("\nIs the activity completed? (Y/N): ");
	scanf(" %c", &completed_input);
	//Initializing
	if(completed_input=='Y' || completed_input=='y'){
		activity_to_update->completed=true;
	}
	activity_to_update->actual_duration = actual_duration;
	activity_to_update->actual_cost = actual_duration*AVG_HOURLY;
}

void update_milestone(milestone_t * milestone_to_update, int activities_in_milestone){
	int activities_completed = 0;
	//Find how many activities are completed
	for(int i = 0; i < activities_in_milestone; i++){
		if(milestone_to_update->activity_list[i].completed){
			activities_completed++;
		}
	}
	//If all activities are completed initialize the following
	if(activities_completed==activities_in_milestone){
		milestone_to_update->completed=true;
		for(int i = 0; i < activities_in_milestone; i++){
			milestone_to_update->actual_cost += milestone_to_update->activity_list[i].actual_cost;
			milestone_to_update->actual_duration += milestone_to_update->activity_list[i].actual_duration;
		}
	}
}

void update_project(const milestone_t * milestone_array, int num_milestones, const int * number_activities, project_t * my_project){
	int completed_activities = 0;
	int total_activities = 0;
	int total_duration = 0;
	int total_cost = 0;
	//Find total num of activities
	for(int i = 0; i < num_milestones; i++){
		total_activities += number_activities[i];
	}
	//Update the following if a milestone is complete
	for(int i = 0; i < num_milestones; i++){
		for(int j = 0; j < number_activities[i]; j++){
			if(milestone_array[i].activity_list[j].completed){
				completed_activities++;
				total_cost += milestone_array[i].actual_cost;
				total_duration += milestone_array[i].actual_duration;
			}
			else{
				break;
			}
		}
	}
	if(completed_activities==total_activities){
		my_project->completed=true;
		my_project->actual_cost = total_cost;
		my_project->actual_duration = total_duration/DAY;
	}
}

//Method to handle submenu for case 1 (updating activities)
void handle_submenu(milestone_t * milestone_array, int num_milestones, const int * number_activities){
	char completed_ativity[15];
	int id_choice;
	//Display activities
	for(int i = 0; i < num_milestones; i++){
		for(int j = 0; j < number_activities[i]; j++){
			if(milestone_array[i].activity_list[j].completed){
				strcpy(completed_ativity, "Complete");
			}
			else{
				strcpy(completed_ativity, "Incomplete");
			}
			printf("\nActivity %s. ID %d. %s", milestone_array[i].activity_list[j].name, 
			milestone_array[i].activity_list[j].id, completed_ativity);
		}
	}
	// Ask for input for activity
	bool bad_choice = true;
	printf("\nEnter the Activity ID to be updated: ");
	//Ensure input is a valid option
	while(bad_choice){
		id_choice = get_input_usi();
		for(int i = 0; i < num_milestones; i++){
			for(int j = 0; j < number_activities[i]; j++){
				if(id_choice==milestone_array[i].activity_list[j].id && !milestone_array[i].activity_list[j].completed){
					update_activity(&milestone_array[i].activity_list[j]);
					update_milestone(&milestone_array[i], number_activities[i]);
					bad_choice = false;
					break;
				}
			}
		}
		if(bad_choice){
			printf("Invalid ID or activity already completed. Try again: ");
		}
	}
	
}











