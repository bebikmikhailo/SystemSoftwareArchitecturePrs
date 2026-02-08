#ifndef ERF_MODULE_H
#define ERF_MODULE_H

// Constant for the size of the t-distribution table
#define T_TABLE_ROWS 34
#define T_TABLE_COLS 3

// Table of t-values
extern double t_table[T_TABLE_ROWS][T_TABLE_COLS];

// Functions for working with the t-distribution table
int get_df_index(int df);
int get_confidence_index(int confidence_level);
double get_t_value_from_table(int df, int confidence_level);

// Functions for normal distribution
double find_confidence_level(double z);
double find_z_by_confidence_level(int confidence_level);

// Functions for processing normal distribution options
void first_option_options_normal();
void first_option_normal();
void second_option_normal();
void third_option();

// Functions for processing t-distribution options
void first_option_options_t();
void first_option_t();
void second_option_t();

#endif