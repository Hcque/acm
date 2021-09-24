

#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

const int N = 1e5+10;
int n;
int k,x;
class List{
public:

    struct Node{
    Node *l,*r;
    int e, id;
    Node(){}
    Node(Node* L, Node* R, int E, int ID):l(L), r(R), e(E), id(ID) {}
    
    };

    map<int, Node*> mm;
    Node *head, *tail;
    int idx;
    List() {
        head = new Node(0,0,0,0);
        tail = new Node(0,0,0,1);
        head->r = tail;
        tail->l = head;
        mm[0] = head;
        mm[1] = tail;
        idx = 2;
    }
    
    void clear(){
        Node *p1 = head, *p2;
        while (p1) {
            p2 = p1;
            p1 = p1->r;
            delete p2;
            p2 = 0;
        }
        mm.clear();
    }
    ~List(){
        clear();
        head = tail = 0;
        idx = 0;
    }
    
    void insert(int k, int x){
        Node* prev = findk(k);
        Node* tmp = new Node(prev,prev->r,x, idx);
        tmp->r->l = tmp;
        tmp->l->r = tmp;
        mm[idx++] = tmp;
    }
    
    void del(int k)
    {
        Node* prev = findk(k);
        prev->r->l = prev->l;
        prev->l->r = prev->r;
        mm.erase(k);
    }
    
    Node* findk(int k){
        return mm[k];
    }
    
    void travsal(){
        for (Node* i = head->r; i!=tail; i = i->r ) cout << i->e << " ";
    }
};

int main()
{
    List LL;
    cin >> n;
    for (int i = 0; i < n; i ++ )
    {
        string op;
        int k,x;
        cin >> op;
        if ( op == "L")
        {
            cin >> x;
            LL.insert(0,x);
        }
        else if (op == "R")
        {
            cin >> x;
            LL.insert(LL.tail->l->id, x);
        }
        else if (op == "D")
        {
            cin >> x;
            LL.del(x+1);
        }
        else if (op == "IL")
        {
            cin >> k >> x;
            LL.insert(LL.findk(k+1)->l->id,x);
        }
        else {
            cin >> k >> x;
            LL.insert((k+1) , x);
        }
    }
    
    LL.travsal();
    
}


