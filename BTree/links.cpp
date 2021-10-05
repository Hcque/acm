
// passed
//	Accepted	509 ms

// node first
// assign constry, stack value avoids deconstructor

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5+10;

#define NODE Node<Entry> 

template <class Entry>
struct Node
{
    Entry data;
    NODE *next;
    Node() {}
    Node(Entry x, NODE* _n = nullptr): data(x), next(_n) {}
};


template <class Entry>
class MStack{
public:
    MStack(){ top == NULL; }
    ~MStack()
    {
        if (!empty()) pop();
    }

    MStack(const MStack& copy)
    {
        if (copy.empty()) top = nullptr;
        else{
            NODE *cur = copy.top, *newcur;
            top = newcur = new NODE(cur->data); 
            while (cur->next){
                cur = cur->next;
                newcur->next = new NODE(cur->data);
                newcur = newcur->next;
            }
        }
    }

    void operator=(const MStack& copy)
    {
        while (!empty()) pop();
        auto tmp(copy);
        top = tmp.top;
        tmp.top = 0;
    }
    bool empty() const { return top == nullptr;  }
    void push(const Entry &x)
    {
        NODE *cur = new NODE(x, top);
        top = cur;
    }
    void pop()
    {
        if (!empty())
        {
            NODE* tmp = top;
            top = top->next;
            delete tmp;
        }

    }
    Entry topX() const
    {
        if (!empty() )
        {
            return top->data;
        }
    }

protected:
    NODE* top;
};

MStack<int> stk;
MStack<int> stk2;

int n;
int main()
{
    cin >> n;
    while (n--)
    {
        string op;
        cin >> op;
        int x;
        if (op == "push"){
            cin >> x;
            stk.push(x);
        }
        else if (op == "pop"){
            // stk2 = stk;
            stk.pop();
        }
        else if (op == "empty") {
            // stk = stk2;
            if (!stk.empty()) cout << "NO" << endl;
            else cout << "YES" << endl;
        }
        else {

            stk2 = stk;
            cout << stk2.topX() << endl;
        }
    }
    
    
    
}