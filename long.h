# ifndef _LONG_H_
# define _LONG_H_

# include <iostream>

# include "misc.h"

using namespace std;

class LongInt {

    public:

        LongInt();
        LongInt(int);
       ~LongInt();

        void display();
        void echo();

        void inc();
        void dec();

        void add(LongInt &);
        void sub(LongInt &);
        void mul(LongInt &);
        void div(LongInt &);

        bool operator > (LongInt &);
        bool operator < (LongInt &);
        void operator = (LongInt &);

    private:

        char * number;
        int size, stock;
        bool sign;

        void expand(int);

        void coreAdd(LongInt &);
   //   void coreAdd(int *, int *, char *, int *, char *);

        void coreSub(LongInt &);
   //   void coreSub(int *, int *, char *, int *, char *);

        void coreMul(LongInt &, char, int);

};


# endif // _LONG_H_
