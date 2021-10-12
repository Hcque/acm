
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5+10;


#define NODE Node<Record>

template <class Record>
struct Node
{
    Record data;
    NODE *next;
    Node(){}
    Node(const Record& _d, NODE* _n=nullptr):data(_d), next(_n) {}
};

template <class Record>
class MQueue
{
public:
    MQueue(){ front = rear = nullptr; }
    MQueue(const MQueue& copy)
    {
        front = rear = nullptr;
        if (copy.front == nullptr) return;
        NODE* cur = copy.front;
        while (cur)
        {
            push(cur->data);
            cur = cur->next;
        }
    }
    void operator=(const MQueue& copy)
    {
        while (!empty()) pop();
        MQueue<Record> tmp(copy);
        front = tmp.front; rear = tmp.rear;
        tmp.front = tmp.rear = nullptr;
    }
    ~MQueue() {while (!empty()) pop(); }
    void push(const Record& target)
    {
        if (rear == nullptr) front = rear = new NODE(target);
        else{
            rear->next = new NODE(target);
            rear = rear->next;
        }
    }

    void pop()
    {
        if (empty()) return;
        if (front == rear) {
            delete rear;
            front = rear = nullptr;
        }
        else{
            NODE* tmp = front;
            front = front->next;
            delete tmp;
        }
    }
    bool empty()const{ return rear == nullptr; }
    Record top() const
    {
        if (!empty()) return front->data;
    }


protected:
    NODE* front, *rear;
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


