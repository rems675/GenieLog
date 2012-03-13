# ifndef _LONG_H_
# define _LONG_H_

# include <iostream>

# include "misc.h"

using namespace std;

class LongInt {

    public:

        LongInt();
        LongInt(int);

        void display();
        void echo();

        void add(LongInt &);
        void sub(LongInt &);

        void mul(LongInt &);
        void div(LongInt &);

        bool operator > (LongInt &);
        bool operator < (LongInt &);
        void operator = (LongInt &);

        void fact();

       ~LongInt();

    private:

        char * number;
        int size, stock;
        bool sign;

        void expand(int);

        void inc();
        void dec();

        void coreAdd(LongInt &);
        void coreSub(LongInt &);
        void coreMul(LongInt &, char, int);

};


# endif // _LONG_H_
