# include <iostream>

using namespace std;

char * coreAdd(char * left, int sizeOfLeft, char * right, int sizeOfRight) {

    /* Determine wich number is longer. */
    int min = sizeOfRight; char * small = right;
    int max = sizeOfLeft;  char * big   = left;
    if (max < min) {
        max = min;        big   = small;
        min = sizeOfLeft; small = left;
    }

    /* Allocate space to store the result. */
    char * result;
    try {
        result = new char[max+1];
    }
    /* Exception handling: Round two. */
    catch (...) { return NULL; }

    /* Now Starts the fun part! */
    char carry = 0;

    result++;
    result[max] = 0; --min; --max;


    for (min ; min >= 0 ; --min, --max) {
        result[max] = big[max] + small[min] - '0' + carry;
        carry       = result[max] / ('9'+1);
        result[max] = result[max] % ('9'+1);
        if (carry)
            result[max] = result[max] + '0';       
    }


    for (max ; max >= 0 ; --max) {
        result[max] = big[max] + carry;
        carry       = result[max] / ('9'+1);
        result[max] = result[max] % ('9'+1);
        if (carry)
            result[max] = result[max] + '0';
    }

    result--;
    if (carry) {
        result[0] = carry + '0';
    }
    else
        result[0] = '0';
    return result;
}

int main(void)
{

    char left[100];
    cout << "Input first number : " ; cin.getline(left, 100);
    int leftSize = cin.gcount(); 

    char right[100];
    cout << "Input second number : " ; cin.getline(right,100);
    int rightSize = cin.gcount();

    char * res = coreAdd(left,leftSize,right,rightSize);
    cout << res << endl;
}

