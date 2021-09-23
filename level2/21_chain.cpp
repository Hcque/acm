// 826
#include <iostream>
using namespace std;

const int N = 1e6+10;
int head, e[N], ne[N], idx;

void init()
{
    head = -1;
    idx = 0;
}
void add_to_head(int x){
    e[idx] = x;
    ne[idx] = head;
    head = idx;
    idx++;
}

// add to k's next
void add(int x, int k){
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx;
    idx++;
}

// remove k 's next 
void remove(int x,int k){
    ne[k] = ne[ne[k]];
}
int main(){
    int m;
    cin >> m;
    while (m--){
        int k,x;
        char op;
        cin >> op;
        if (op == 'H'){
            cin >> x;
            add_to_head(x);
        }
        else if (op == 'D')
        {
            cin >> k;
            remove(x,k-1);
        }
        else 
        {
            cin >> k >> x;
            add(k-1,x);
        }
    }
    for (int i=head;i!=-1;i=ne[i]) cout << e[i] << ' ';
    cout << endl;


}