/* SYSC 2006 Lab 4. 

 * Incomplete implementations of the functions that will be coded during the lab.
 */

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "arrays.h"

/* Exercise 1. */

/* Return the average magnitude of the signal represented by
 * the n doubles in x[]. 
 * This function assumes that parameter n is >= 1.
 */
double avg_magnitude(double x[], int n)
{
    double avg_mag = 0;
    for(int i=0; i<n; i++){
        avg_mag += fabs(x[i]);
    }
    return avg_mag/n;
}

/* Exercise 2. */

/* Return the average power of the signal represented by
 * the n doubles in x[].
 * This function assumes that parameter n is >= 1.
 */
double avg_power(double x[], int n)
{
    double avg_pow = 0;
    for(int i=0; i<n; i++){
        avg_pow += pow(x[i],2);
    }
    return avg_pow/n;
}

/* Exercise 3. */

/* Return the largest of the n doubles in arr[]. 
 * This function assumes that parameter n is >= 1.
 */
double maxi(double arr[], int n)
{   
    double max = arr[0];
    for(int i=1; i<n; i++){
        //Check if value in array is greater than stored value
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

/* Exercise 4. */

/* Return the smallest of the n doubles in arr[]. 
 * This function assumes that parameter n is >= 1.
 */
double mini(double arr[], int n)
{
    double min = arr[0];
    for(int i=1; i<n; i++){
        //Check if value in array is smaller than stored value
        if(arr[i] < min){
            min = arr[i];
        }
    }
    return min;
}

/* Exercise 5. */

/* Normalize the n doubles in x[]. 
 * This function assumes that parameter n is >= 2, and that at least
 * two of the values in x[] are different.
 */
void normalize(double x[], int n)
{
    //Call other functions to find max and min in array
    double max = maxi(x, n);
    double min = mini(x, n);
    for(int i=0; i<n; i++){
        //Calculate normalized number and replace in array
        x[i] = (x[i]-min)/(max-min);
    }
}
