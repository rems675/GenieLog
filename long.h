# ifndef _LONG_H_
# define _LONG_H_

# include <iostream>

# include "misc.h"

using namespace std;

class LongInt {

    public:

        LongInt();
       ~LongInt();

        void display();

        void add(LongInt &);
        void sub(LongInt &);

    private:

        char * number;
        int size, stock;
        bool sign;

        void expand(int);

        void coreAdd(LongInt &);
   //   void coreAdd(int *, int *, char *, int *, char *);

        void coreSub(LongInt &);
   //   void coreSub(int *, int *, char *, int *, char *);

   //   bool & operator > (LongInt &);
   //   bool & operator < (LongInt &);

};


# endif // _LONG_H_
