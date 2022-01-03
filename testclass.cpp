
// #include <iostream>
// using namespace std;

// struct AA
// {
//     static void f(){ cout << "f\n"; }

// };

// void  g(){ cout << "g\n"; }
// int main()
// {
//     // void(*p)() = g;
//     // p();
//     void(*p)() = AA::f;
//     AA a;
    


// }


#include <iomanip> 
#include <iostream> 
using namespace std; 
class Base { public:Base(int i) { cout << i << "BASE\n"; }
~Base () { } };

class Base1: virtual public Base { 
    public:Base1(int i, int j=0) : Base(j) { cout << i << "BASE!\n"; } ~Base1() {} };

class Base2: virtual public Base { 
    public:Base2(int i, int j=0) : Base(j) { cout << i << "BASE2\n"; } ~Base2() {} };
    
class Derived :  public Base2, public Base1 { 
    public:Derived(int a, int b, int c, int d) : 
    mem1(a), mem2(b),Base2(d), Base1(c), Base(a) { cout << b; } 
    
    private:Base2 mem2; Base1 mem1; };
    
int main() {
    Derived d(1,2,3,4);
}

