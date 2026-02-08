#include <math.h>
#include <stdio.h>
#include "erf_module.h"


// Table with a set of predefined values for Student's t-distribution
// Columns with 90%, 95%, 99% confidence levels
double t_table[T_TABLE_ROWS][T_TABLE_COLS] = {
    {6.314, 12.706, 63.657},
    {2.920, 4.303, 9.925},
    {2.353, 3.182, 5.841},
    {2.132, 2.776, 4.604},
    {2.015, 2.571, 4.032},
    {1.943, 2.447, 3.707},
    {1.895, 2.365, 3.499},
    {1.860, 2.306, 3.355},
    {1.833, 2.262, 3.250},
    {1.812, 2.228, 3.169},
    {1.796, 2.201, 3.106},
    {1.782, 2.179, 3.055},
    {1.771, 2.160, 3.012},
    {1.761, 2.145, 2.977},
    {1.753, 2.131, 2.947},
    {1.746, 2.120, 2.921},
    {1.740, 2.110, 2.898},
    {1.734, 2.101, 2.878},
    {1.729, 2.093, 2.861},
    {1.725, 2.086, 2.845},
    {1.721, 2.080, 2.831},
    {1.717, 2.074, 2.819},
    {1.714, 2.069, 2.807},
    {1.711, 2.064, 2.797},
    {1.708, 2.060, 2.787},
    {1.706, 2.056, 2.779},
    {1.703, 2.052, 2.771},
    {1.701, 2.048, 2.763},
    {1.699, 2.045, 2.756},
    {1.697, 2.042, 2.750},
    {1.684, 2.021, 2.704},
    {1.671, 2.000, 2.660},
    {1.658, 1.980, 2.617},
    {1.645, 1.960, 2.576}
};

int get_df_index(int df) {
    if (df >= 1 && df <= 30) {
        return df - 1;
    } else if (df == 40) {
        return 30;
    } else if (df == 60) {
        return 31;
    } else if (df == 120) {
        return 32;
    } else if (df > 120) {
        return 33;
    }
    return -1;
}

int get_confidence_index(int confidence_level) {
    if (confidence_level == 90) {
        return 0;
    } else if (confidence_level == 95) {
        return 1;
    } else if (confidence_level == 99) {
        return 2;
    }
    return -1;
}

double get_t_value_from_table(int df, int confidence_level) {
    int df_idx = get_df_index(df);
    int conf_idx = get_confidence_index(confidence_level);
    
    if (df_idx == -1 || conf_idx == -1) {
        return -1.0;
    }
    
    return t_table[df_idx][conf_idx];
}


// Normal distribution functions ------------------------------------

double find_confidence_level(double z) {
	if (isnan(z)) {
		fprintf(stderr, "The Z-score has to be a number \n");
	}
	return erf(z * sqrt(1/2.));
}


void third_option() {
    double z = 0;
    printf("Enter Z-score: ");
	if (scanf("%lf", &z) != 1) {
		fprintf(stderr, "Invalid input!\n");
		return;
	}

    if (isnan(z)) {
		fprintf(stderr, "The Z-score has to be a number");
		return;
	}

    printf("The integral of a Normal (0,1) distribution "
		"between -Z and Z is: %g\n", find_confidence_level(z));
}


double find_z_by_confidence_level(int confidence_level) {
    // Value that I choose (it's approximately 50 % confidence level)
    double looking_value = 0.68;

    // current confidence level
    double curr_conf_level = find_confidence_level(looking_value);

    /*
    We use find_confidence_level fucntion to find confidence level
    passing value we looking for as argument.  
    If returned confidence level less than confidence level we look for, looking_value increases by 0.01
    otherwise deacreses by 0.01. 
    */
    while (((int) (100 * curr_conf_level)) != confidence_level) { 
        if (((int) (100 * curr_conf_level)) > confidence_level) {
            looking_value -= 0.01;
        }
        else if (((int) (100 * curr_conf_level)) < confidence_level) {
            looking_value += 0.01;
        }

        curr_conf_level = find_confidence_level(looking_value);

    }

    return looking_value;
}

void second_option_normal() {
    int confidence_level = 0;
    printf("Enter confidence level: ");
    if (scanf("%d", &confidence_level) != 1) {
		fprintf(stderr, "Invalid input!\n");
		return;
	}

    if (confidence_level < 0 && confidence_level > 100) {
		fprintf(stderr, "The confidence level must be in range [0; 100]");
		return;
	}

    printf("Z value: %.2lf \n", find_z_by_confidence_level(confidence_level));
}


void first_option_options_normal() {
    printf("-----------------------------------\n");
	printf("Confidence level options: \n");
	printf("1. 90%%\n");
	printf("2. 95%%\n");
	printf("3. 99%%\n");
}

void first_option_normal() {
    first_option_options_normal();
    int choice = 0;
    printf("Enter option's number: ");
    while(scanf("%d", &choice)) {
        if (choice >= 1 && choice <= 3) {
            break;
        }
        fprintf(stderr, "Incorrect input!! \n");
        printf("Enter option's number: \n");
    }
    
    switch(choice) {
        case 1:
            printf("Z value with 90%% confidence level: %.2lf\n", find_z_by_confidence_level(90));
            break;
        case 2:
            printf("Z value with 95%% confidence level: %.2lf\n", find_z_by_confidence_level(95));
            break;
        case 3:
            printf("Z value with 99%% confidence level: %.2lf\n", find_z_by_confidence_level(99));
            break;        
    }
}

// ----------------------------------------------------------------


// Student's t-distribution functions ------------------------------------

void first_option_options_t() {
    printf("-----------------------------------\n");
	printf("Confidence level options: \n");
	printf("1. 90%%\n");
	printf("2. 95%%\n");
	printf("3. 99%%\n");
}

void first_option_t() {
    int df = 0;
    printf("Enter degrees of freedom (sample size - 1): ");
    if (scanf("%d", &df) != 1) {
		fprintf(stderr, "Invalid input!\n");
		return;
	}

    if (df < 1) {
		fprintf(stderr, "Degrees of freedom must be >= 1\n");
		return;
	}

    first_option_options_t();
    int choice = 0;
    printf("Enter option's number: ");
    while(scanf("%d", &choice)) {
        if (choice >= 1 && choice <= 3) {
            break;
        }
        fprintf(stderr, "Incorrect input!! \n");
        printf("Enter option's number: \n");
    }
    
    int confidence_level = 0;
    switch(choice) {
        case 1:
            confidence_level = 90;
            break;
        case 2:
            confidence_level = 95;
            break;
        case 3:
            confidence_level = 99;
            break;        
    }
    
    double t_value = get_t_value_from_table(df, confidence_level);
    
    if (t_value == -1.0) {
        fprintf(stderr, "Could not find t-value for these parameters\n");
        return;
    }
    
    printf("t value with %d%% confidence level and df=%d: %.3lf\n", 
           confidence_level, df, t_value);
}

void second_option_t() {
    int df = 0;
    int confidence_level = 0;
    
    printf("Enter degrees of freedom (sample size - 1): ");
    if (scanf("%d", &df) != 1) {
		fprintf(stderr, "Invalid input!\n");
		return;
	}

    if (df < 1) {
		fprintf(stderr, "Degrees of freedom must be >= 1\n");
		return;
	}
    
    printf("Enter confidence level (90, 95, or 99): ");
    if (scanf("%d", &confidence_level) != 1) {
		fprintf(stderr, "Invalid input!\n");
		return;
	}

    if (confidence_level != 90 && confidence_level != 95 && confidence_level != 99) {
		fprintf(stderr, "Only 90%%, 95%%, and 99%% confidence levels are supported\n");
		return;
	}
    
    double t_value = get_t_value_from_table(df, confidence_level);
    
    if (t_value == -1.0) {
        fprintf(stderr, "Could not find t-value for these parameters\n");
        return;
    }
    
    printf("t value with %d%% confidence level and df=%d: %.3lf\n", 
           confidence_level, df, t_value);
}

// ----------------------------------------------------------------