# include "long.h"

/**
 * \file    sub.cpp
 * \brief   Implementation of LongInt class methods.
 * \author  Remy Saksik & Etienne Papegnies
 * \version 0.1
 * \date    March 27 - 2012
 *
 * This file contains the implementation for :
 *
 * - The decrementation routine. 
 * - The subtraction wrapper routine. 
 * - The subtraction routine.
 *
 */



/**
 * \fn      void LongInt::dec()
 * \brief   Decrementation routine.
 *
 * Decrement the local number by one.
 *
 */
void LongInt::dec() {

    if (size < 2) { inc(); sign = true; return; }

    if (sign) { sign = false; inc(); sign = true; return; }

    char carry = 1;
    for (int i = size - 2 ; i >= 0 ; --i) {
        if (carry) {
            if (number[i] == '0')
                number[i] = '9';
            else {
                --number[i];
                carry = 0;
            }
        }
        else
            break;
    }
    if (number[0] == '0') {
        ++number;
        ++stock;
        --size;
    }
}





/**
 * \fn      void LongInt::sub(LongInt & N)
 * \brief   coreSub() routine wrapper.
 *
 * Handle request for memory re-allocation if needed and decide if the operation
 * to perform is really a subtraction or an addition.
 *
 */
void LongInt::sub(LongInt & N) {
    if (size+stock <= N.size)
        expand(N.size);

    if (sign != N.sign)
        // (-a) - (+b) ->  -(a+b)
        // (+a) - (-b) ->  +(a+b)
        coreAdd(N);
    else
        // (-a) - (-b) ->  -(a-b)
        // (+a) - (+b) ->  +(a-b)
        coreSub(N);
}



/**
 * \fn      void LongInt::coreSub(LongInt & N)
 * \brief   Core subtraction routine.
 *
 * Subtract the number contained in the "N" object to the local object. This is
 * done using the classical "complement" algorithm. ( a - b = [a + c(b)] / 10 )
 *
 */
void LongInt::coreSub(LongInt & N) {
    /* Step 0 : Handles operations with "zero" parameters. */
    if (N.size < 2)
        return;
    if (size < 2) {
        sign = !N.sign;
        size = N.size;
        number -= size;
        stock -= size;
        for (size  ; size >= 0 ; --size)
            number[size] = N.number[size];
        size = N.size;
        return;
    }
    /* Step 1 : Determines which number is bigger & Initialize. */
    // So that we can deal with both cases at once, we'll attach some alias to
    //  the two array of digits, depending on which one's the biggest one.
    int max =   size;    char * big   =   number;
    int min = N.size;    char * small = N.number;
    if (__strcmp(number, size, N.number, N.size) == -1) {
        sign = !sign;
        min =   size;   small =   number;
        max = N.size;   big   = N.number;
    }

    min -= 2;           // Ditch EOS.
    max -= 2;

    big    += max;      // Align last char before EOS.
    small  += min;
    number += (size - 2);

    stock += size;      // Updates values for stock and size.
    stock -= max + 2;
    size = max + 2;

    max = max - min;    // max == number of extra digits in the longest array.


    char tmp;           // Will be used for temporary storage of digits.
    char carry;

    /* Step 2 : Find the first non-zero digit in the smallest array. */
    while (small[0] == '0') {
        number[0] = big[0];
        --min;
        --small;
        --big;
        --number;
    }
    tmp = 58 - small[0];// tmp is now small's digit Ten-complement.
    tmp += big[0];
    if (tmp > 57) {
        tmp -= 10;
        carry = 1;
    }
    else
        carry = 0;

    number[0] = tmp;    // The target array is always the local one.

    --min;              // Go to next digit.
    --small;            //
    --big;              //
    --number;           //

    /* Step 3 : Compute & add niner-complements. */
    for (min ; min >= 0 ; --min) {
        tmp = 57 - small[0];    // tmp is now small's digit niner-complement.
        tmp += (big[0] + carry);
        if (tmp > 57) {
            tmp -= 10;
            carry = 1;
        }
        else
            carry = 0;
        number[0] = tmp;
        --small;
        --big;
        --number;
    }

    /* Step 4 : The smallest array was done in. Assume 9 as complement. */
    for (max ; max > 0 ; --max) {
        tmp = big[0] + 9 + carry;
        if (tmp > 57) {
            tmp -= 10;
            carry = 1;
        }
        else
            carry = 0;
        number[0] = tmp;
        --big;
        --number;
    }

    /* Step 5 : Completion. Update stock and size values. */
    ++number;   // Because of last hop in the previous loop.
    while (number[0] == '0') {  // Skip leading zeros.
        ++stock;
        ++number;
        --size;
    }
}


