# include <iostream>

using namespace std;

char * coreAdd(char * left, int sizeOfLeft, char * right, int sizeOfRight) {

    /* [ Determine which number is longer. ]
     * For visibility's sake, I'm aliasing "min" and "max" to the corresponding
     * values from "sizeOfLeft" and "sizeOfRight".
     * For the same reason I'm aliasing the pointers "small" and "big" to the
     * "left" and "right" array of characters.
     */
    int min = sizeOfRight; char * small = right;
    int max = sizeOfLeft;  char * big   = left;
    if (max < min) {
        max = min;        big   = small;
        min = sizeOfLeft; small = left;
    }


    /* [ Allocate space to store the result. ]
     * The result array of characters needs to have one more cell than the
     * bigger between right and left, so that's one more than "max".
     * 9 + 9 -> 18
     * 9 + 1 -> 10
     * The allocation itself needs to be nested in a try block to provide
     * exception handling when not enough space is available.
     */
    char * result;
    try {
        result = new char[max+1];
    }
    catch (...) { return NULL; } // This catches any exception and return NULL.


    /* [ Initialize. ] 
     * - Of course the carry needs to be 0 when first entering the loop.
     * - Also, we'll use "max" to address both the current value inside of "big"
     * and the current cell in the result array.
     * Because the result array has "max+1" cells, to access the right one using
     * the value of "max" we can either evaluate "max+1" each time we need it,
     * or save ourselves a considerable number of operations by adding "1" to
     * the value pointed by "result". (The same way we would move %edi by one 
     * char in assembly using "addb $1,%edi")
     * - Finally, the last cell of each array holds the "End Of String"
     * character: '\0' which value is "0". We need to set the last cell of the
     * result array with that same value for various reasons. 
     * (i.e: Use with "cout".)
     */
    char carry = 0;
    ++result;
    result[max] = 0; --min; --max;

    /* Now let's get to work people! */

    /* [ Phase 1/3 ]
     * We have to sum the values contained in the cells of the small and big
     * arrays, and store the result in the "result" array.
     * At each step we also need to add the carry.
     *
     *      Example 1:
     *      '1' + '2' = 49 + 50 =  99
     *                            -48
     *                           = 51 = '3'
     *      (Hence the - '0' below, because '0' = 48) (#1)
     *
     *      Example 2:
     *      '9' + '3' = 57 + 51 = 108
     *                            -48
     *                           = 60 = '<' --> 60 / 58 = 1 ( carry )
     *                                      --> 60 % 58 = 2 ( reminder )
     *      (Hence the '9'+1 below, because '9'-1 = 58) (#2)
     *
     * When a carry is produced, the reminder needs to be added 48 again to
     * match the character corresponding. (#3)
     * In the second example above, the reminder is 2. But the character of
     * value 2 is '2'. and '2' = 50 = 2 + 48
     */
    for (min ; min >= 0 ; --min, --max) {
        result[max] = big[max] + small[min] - '0' + carry; // (#1)
        carry       = result[max] / ('9'+1);  // (#2)
        result[max] = result[max] % ('9'+1);
        if (carry)       // (#3)
            result[max] = result[max] + '0';
    }


    /* [ Phase 2/3 ]
     * It's exactly the same principle as in phase 1, except we're done with
     * the small array, so we only need to propagate the carry on the values
     * from the big array.
     */
    for (max ; max >= 0 ; --max) {
        result[max] = big[max] + carry;
        carry       = result[max] / ('9'+1);
        result[max] = result[max] % ('9'+1);
        if (carry)
            result[max] = result[max] + '0';
        else
            while (max--)
                result[max] = big[max];
    }


    /* [ Phase 3/3 ]
     * The work is almost done.
     * The last operation may have raised a carry, in which case we need to set
     * the value of the first cell of our array with the character '1'.
     * But to access the cell of indice zero in our array, we first need to
     * switch back the pointer from one char so as to undo what was done during
     * initialization.
     */
    --result;
    if (carry)
        result[0] = '1';
    else
        result[0] = '0';


    /* [ Completion. ]
     * Return the pointer on the array with the result.
     * A problem with this algorithm is the leading zero when the last
     * addition fails to raise a carry.
     */
    return result;
}

void myCopy(const char * source, char * target) {
    int i = 0;
    while (source[i])
        target[i++] = source[i];
    target[i] = 0;
}

int main(void)
{

    char left[100];
    cout << "Input first number : " ; cin.getline(left, 100);
    int leftSize = cin.gcount(); 
   /*myCopy("99999999999199",left);
     int leftSize = 15;
    */
    char right[100];
    cout << "Input second number : " ; cin.getline(right,100);
    int rightSize = cin.gcount();
   /*myCopy("1",right);
     int rightSize = 2;    
    */

    char * res = coreAdd(left,leftSize,right,rightSize);
    cout << res << endl;
}

