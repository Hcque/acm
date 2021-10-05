// assighn oper clear first
// front rear pop last

// since using push, set fornt = null

// 	Accepted	500 ms

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
    Node(Entry x, NODE* _n  = nullptr): data(x), next(_n) {}
};


template <class Entry>
class MQueue
{
public:
    MQueue(){
        front = rear = nullptr;
    }
    MQueue(const MQueue& copy){
        front = rear = nullptr;
        if (copy.empty()) return;
        else{
           NODE *oldcur = copy.front;
           for (;oldcur;oldcur=oldcur->next)
               push(oldcur->data);
        }
    }

    void operator=(const MQueue& copy){
        while (!empty()) pop();
        MQueue<Entry> tmp(copy);
        front = tmp.front;
        rear = tmp.rear;
        tmp.front = tmp.rear = 0;
    }

    ~MQueue(){ while (!empty()) pop(); }

    bool empty() const { return front == nullptr; }
    void push(const Entry &x)
    {
        NODE* tmp = new NODE(x);
        if (rear == nullptr) front = rear = tmp;
        else{
            rear->next = tmp;
            rear = rear->next;
        }
    }
    void pop(){
        if (!empty())
        {
            NODE *tmp = front;
            front = front->next;
            if (front == nullptr) rear = front; // caation!
            delete tmp;
        }
    }
    Entry top() const{
        return front->data;
    }
protected:
    NODE *front, *rear;

};


int n;

MQueue<int> que, que2;

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
            que.push(x);
        }
        else if (op == "pop"){
            que.pop();
        }
        else if (op == "empty") {
            if (!que.empty()) cout << "NO" << endl;
            else cout << "YES" << endl;
        }
        else {
            que2 = que;
            cout << que2.top() << endl;
        }
    }
    
    
    
}



