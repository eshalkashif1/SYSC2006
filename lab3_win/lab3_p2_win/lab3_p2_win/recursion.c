/* SYSC 2006 Lab 3, part 2. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "recursion.h"



/* Exercise 4. Return the number of digits in integer n, n >= 0. */
int num_digits(int n)
{
    if(n<=0){
        return 0;
    }
    return 1 + num_digits(n/10);
}

/* Exercise 5. Return x raised to the power n for n >= 0. */
double power2(double x, int n){
    // Base case when n is less than zero (simplifies to n=0) 
    if(n==0){
        return 1;
    }
    else{
        // Store formula in variable to reduce num times function is called
        double powers = power2(x, n/2)*power2(x, n/2);
        //Recursive case for when n is even
        if(n%2==0){
            return powers;
        }
        // Recursive case for when n is odd
        else{
            return x*powers;
        }
    } 
}

