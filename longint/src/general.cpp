# include "general.h"

/**
 * \file    general.cpp
 * \brief   Implementation of miscellaneous functions.
 * \author  Remy Saksik
 * \version 0.1
 * \date    March 6 - 2012
 *
 */



int __strcmp(char * & left, int & sizeOfLeft, char * & right, int & sizeOfRight)
{
    if (sizeOfLeft > sizeOfRight)  // We check if the left number is longer.
        return 1;
    if (sizeOfLeft < sizeOfRight)  // We check if the right number is longer.
        return -1;
    
    // While the current digits are equals and we haven't run through the whole 
    //  string we keep checking the next digits.

    int i = 0;
    while ((left[i] == right[i]) && (i != sizeOfLeft-1)) 
        i++;

    // Now differents digits have been found, or we're at the end of the string.
    if (left[i] > right[i]) // Current digit of left is bigger: Left is bigger.
        return 1;
    if (left[i] < right[i]) // Reverse... Right is bigger.
        return -1;
    return 0;               // Left equals Right.
}
