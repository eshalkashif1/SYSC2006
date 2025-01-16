/* main.c - SYSC 2006 Lab 7 
 *
 * Do not modify any of the code in this file.
 */
#include <stdio.h>
#include <stdlib.h>  // exit

#include "struct_string.h"
#include "sput.h"

/* Some IDEs generate "warning #2154: Unreachable code"
   and "warning #2130: Result of comparison is constant" when the 
   macros in sput.h are used. The following pragma directive disables the
   generation of these warnings.
 */
#pragma warn(disable: 2130 2154)

static void _print(fraction_t f)
{
	printf("%d/%d", f.num, f.den);
}

static void test_print_fraction(void)
{
	printf("\nTesting print_fraction\n\n");

	fraction_t fr;

	fr = (fraction_t) {1, 3};
	printf("Expected output: 1/3\n");
	printf("Actual output:   ");
	print_fraction(&fr);
	printf("\n\n");

	fr = (fraction_t) {-1, 3};
	printf("Expected output: -1/3\n");
	printf("Actual output:   ");
	print_fraction(&fr);
	printf("\n\n");
}

static void test_gcd(void)
{
	sput_fail_unless(gcd(42, 30) == 6, "gcd(42, 30)");
	printf("Expected result: 6, actual result: %d\n", gcd(42, 30));
	sput_fail_unless(gcd(30, 42) == 6, "gcd(30, 42)");
	printf("Expected result: 6, actual result: %d\n", gcd(30, 42));
	sput_fail_unless(gcd(-42, 30) == 6, "gcd(-42, 30)");
	printf("Expected result: 6, actual result: %d\n", gcd(-42, 30));
	sput_fail_unless(gcd(42, -30) == 6, "gcd(42, -30)");
	printf("Expected result: 6, actual result: %d\n", gcd(42, -30));
	sput_fail_unless(gcd(-42, -30) == 6, "gcd(-42, -30)");
	printf("Expected result: 6, actual result: %d\n", gcd(-42, -30));
	sput_fail_unless(gcd(144, -55) == 1, "gcd(144, -55)");
	printf("Expected result: 1, actual result: %d\n", gcd(144, -55));
}

static void test_reduce(void)
{
	fraction_t fr;

	// Test reduce(1/3)

	fr = (fraction_t) {1, 3}; // Initialize the function to reduce
	reduce(&fr);
	sput_fail_unless(fr.num == 1 && fr.den == 3,
					 "reduce(1/3)");
	printf("Expected result: 1/3, actual result: ");
	_print(fr);
	printf("\n");

	// Test reduce(6/8)

	fr = (fraction_t) {6, 8};
	reduce(&fr);
	sput_fail_unless(fr.num == 3 && fr.den == 4,
					 "reduce(6/8)");
	printf("Expected result: 3/4, actual result: ");
	_print(fr);
	printf("\n");
 

	// Test reduce(-2/3)

	fr = (fraction_t) {-2, 3};
	reduce(&fr);
	sput_fail_unless(fr.num == -2 && fr.den == 3,
					 "reduce(-2/3)");
	printf("Expected result: -2/3, actual result: ");
	_print(fr);
	printf("\n");

	// Test reduce(4/-5)

	fr = (fraction_t) {4, -5};
	reduce(&fr);
	sput_fail_unless(fr.num == -4 && fr.den == 5,
					 "reduce(4/-5)");
	printf("Expected result: -4/5, actual result: ");
	_print(fr);
	printf("\n");

	// Test reduce(-6/-8)

	fr = (fraction_t) {-6, -8};
	reduce(&fr);
	sput_fail_unless(fr.num == 3 && fr.den == 4,
					 "reduce(-6/-8)");
	printf("Expected result: 3/4, actual result: ");
	_print(fr);
	printf("\n");

	// Test reduce(0/7)

	fr = (fraction_t) {0, 7};
	reduce(&fr);
	sput_fail_unless(fr.num == 0 && fr.den == 1,
					 "reduce(0/7)");
	printf("Expected result: 0/1, actual result: ");
	_print(fr);
	printf("\n");

}

static void test_make_fraction(void)
{
	fraction_t result;

	// Test make_fraction(1, 3)

	make_fraction(1, 3, &result);
	sput_fail_unless(result.num == 1 && result.den == 3,
					 "make_fraction(1, 3)");
	printf("Expected result: 1/3, actual result: ");
	_print(result);
	printf("\n");


	// Test make_fraction(6, 8)

  	make_fraction(6, 8,&result);
	sput_fail_unless(result.num == 3 && result.den == 4,
					 "make_fraction(6, 8)");
	printf("Expected result: 3/4, actual result: ");
	_print(result);
	printf("\n");

	// Test make_fraction(-2, 3)
	make_fraction(-2, 3, &result);
	sput_fail_unless(result.num == -2 && result.den == 3,
					 "make_fraction(-2, 3)");
	printf("Expected result: -2/3, actual result: ");
	_print(result);
	printf("\n");

	// Test make_fraction(4, -5)

	make_fraction(4, -5, &result);
	sput_fail_unless(result.num == -4 && result.den == 5,
					 "make_fraction(4, -5)");
	printf("Expected result: -4/5, actual result: ");
	_print(result);
	printf("\n");


	// Test make_fraction(-6, -8)

	make_fraction(-6, -8, &result);
	sput_fail_unless(result.num == 3 && result.den == 4,
					 "make_fraction(-6, -8)");
	printf("Expected result: 3/4, actual result: ");
	_print(result);
	printf("\n");

	// Test make_fraction(0, 7)

	make_fraction(0, 7, &result);
	sput_fail_unless(result.num == 0 && result.den == 1,
					 "make_fraction(0, 7)");
	printf("Expected result: 0/1, actual result: ");
	_print(result);
	printf("\n");

}

static void test_add_fractions(void)
{
	fraction_t fr1, fr2, result;

	// Test add_fractions: 2/3 + 1/2

	make_fraction(2, 3, &fr1);
	make_fraction(1, 2, &fr2);

	add_fractions(&fr1, &fr2, &result);
	sput_fail_unless(result.num == 7 && result.den == 6,
					 "add_fractions(2/3, 1/2)");
	printf("Expected result: 7/6, actual result: ");
	_print(result);
	printf("\n");
   

	// Test add_fractions: 1/2 + 2/1

	make_fraction(1, 2, &fr1);
	make_fraction(2, 1, &fr2);

	add_fractions(&fr1, &fr2, &result);
	sput_fail_unless(result.num == 5 && result.den == 2,
					 "add_fractions(1/2, 2/1)");
	printf("Expected result: 5/2, actual result: ");
	_print(result);
	printf("\n");
}


static void test_multiply_fractions(void)
{

	fraction_t fr1, fr2, result;

	// Test multiply_fractions: 2/3 * 1/2

	make_fraction(2, 3,&fr1);
	make_fraction(1, 2, &fr2);

	multiply_fractions(&fr1, &fr2, &result);
	sput_fail_unless(result.num == 1 && result.den == 3,
					 "multiply_fractions(2/3, 1/2)");
	printf("Expected result: 1/3, actual result: ");
	_print(result);
	printf("\n");
 
	// Test multiply_fractions: 1/2 * 2/1

	make_fraction(1, 2, &fr1);
	make_fraction(2, 1, &fr2);

	multiply_fractions(&fr1, &fr2, &result);
	sput_fail_unless(result.num == 1 && result.den == 1,
					 "multiply_fractions(1/2, 2/1)");
	printf("Expected result: 1/1, actual result: ");
	_print(result);
	printf("\n"); 
}
static void test_count_char(void)
{

	char test1[] = "Hello world";
	char target1 = 'l';
	char target2 = 'a';
	char target3 = 'L';
	char target4 = 'H';
	char target5 = 'o';
	int count;
	count = count_char(test1,target1);
	sput_fail_unless(count == 3, "count_char(\"Hello world\", 'l')");
	printf("Expected result: 3, actual result: ");
	printf("%d",count);
	printf("\n"); 
	count = count_char(test1,target2);
	 sput_fail_unless(count == 0, "count_char(\"Hello world\", 'a')");
	printf("Expected result: 0, actual result: ");
	printf("%d",count);
	printf("\n"); 
	count = count_char(test1,target3);
	 sput_fail_unless(count == 0, "count_char(\"Hello world\", 'L')");
	printf("Expected result: 0, actual result: ");
	printf("%d",count);
	printf("\n"); 
	count = count_char(test1,target4);
	 sput_fail_unless(count == 1, "count_char(\"Hello world\", 'H')");
	printf("Expected result: 1, actual result: ");
	printf("%d",count);
	printf("\n"); 
	count = count_char(test1,target5);
	 sput_fail_unless(count == 2, "count_char(\"Hello world\", 'o')");
	printf("Expected result: 2, actual result: ");
	printf("%d",count);
	printf("\n"); 
	printf("\n\n");
}

static void test_count_char_wp(void)
{

	char test1[] = "Hello world";
	char target1 = 'l';
	char target2 = 'a';
	char target3 = 'L';
	char target4 = 'H';
	char target5 = 'o';
	int count;
	count = count_char_wp(test1,target1);
	sput_fail_unless(count == 3, "count_char_wp(\"Hello world\", 'l')");
	printf("Expected result: 3, actual result: ");
	printf("%d",count);
	printf("\n"); 
	count = count_char_wp(test1,target2);
	 sput_fail_unless(count == 0, "count_char_wp(\"Hello world\", 'a')");
	printf("Expected result: 0, actual result: ");
	printf("%d",count);
	printf("\n"); 
	count = count_char_wp(test1,target3);
	 sput_fail_unless(count == 0, "count_char_wp(\"Hello world\", 'L')");
	printf("Expected result: 0, actual result: ");
	printf("%d",count);
	printf("\n"); 
	count = count_char_wp(test1,target4);
	 sput_fail_unless(count == 1, "count_char_wp(\"Hello world\", 'H')");
	printf("Expected result: 1, actual result: ");
	printf("%d",count);
	printf("\n"); 
	count = count_char_wp(test1,target5);
	 sput_fail_unless(count == 2, "count_char_wp(\"Hello world\", 'o')");
	printf("Expected result: 2, actual result: ");
	printf("%d",count);
	printf("\n"); 
	printf("\n\n");
}

int main(void)
{	
	printf("Running test harness for SYSC 2006 Lab 7\n");
	sput_start_testing();

	sput_enter_suite("Exercise 1A: print_fraction()");
	sput_run_test(test_print_fraction);
	
	sput_enter_suite("Exercise 1B: gcd()");
	sput_run_test(test_gcd);
	sput_leave_suite();

	if (sput_get_return_value() == EXIT_FAILURE) {
		printf("Tests for remaining exercises won't be run until gcd "
			   "passes all tests.\n");
		sput_finish_testing();
		return sput_get_return_value();
	}

	sput_enter_suite("Exercise 1C: reduce()");
	sput_run_test(test_reduce);
	sput_leave_suite();

	if (sput_get_return_value() == EXIT_FAILURE) {
		printf("Tests for remaining exercises won't be run until reduce "
			   "passes all tests.\n");
		sput_finish_testing();
		return sput_get_return_value();
	}

	sput_enter_suite("Exercise 1D: make_fraction()");
	sput_run_test(test_make_fraction);
	sput_leave_suite();

	if (sput_get_return_value() == EXIT_FAILURE) {
		printf("Tests for remaining exercises won't be run until make_fraction "
			   "passes all tests.\n");
		sput_finish_testing();
		return sput_get_return_value();
	}

	sput_enter_suite("Exercise 1E: add_fractions()");
	sput_run_test(test_add_fractions);

	sput_leave_suite();

	if (sput_get_return_value() == EXIT_FAILURE) {
		printf("Tests for remaining exercises won't be run until add_fractions "
			   "passes all tests.\n");
		sput_finish_testing();
		return sput_get_return_value();
	}

	sput_enter_suite("Exercise 1F: multiply_fractions()");
	sput_run_test(test_multiply_fractions);

   
	
	printf("For exercise 2, you will do manual testing. Check that the output matches the expected output\n");
	
	
	// Exercise 2

	// set up an array of student data
	const int STSIZE = 10;
	const int GRSIZE = 6;
	student_t students[STSIZE];
	for (int i=0; i<STSIZE; i++) {
		students[i].id = i*10+7;
		students[i].gpa = 0;
		for (int j=0; j<GRSIZE; j++) {
			students[i].grades[j].code = (i+j)*5+2;
			students[i].grades[j].weight = (j%2+1)*0.5;
			students[i].grades[j].gp = (i+j)%13;
		}
	}
	
	// print the student data before calculating GPAs
	for (int i=0; i<STSIZE; i++) {
		printf("Student Index: %d  Student ID: %d  Student GPA: %.1f\n", i, students[i].id, students[i].gpa);
		for (int j=0; j<GRSIZE; j++) {
			printf("\t Grade Index: %d  Grade Code: %d  Grade Weight: %.1f  Grade Point: %d\n", j, students[i].grades[j].code, students[i].grades[j].weight, students[i].grades[j].gp);
		}
	}
	printf("\n"); 
	
	// update the students' GPAs
	for (int i=0; i<STSIZE; i++){
		update_gpa(&students[i],GRSIZE);
	}
	
	// print the student (updated) GPAs
	for (int i=0; i<STSIZE; i++){
		printf("Student Index: %d  Student ID: %d  Student GPA: %.1f\n", i, students[i].id, students[i].gpa);
	}
	printf("\n");
	
sput_enter_suite("Exercise 3: count_char()");
	sput_run_test(test_count_char);
	sput_leave_suite();

	if (sput_get_return_value() == EXIT_FAILURE) {
		printf("Tests for remaining exercises won't be run until count_char "
			   "passes all tests.\n");
		sput_finish_testing();
		return sput_get_return_value();
	}

	sput_enter_suite("Exercise 4: count_char_wp()");
	sput_run_test(test_count_char_wp);
	sput_leave_suite();

	if (sput_get_return_value() == EXIT_FAILURE) {
		printf("Tests for remaining exercises won't be run until count_char_wp "
			   "passes all tests.\n");
		sput_finish_testing();
		return sput_get_return_value();
	}

	sput_finish_testing();
	return sput_get_return_value();

}
