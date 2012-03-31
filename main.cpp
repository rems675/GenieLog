# include <long.h>


int main(void)
{
    
    cout << "a : " ;  LongInt a; a.read();

    //*
    cout << "b : " ;  LongInt b; b.read();

    LongInt i, j, k, l, m;

    i = a;
    j = a;
    k = a;
    l = a;
    m = a;

    cout << "add : "; i += b; i.display();
    cout << "sub : "; j -= b; j.display();
    cout << "mul : "; k *= b; k.display();
    cout << "div : "; l /= b; l.display();
    cout << "mod : "; m %= b; m.display();
    //*/
    return 0;

}

























