#include <iostream>
using namespace std;

const int N = 1e5+10;
template <class Record>
struct Node
{
    Record val;
    Node<Record> *ne;

    Node(){}
    Node(int _v):val(_v), ne(0) {}
} ;

template<class Record>
Node<Record>* div(Node<Record>* q){
    Node<Record>* pos, *mid;
    pos = mid = q;
    while (pos->ne){
        pos=pos->ne;
        while (pos->ne){
            pos=pos->ne;
            mid=mid->ne;
        }
    }
    pos = mid->ne;
    mid->ne = 0;
    return pos;
}

template<class Record>
Node<Record>* merge(Node<Record>* q1, Node<Record>* q2)
{
    Node<Record> combine, *last;
    last = &combine;
    while (q1!=0 && q2 != 0)
    {
        if (q1->val < q2->val)
        {
            last->ne = q1;
            q1=q1->ne;
        }
        else 
        {
            last->ne = q2;
            q2 = q2->ne;
        }
    }
    while (q1!= 0) 
        last->ne = q1, q1=q1->ne;
    while (q2!= 0) 
        last->ne = q2, q2=q2->ne;
    
    return combine.ne;
}

template<class Record>
void merge_sort(Node<Record>*& q)
{
    if (q != NULL && q->ne != NULL){
        Node<Record>* sec;
        // divide
        sec = div(q);

        merge_sort(q);
        merge_sort(sec);
        
        q = merge(q, sec);
    }
}
int n;
int main()
{
    cin >> n;
    Node<int> h;
    Node<int> *a = &h;
    int x;
    for (int i=0;i<n;i++) {
        cin >> x;
        a->ne = new Node<int>(x);
        a = a->ne;
    }
    merge_sort(a->ne);
    while (a->ne){
        cout << a->ne;
        printf("%d ", a->ne->val);
    }
}