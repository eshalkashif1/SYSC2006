#ifndef __STRUCT_STRING_H__
#define __STRUCT_STRING_H__

// for Exercise 1
typedef struct {
	int num;  // numerator
	int den;  // denominator
} fraction_t;


// for Exercise 2
typedef struct {
	int code; // course code
	float weight; // course weight
	int gp; // course grade point
} grade_t;

typedef struct {
	int id;  // student id
	float gpa;  // student gpa
	grade_t grades[6]; // student grades
} student_t;

// for Exercise 1
void make_fraction(int a, int b, fraction_t* pf);
void print_fraction(const fraction_t* pf);
void add_fractions(const fraction_t* pf1, const fraction_t* pf2, fraction_t* psum);
void multiply_fractions(const fraction_t* pf1, const fraction_t* pf2, fraction_t* pprod);

/* Helper functions. */
int gcd(int a, int b);
void reduce(fraction_t* pf);


// for Exercise 2
void update_gpa(student_t *studentp, int numGrades);
float calc_gpa(const grade_t *pgrades, int numGrades);

// for Exercise 3
int count_char(const char *, char );

// for Exercise 4
int count_char_wp(const char *, char );

#endif