# include <long.h>

/**
 * \file    div.cpp
 * \brief   Implementation of LongInt class methods.
 * \author  Remy Saksik & Etienne Papegnies
 * \version 0.1
 * \date    March 27 - 2012
 *
 * This file contains the implementation for :
 *  
 * - The function that divide a number that's less than 10 times local and
 *    outputs the result as a character.
 * - The routine that pushes a character at the back of an existing object.
 * - A routine that shifts an existing object by adding zeros to the end.
 * - The division routine. 
 * - The modulo routine. (Very similar to the division.)
 *
 */



/**
 * \fn      char LongInt::coreDiv(LongInt & N)
 * \brief   Core division routine.
 * \return  A character representing the result of the division.
 *
 * Handle the division of the calling object by the distant object passed as 
 * parameter. The local object must be no more than ten times the parameter.
 *
 */
char LongInt::coreDiv(LongInt & N) {
    char quotient = '0';
    while (!((*this) < N)) {
        sub(N);
        ++quotient;
    }
    return quotient;
}



/**
 * \fn      void LongInt::pushBack(char digit)
 * \brief   Append a digit.
 *
 * "digit" is pushed as the last digit of the local number.
 *
 */
void LongInt::pushBack(char digit) {
    /* Checking available memory and requesting more if needed. */
    if (stock == 0) expand(size);
    /* Copying each digit if the cell to it's left. */
    --number;
    --stock;
    for (int i = 0 ; i < size ; ++i)
        number[i] = number[i+1];
    /* Completion: Write the digit, and update size. */
    number[size-1] = digit;
    ++size;
}



/**
 * \fn      void LongInt::shift(int offset)
 * \brief   Shift the object.
 *
 * The local object is shifted from "offset" by adding that number of zeros to
 * the end of the number.
 *
 */
void LongInt::shift(int offset) {
    /* Checking available memory and requesting more if needed. */
    if (stock <= offset) expand(offset);
    /* Copying each digit "offset" cells to it's left. */
    number -= offset;
    stock  -= offset;
    int i;
    for (i = 0 ; i < size-1 ; ++i)
        number[i] = number[i+offset];
    /* Filling the "offset" rightmost digits with zeros and updating size. */
    for (i = size-1 ; i < size-1+offset ; ++i)
        number[i] = '0';
    size   += offset;
}



/**
 * \fn      void LongInt::div(LongInt & N)
 * \brief   Division routine.
 *
 * Set local with the quotient of local divided by N.
 * This is the naïve "Long Division" grade school algorithm.
 *
 */
void LongInt::div(LongInt & N) {
    if (N.size < 2) {
        cerr << "Div by zero except" << endl;
        return;
    }
    else {
        LongInt temporary(31);
        LongInt temp(31);
        LongInt Quotient(31);
        char partialQuotient;
        int w;
        bool exit = false;
        while (size >= N.size) {

            // Select target area.
            w = N.size - 1;
            temporary.load(number, w, true);
            if (temporary < N) {
                if (size == N.size)
                    break;
                temporary.load(number, ++w, true);
                if (size - 1 == N.size) 
                    exit = true;
            }
            // Execute sub division function.
            partialQuotient = temporary.coreDiv(N);

            // Push the result on the back of what we'll output.
            temp.sub(temp);
            temp.pushBack(partialQuotient);
            temp.shift((size-1) - w);
            Quotient.add(temp);

            // Rewrite the affected area with the updated value.
            // The updated value is the remainder for the sub div.

            number += w;
            stock  += w;
            size   -= w;
            int i = temporary.size-1;
            number -= i;
            stock  -= i;
            size   += i;
            while (i-- > 0)
                number[i] = temporary.number[i];
            if (exit)
                break;
        }
        (*this) = Quotient;
    }
}



/**
 * \fn      void LongInt::mod(LongInt & N)
 * \brief   Division routine - Remainder.
 *
 * Set local with the remainder of local divided by N.
 * Implements the very same algorithm than the div routine, except the local
 * value doesn't get updated with the result at the end. So we don't care about
 * actually computing the quotient.
 *
 */
void LongInt::mod(LongInt & N) {
    if (N.size < 2) {
        cerr << "Div by zero except" << endl;
        return;
    }
    else {
        LongInt temporary(31);
        int w;
        bool exit = false;
        while (size >= N.size) {

            // Select target area.
            w = N.size - 1;
            temporary.load(number, w, true);
            if (temporary < N) {
                if (size == N.size) {
                    exit = true;
                    break;
                }
                temporary.load(number, ++w, true);
                if (size - 1 == N.size)
                    exit = true; 
            }
            // Execute sub division function.
            temporary.coreDiv(N);

            // Rewrite the affected area with the updated value.
            // The updated value is the remainder for the sub div.
            number += w;
            stock  += w;
            size   -= w;
            int i = temporary.size-1;
            number -= i;
            stock  -= i;
            size   += i;
            while (i-- > 0)
                number[i] = temporary.number[i];
            if (exit)
                break;
        }
    }
}

