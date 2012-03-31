# include <long.h>


/**
 * \file    operators.cpp
 * \brief   Implementation of LongInt class overloaded operators.
 * \author  Remy Saksik & Etienne Papegnies
 * \version 0.1
 * \date    March 27 - 2012
 *
 * This file contains the implementation for the operators :
 * 
 *  >               +=      /=      *=              =
 *  <               -=      %=
 *
 */

bool LongInt::operator > (LongInt & N) {
    if (sign != N.sign)
        return N.sign;
    else {
        if (sign && __strcmp(number, size, N.number, N.size) == -1)
            return true;
        if (!sign && __strcmp(number, size, N.number, N.size) == 1)
            return true;
    }
    return false;
}

bool LongInt::operator < (LongInt & N) {
    if (sign != N.sign)
        return sign;
    else {
        if (sign && __strcmp(number, size, N.number, N.size) == 1)
            return true;
        if (!sign && __strcmp(number, size, N.number, N.size) == -1)
            return true;
    }
    return false;
}


void LongInt::operator = (LongInt & N) { load(N.number, N.size-1, true); }

void LongInt::operator += (LongInt & N) { add(N); }

void LongInt::operator -= (LongInt & N) { sub(N); }

void LongInt::operator *= (LongInt & N) { mul(N); }

void LongInt::operator /= (LongInt & N) { div(N); }

void LongInt::operator %= (LongInt & N) { mod(N); }

