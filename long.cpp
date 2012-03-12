# include "long.h"

/**
 * \file    long.cpp
 * \brief   Implementation of LongInt class methods.
 * \author  Gigator & ouroumov
 * \version 0.1
 * \date    March 6 - 2012
 *
 */



/**
 * \fn      LongInt::LongInt()
 * \brief   Void state's constructor.
 *
 * Construct a LongInt object using input from stdin.
 *
 */
LongInt::LongInt() {

    /* Get input into buffer. */
    char buffer[4096];
    cin.getline(buffer,4096);
    size = cin.gcount();

    /* Initialize array of digits using the input buffer. */
    try {
        number = new char[size+32];
    } catch (...) {
        cerr << "Memory allocation exception raised" << endl ;
        return;
    }

    sign = false;
    if (buffer[0] == '-') {
        sign = true;
        buffer[0] = '0';
    }

    stock   = 32;
    number += 32;
    int i;
    for (i = size ; i >= 0 ; --i)
        number[i] = buffer[i];

    while (number[0] == '0') {
        ++stock;
        ++number;
        --size;
    }
}



/**
 * \fn      LongInt::LongInt(int n)
 * \brief   Alternate constructor.
 *
 * Construct an empty object with the capacity to store "n" digits.
 *
 */
LongInt::LongInt(int n) {
    number = new char[n+1];
    stock = n;
    size = 1;
    number += stock;
    sign = false;
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



/**
 * \fn      void LongInt::inc()
 * \brief   Incrementation routine.
 *
 * Increment local number by one.
 *
 */
void LongInt::inc() {
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
 * \fn      void LongInt::coreAdd(LongInt & N)
 * \brief   Core addition routine.
 *
 * Adds two numbers represented as arrays of characters by performing the
 * classical digit-by-digit algorithm. The number contained in the LongInt "N"
 * object is added to the local LongInt object.
 *
 */
void LongInt::coreAdd(LongInt & N) {
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
    /* Pḧase 2/3 : Depends on which number has the more digits. */
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



/**
 * \fn      void LongInt::coreSub(LongInt & N)
 * \brief   Core subtraction routine.
 *
 * Subtract the number contained in the "N" object to the local object. This is
 * done using the cassical "complement" algorithm. ( a - b = [a + c(b)] / 10 )
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


/**
 * \fn      void LongInt::mul(LongInt & N);
 * \brief   Multiplication routine.
 *
 * Mutiply local by the value of "N".
 *
 */
void LongInt::mul(LongInt & N) {
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

    if (stock <= N.size)
        expand(size + N.size);

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



/**
 * \fn      void LongInt::div(LongInt & N)
 * \brief   Division routine.
 *
 *
 *
 *
 *
 */
void LongInt::div(LongInt & N) {
    LongInt quotient(31);
    LongInt remainder(31);
}





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

void LongInt::operator = (LongInt & N) {
    number += size;
    stock += size;
    number -= N.size;
    stock -= N.size;
    size = N.size;
    int i = size;
    while (i--)
        number[i] = N.number[i];
}



















void LongInt::echo() { 
    cout << "stock : " << stock << 
            "\nsize : " << size << endl;
}













