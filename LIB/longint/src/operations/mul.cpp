# include <long.h>

/**
 * \file    mul.cpp
 * \brief   Implementation of LongInt class methods.
 * \author  Remy Saksik & Etienne Papegnies
 * \version 0.1
 * \date    March 27 - 2012
 *
 * This file contains the implementation for :
 *  
 * - The multiplication routine. 
 * - The single digit multiplication routine.
 *
 */


/**
 * \fn      void LongInt::mul(LongInt & N);
 * \brief   Multiplication routine.
 *
 * Mutiply local by the value of "N".
 *
 */
void LongInt::mul(LongInt & N) {
    if (size < 2) return;
    if (N.size < 2) {
        number += size;
        stock += size;
        size = 1;
        return;
    }
    if (sign != N.sign)
        sign = true;
    else if (sign && N.sign)
        sign = false;

    LongInt temporary(size + N.size);
    LongInt result(size + N.size);

    int i, j;
    char digit;
    for (i = N.size - 2, j = 0 ; i >= 0 ; --i, ++j) {
        digit = N.number[i];
        if (digit != '0') {
            coreMul(temporary, digit, j);
            result.add(temporary);
        }
    }

    (*this) = result;

}



/**
 * \fn      void LongInt::coreMul(LongInt & target, char digit, int offset)
 * \brief   Core multiplication routine.
 *
 * Load the "target" object with the correctly offseted result of the
 * multiplication of local by "digit".
 *
 */
void LongInt::coreMul(LongInt & target, char digit, int offset) {
    digit -= '0';
    target.number += target.size; // Clear. 
    target.stock  += target.size;
    target.stock  -= (size + offset);
    target.size    = (size + offset);
    int i;      // Loop counter.
    char tmp;   // For temporary storage of digits.
    char carry = 0;
    /* Add "offset" zeros to the end of the target array. */
    target.number -= 2;
    for (i = offset ; i > 0 ; --i) {
        target.number[0] = '0';
        --target.number;
    }
    /* Do the multiplication while proparating the carry. */
    for (i = size - 2 ; i >= 0 ; --i) {
        tmp = number[i];
        tmp -= '0';
        tmp *= digit;
        tmp += carry;
        if (tmp > 9) {
            carry = tmp / 10;
            tmp   = tmp % 10;
        }
        else
            carry = 0;
        tmp += '0';
        target.number[0] = tmp;
        --target.number;
    }
    /* Check if the last operation raised a carry and handle it if it did. */
    ++target.number;
    if (carry) {
        --target.number;
        --target.stock;
        ++target.size;
        target.number[0] = carry + '0';   
    }
}

