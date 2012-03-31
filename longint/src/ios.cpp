# include <long.h>

/**
 * \file    ios.cpp
 * \brief   Implementation of LongInt class methods.
 * \author  Remy Saksik & Etienne Papegnies
 * \version 0.1
 * \date    March 27 - 2012
 *
 */


/**
 * \fn      void LongInt::display()
 * \brief   Display routine.
 *
 * Displays the number on standard output, with eventual sign prefix.
 *
 */
void LongInt::display() { 
    if (size < 2) {
        cout << "0" << endl ;
        return;
    }
    if (sign) 
        cout << "-" ;
    cout << number << endl ;
}


void LongInt::read() {

    /* Get input into buffer. */
    char buffer[4096];
    cin.getline(buffer,4096);

    /* Initialize array of digits using the input buffer. */
    
    load(buffer, cin.gcount()-1, isSafe);

    while (number[0] == '0') {
        ++stock;
        ++number;
        --size;
    }

}
