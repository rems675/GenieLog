# include <long.h>

/**
 * \file    LongInt.cpp
 * \brief   Implementation of LongInt class methods.
 * \author  Remy Saksik & Etienne Papegnies
 * \version 0.1
 * \date    March 27 - 2012
 *
 * This file contains the implementation for :
 *  
 * - The object constructor.
 * - A routine that loads an existing object from a source array of digits.
 * - A routine that handles expansion of the available memory space.
 * - The object destructor.
 *
 */



/**
 * \fn      LongInt::LongInt(int n)
 * \brief   Default constructor.
 *
 * Construct an empty object with the capacity to store "n" digits.
 * The parameter has a default value of DEFAULT_INIT_SIZE. (See LongInt.h)
 *
 */
LongInt::LongInt(int n) {
    setSafeMode();
    number = new char[n+1]; // The extra cell is needed for the EOS character.
    stock = n;
    number += stock;
    size = 1;
    sign = false;
}


/**
 * \fn      void LongInt::setSafeMode(bool isSafe_)
 * \brief   Set safety mode.
 *
 * isSafe determines whether or not a check is performed on input.
 * It's default value is DEFAULT_SAFETY_MODE. (See LongInt.h)
 * The default value is used in the constructor.
 *
 */
void LongInt::setSafeMode(bool isSafe_) { isSafe = isSafe_; }



/**
 * \fn      void LongInt::load(char * source, int length, bool Safe)
 * \brief   Loading routine.
 *
 * Loads an object with the content of a source array of digits.
 * Depending on the current safety mode, a check will be performed or not on
 * the source array.
 * 
 */
void LongInt::load(char * source, int length, const bool Safe) {

    // Check if memory reallocation is needed.
    if (size + stock <= length)
        expand(length);

    // Clear local object.
    stock  += size;
    number += size;

    stock  -= length+1;
    number -= length+1;
    size    = length+1;
    int i = length-1; // Array indice for the following loops.
    /* Safe mode: No check on the source array is needed. */
    if (isSafe) {
        while (i >= 0) {
            number[i] = source[i];
            --i;
        }
    }
    /* Unsafe mode: The source array is to be checked for illegal characters. */
    else {
        char temporary;
        while (i >= 0) {
            temporary = source[i];
            if (temporary >= '0' && temporary <= '9')
                number[i] = source[i];
            else {
                stock  += size;
                number += size;
                size = 1;
                cerr << "Illegal character on input stream. "
                        "Object set to zero." << endl;
                return;
            }
            --i;
        }
    }
}



/**
 * \fn      LongInt::~LongInt()
 * \brief   Object Destructor.
 *
 * Release dynamicaly allocated memory.
 *
 */
LongInt::~LongInt() { number -= stock; delete [] number; }



/**
 * \fn      void expand(int newSize)
 * \brief   Memory re-allocation routine.
 * 
 * Expands available storage space to 32 over the value specified in parameter.
 *
 */
void LongInt::expand(int newSize) {
    newSize += 32;
    try {
        char * tmp = new char[newSize];
        int oldStock = stock;
        stock += (newSize - (stock+size)); // Offset from size bump.
        tmp += stock;                      // Normal offset from stock.
        int i = size;
        while (i--)
            tmp[i] = number[i];            // Copy to new array.
        number -= oldStock;
        delete [] number;
        number = tmp;
    } catch (...) { cerr << "Memory allocation exception raised." << endl; }
}



