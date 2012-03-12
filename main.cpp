# include "long.h"


int main(void)
{

    //*
    cout << "a : " ;  LongInt a; 
    cout << "b : " ;  LongInt b;


    a.inc();

    cout << "a -> " ; a.display();

    //*

    a.mul(b);
    a.display();

    cout << "(a > b) ? -- ";
    if (a > b)
        cout << "yes" << endl;
    else
        cout << "no" << endl;

    cout << "(a < b) ? -- ";
    if (a < b)
        cout << "yes" << endl;
    else
        cout << "no" << endl;

    a.sub(b); cout << "a -> " ; a.display();
    a.sub(b); cout << "a -> " ; a.display();
    a.add(b); cout << "a -> " ; a.display();
    a.add(b); cout << "a -> " ; a.display();
    b.add(a); cout << "b -> " ; b.display();

    for (int i = 0 ; i < 1000000 ; ++i)
        a.add(b);


    cout << "a -> " ; a.display();
    cout << "b -> " ; b.display();

    a.mul(b);
    a.display();


    //*/

    return 0;

}


