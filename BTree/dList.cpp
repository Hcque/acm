#include <iostream>
using namespace std;


#define NODE Node<Record>

template <class Record>
struct Node{
    Record data;
    NODE *l,*r;
    Node() {}
    Node(Record _d, NODE* _l=nullptr, NODE* _r=nullptr) : data(_d),
                l(_l), r(_r) {}
};

template <class Record>
class DList 
{
public:
    DList() {
        head = new NODE(-1);
        tail = new NODE(-1);
        head->r = tail; tail->l = head;
        sz = 0;
    }

    DList(const DList& copy)
    {
        head = new NODE(-1);
        tail = new NODE(-1);
        head->r = tail; tail->l = head;
        sz = 0;
        if (copy.empty()) return;

        NODE* old_p = copy.head->r;
        NODE* new_p = head;
        while (old_p)
        {
            insert_right(new_p,old_p->data);
            new_p = new_p->r;
            old_p = old_p->r;
        }
        
    }
    void operator=(const DList& copy)
    {
        clear();
        auto tmp(copy);
        head = tmp.head; tail = tmp.tail; sz = tmp.sz;
        tmp.head = tmp.tail = nullptr;
    }

    virtual ~DList() { clear(); }

    void clear()
    {
        for (NODE* now=head; now ; now = now->r)
        {
            NODE* tmp = now;
            delete tmp; tmp = 0;
        }
        head = tail = nullptr;
        sz = 0;
    }

    void push(const Record& new_entry)
    {
        insert_right(tail->l, new_entry);
    }
    void pop()
    {
        if (!empty())
            remove(head->r);
    }
    Record top()
    {
        if (!empty())
            return head->r->data;
    }

    bool empty() const { return sz == 0; }
private:
    void insert_right(NODE* now, const Record& new_entry)
    {
        NODE* tmp = new NODE(new_entry);
        tmp->r = now->r; tmp->r->l = tmp;
        tmp->l = now; now->r = tmp;
        sz++;
    }
    void remove(NODE* now)
    {
        NODE* todel = now;
        now->l->r = now->r;
        now->r->l = now->l;
        delete todel;
        sz--;
    }

    size_t sz;
    NODE *head, *tail;
};

int n;

DList<int> que, que2;

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