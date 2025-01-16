//SYSC 2006 - Lab 2 Template

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Include the necessary header for _Bool
#include "lab2.h"

/* Replace these lines with your information */ 
  const char* author_main = "Eshal Kashif"; 
  const char* student_number_main = "101297950"; 

  void test_prime(int value);
  void test_non_prime(int value);
  void test_count_replace(int value, char* expected_result);
  void test_sum_even(int value, int expected_result);

void test_prime(int value){
  _Bool expected_prime = true;
  if(is_prime(value) == expected_prime){
    printf("Num %d, TEST PASS.\n", value);
  } else{
    printf("Num %d, TEST FAIL.\n", value);
  }
  return;
}

void test_non_prime(int value){
  _Bool expected_non_prime = false;
    if(is_prime(value) == expected_non_prime){
      printf("Num %d, TEST PASS.\n", value);
    } else{
      printf("Num %d, TEST FAIL.\n", value);
    }
    return;
}

void test_count_replace(int value, char* expected_result){
  printf("Num %d, Expected VS Actual Result\n", value, expected_result);
  printf("%s\n", expected_result);
  count_replace(value);
  return;
}

void test_sum_even(int value, int expected_result){
  if(sum_even(value)==expected_result){
    printf("Num %d, TEST PASS.\n", value);
  } else {
    printf("Num %d, TEST FAIL.\n", value);
  }
  return;
}

int main(void){
  // Tests exercise 1 - Complete for a comprehensive test harness
  // TEST 1: Weekday and Non-Vacation
  printf("\n\nTESTING alarm_clock\n");

  int expected_week_non_vac = 7;
  for(int day = 1; day <=5; day++){
    int alarm_time = alarm_clock(day, false);
    if (alarm_time == expected_week_non_vac) {
      printf("Day %d, Non vacation: TEST PASS.\n", day);
    } else {
      printf("Day %d, Non vacation: TEST FAIL.\n", day);
    } 
  }
  // TEST 2: Weekend and Non-Vacation
  int expected_weekend_non_vac = 10;
  for(int day=0; day <=6; day+=6){
    int alarm_time = alarm_clock(day, false);
    if(alarm_time == expected_weekend_non_vac){
      printf("Day %d, Vacation: TEST PASS.\n", day);
    } else {
      printf("Day %d, Vacation: TEST FAIL.\n", day);
    }
  }
  // TEST 3: Weekday and Vacation
  int expected_week_vac = 10;
  for(int day = 1; day <=5; day++){
    int alarm_time = alarm_clock(day, true);
    if (alarm_time == expected_week_vac){
      printf("Day %d, Vacation: TEST PASS.\n", day);
    } else {
      printf("Day %d, Vacation: TEST FAIL.\n", day);
    }
  }
  // TEST 4: Weekend and Vacation
  int expected_weekend_vac = -1;
  for(int day=0; day <=6; day+=6){
    int alarm_time = alarm_clock(day, true);
    if(alarm_time == expected_weekend_vac){
      printf("Day %d, Vacation: TEST PASS.\n", day);
    } else {
      printf("Day %d, Vacation: TEST FAIL.\n", day);
    }
  }
  
  // Type your test cases for exercise 2. Make sure to include border line cases

  printf("\n\nTESTING count_replace\n");
  test_count_replace(16,"1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz 16");
  test_count_replace(10, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz");
  test_count_replace(1, "1");
  test_count_replace(30, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz 16 17 Fizz 19 Buzz Fizz 22 23 Fizz Buzz 26 Fizz 28 29 FizzBuzz");


  // Type your test cases for exercise 3. Make sure to include border line cases
  printf("\n\nTESTING is_prime\n");
  // TEST 1-6: prime numbers
  // Calling function above 
  test_prime(2);
  test_prime(7);
  test_prime(47);
  test_prime(97);
  test_prime(73);
  test_prime(199);

  // TEST 7-12: non-prime numbers
  test_non_prime(4);
  test_non_prime(20);
  test_non_prime(74);
  test_non_prime(98);
  test_non_prime(100);
  test_non_prime(50);

  // Type your test cases for exercise 4. Make sure to include border line cases
  printf("\n\nTESTING sum_even\n");
  test_sum_even(2, 2);
  test_sum_even(10, 30);
  test_sum_even(20, 110);
  test_sum_even(7, 12);
  test_sum_even(15, 56);

  printf("Test harness finished\n");
  return EXIT_SUCCESS;
}


