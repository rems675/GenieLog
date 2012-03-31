# include <long.h>

/**
 * \file    add.cpp
 * \brief   Implementation of LongInt class methods.
 * \author  Remy Saksik & Etienne Papegnies
 * \version 0.1
 * \date    March 27 - 2012
 *
 * This file contains the implementation for :
 * 
 * - The incrementation routine. 
 * - The addition wrapper routine. 
 * - The addition routine.
 *
 */



/**
 * \fn      void LongInt::inc()
 * \brief   Incrementation routine.
 *
 * Increment the local number by one.
 *
 */
void LongInt::inc() {

    if (size < 2) { sign = false; }

    if (sign) { sign = false; dec(); sign = true; return; }

    if (!stock)
        expand(size);

    char carry = 1;
    for (int i = size - 2 ; i >= 0 ; --i) {
        if (carry) {
            carry += number[i];
            if (carry > 57) {
                carry -= 10;
                number[i] = carry;
                carry = 1;
            }
            else {
                number[i] = carry;
                carry = 0;   
            }
        }
        else
            break;
    }
    if (carry) {
        --number;
        --stock;
        ++size;
        number[0] = '1';
    }
}



/**
 * \fn      void LongInt::add(LongInt &)
 * \brief   coreAdd() routine wrapper.
 *
 * Handle request for memory re-allocation if needed and decide if the operation
 * to perform is really an addition or a subtraction.
 *
 */
void LongInt::add(LongInt & N) {
    if (size+stock <= N.size) // We need to expand local storage space.
        expand(N.size);

    if (sign == N.sign)   
        // (-a) + (-b) ->  -(a+b)
        // (+a) + (+b) ->  +(a+b)
        coreAdd(N);
    else
        // (-a) + (+b) ->  -(a-b)
        // (+a) + (-b) ->  +(a-b)
        coreSub(N);
}



/**
 * \fn      void LongInt::coreAdd(LongInt & N)
 * \brief   Core addition routine.
 *
 * Adds two numbers represented as arrays of characters by performing the
 * classical digit-by-digit algorithm. The number contained in the LongInt "N"
 * object is added to the local LongInt object.
 *
 */
void LongInt::coreAdd(LongInt & N) {
    if (N.size < 2)
        return;

    /* Initialization : Find out which number has max or min length. */
    int min = N.size;
    int max = size;
    if (max < min) {
        max = N.size;
        min = size;
    }

    max -= 2;   // Ditch EOS & Account for zero-based indices.
    min -= 2;

    char carry = 0;
    char * distant = N.number;
    char * local = number;
    distant += N.size - 2;
    local   +=   size - 2;

    /* Phase 1/3 : Sum digits of distant with digits of local. */
    max = max - min;
    for (min ; min >= 0 ; --min) {
        local[0] = local[0] + distant[0] - '0' + carry;
        if (local[0] > 57) {
            local[0] -= 10;
            carry = 1;
        }
        else
            carry = 0;
        --local;
        --distant;
    }
    /* Phase 2/3 : Depends on which number has the more digits. */
    if (N.size <= size) {
        // Local has more digits: We have to propagates the carry over local's
        //  remaining digits and stop as soon as there is no more carry.
        for (max ; max > 0 ; --max) {
            if (carry) {
                if (local[0] == '9') { 
                    local[0] = '0';
                }
                else {
                    local[0] += 1;
                    carry = 0;
                }
                --local;
            }
            else
                break;
        }
    }
    else {
        // Distant has more digits: We have to propagates the carry over
        //  distant's digits and then copy to local. As soon as there is no more
        //  carry, we just have to copy leftover digits from distant to local.
        stock -= max;   // Local stock is reduced by the number of extra digits.
        size += max;    // Local size is bumped by the number of extra digits.
        number -= max;
        for (max ; max > 0 ; --max) {
            if (carry) {
                if (distant[0] == '9')
                    local[0] = '0';
                else {
                    local[0] = distant[0] + 1;
                    carry = 0;
                }
            }
            else {
                local[0] = distant[0];
            }
            --local;
            --distant;
        }
    }
    /* Phase 3/3 : Completion: Check if phase 2 ended with a carry. Update stock
       and size accordingly. */
    if (carry) {
        local[0] = '1';
        --stock; ++size; --number;
    }
}


