#include <iostream>

using namespace std;

class A
{
    public:
    void foo(){ cout << "A foo" << endl; }
    virtual void bar(){ cout << "A bar" << endl; }
};


class B: public A
{
    public:
    void foo(){ cout << "B foo" << endl; }
    void bar(){ cout << "B bar" << endl; }
};

int main()
{
    A a;
    B b;
    B* p = (B*)&a;
    p->foo();
    p->bar();


}
