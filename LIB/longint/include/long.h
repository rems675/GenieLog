# ifndef _LONG_H_
# define _LONG_H_

# include <iostream> 

# include "general.h"

# define DEFAULT_INIT_SIZE (32)
# define DEFAULT_SAFETY_MODE (false)

using namespace std;

class LongInt {

    public:

        LongInt(int = DEFAULT_INIT_SIZE);
        void setSafeMode(bool = DEFAULT_SAFETY_MODE);

        void display();

        void add(LongInt &);        void operator += (LongInt &);
        void sub(LongInt &);        void operator -= (LongInt &);
        void mul(LongInt &);        void operator *= (LongInt &);
        void div(LongInt &);        void operator /= (LongInt &);
        void mod(LongInt &);        void operator %= (LongInt &);

        bool operator > (LongInt &);
        bool operator < (LongInt &);
        void operator = (LongInt &);

        void fact();

       ~LongInt();

        char * echo();

        void read();

    private:

        char * number;
        int size, stock;
        bool sign;
        bool isSafe;


        void expand(int);

        void inc();
        void dec();

        void coreAdd(LongInt &);
        void coreSub(LongInt &);
        void coreMul(LongInt &, char, int);
        char coreDiv(LongInt &);

        void load(char *, int, const bool);
        void pushBack(char);
        void shift(int);

};


# endif // _LONG_H_
