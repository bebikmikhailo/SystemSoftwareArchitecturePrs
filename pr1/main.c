#include <stdio.h>
#include "erf_module.h"


void main_menu() {
    printf("-----------------------------------\n");
    printf("Confidence Interval Calculator\n");
    printf("Options: \n");
    printf("1. Normal distribution (Z-values) \n");
    printf("2. Student's t-distribution (t-values) \n");
}

void normal_menu() {
    printf("-----------------------------------\n");
	printf("Function: erf(z * sqrt(1/2)) \n");
	printf("Options: \n");
	printf("1. Find Z based on preset confidence level \n");
	printf("2. Find Z based on any confidence level \n");
	printf("3. Find confidence level by Z \n");
}

void t_menu() {
    printf("-----------------------------------\n");
	printf("Student's t-distribution \n");
	printf("Options: \n");
	printf("1. Find t based on preset confidence level \n");
	printf("2. Find t based on custom parameters \n");
}


int select_option(int right_bound, int left_bound) {
    printf("Enter option's number: ");
    int choice = 0;
    while(scanf("%d", &choice)) {
        if (choice >= right_bound && choice <= left_bound) {
            break;
        }
        fprintf(stderr, "Incorrect input!! \n");
        printf("Enter option's number: \n");
    }
    return choice;
}


void handle_t_distribution() {
    t_menu();
    switch(select_option(1, 2)) {
        case 1:
            first_option_t(); 
            break;
        case 2:
            second_option_t();
            break;
    }
}


void handle_normal_distribution() {
    normal_menu();
    switch(select_option(1, 3)) {
        case 1:
            first_option_normal(); 
            break;
        case 2:
            second_option_normal();
            break;
        case 3:
            third_option();
            break;
    }
}

int main() {

    main_menu();
    switch(select_option(1, 2)) {
        case 1:
            handle_normal_distribution();
            break;
        case 2:
            handle_t_distribution();
            break;
    }

	return 0;
}