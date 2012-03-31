# include <long.h>

/**
 * \file    compound.cpp
 * \brief   Implementation of LongInt class compound methods.
 * \author  Hamed Sargazi & Naïma El-Missouri
 * \version 0.1
 * \date    March 27 - 2012
 *
 */


/**
 * \fn      void LongInt::fact()
 * \brief   Factorial routine.
 *
 * Raises local to it's factorial.
 *
 */
void LongInt::fact() {
    LongInt N(0);
    N = (*this);
    N.dec();
    while (N.size > 1) {
        mul(N);
        N.dec();
    }
}

