# ifndef _LONG_H_
# define _LONG_H_

# include <iostream>

using namespace std;

class LongInt {

    public:

        LongInt();
       ~LongInt();

        void display();

        void add(LongInt &);
        void sub(LongInt &);
        void expand(int);

    private:

        char * number;
        int size, stock;
        bool sign;


        void coreAdd(LongInt &);
   //   void coreAdd(int *, int *, char *, int *, char *);

        void coreSub(LongInt &);
   //   void coreSub(int *, int *, char *, int *, char *);

   //   bool & operator > (LongInt &);
   //   bool & operator < (LongInt &);

};


# endif // _LONG_H_
