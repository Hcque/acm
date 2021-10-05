// splay

!!

#include <iostream>
using namespace std;

const int N = 1e5+10;
struct Node
{
    int l, r, sz, val, cnt;
#define L(x) tr[x].l
#define R(x) tr[x].r
} tr[N];
int root, cnt;

void newNode(int &u, int val){
    tr[u = ++cnt].val = val;
    tr[u].sz = tr[u].cnt = 1;
}

void update(int u)
{
    tr[u].sz = tr[u].cnt + tr[L(u)].sz + tr[R(u)].sz;
}
void zig(int &u)
{
    int l = tr[u].l;
    tr[u].l = tr[l].r;
    tr[l].r = u;
    u = l;
    update(R(u)); update(u);
}

void zag(int &u)
{
    int r = tr[u].r;
    tr[u].r = tr[r].l;
    tr[r].l = u;
    u = r;
    update(L(u)); update(u);
}

void splay(int &u, int &y)
{
    int &l = tr[y].l, &r = tr[y].r;
    if (u == l) zig(y);
    else if (u == r) zag(y);
    else {
        if (tr[l].sz > tr[r].sz){
            if (tr[tr[l].l].sz > tr[tr[l].r].sz) zig(l);
            else zag(l);
            zig(y);
        }
        else {
            if (tr[tr[r].r].sz > tr[tr[r].r].sz) zag(r);
            else zig(r);
            zag(y);
        }
    }
    update(u);
}

void ins(int &u, int val)
{
    if (!tr[u].val) newNode(u, val), splay(u, root);
    else if (val == tr[u].val){
        tr[u].cnt++;
        tr[u].sz++;
        splay(u, root);
    }
    else if (val < tr[u].val) ins(tr[u].l, val);
    else ins(tr[u].r, val);
    update(u);
}

void del(int u, int val)
{
    if (tr[u].val == val) {
        if (tr[u].cnt > 1) tr[u].cnt--, tr[u].sz--, splay(u,root);
        else {
            splay(u, root);
            int p = u;
            while (L(p)) p = tr[p].l;
            splay(p, tr[u].r);
            if (!L(u)) root = tr[u].r;
            else {
                tr[R(u)].l = tr[u].l;
                root = tr[u].r;
            }
        }
    }
    else if (val < tr[u].val) del(L(u), val);
    else del(R(u), val);
    update(u);
}


int getrank(int val){
    // cout << "getrank";
    int now = root;
    int rank = 1;
    while (now) {
        if (tr[now].val == val){
            rank += tr[tr[now].l].sz;
            splay(now, root);
            break;
        }
        if (val <= tr[now].val) now = tr[now].l;
        else {
            rank += tr[now].cnt + tr[tr[now].l].sz;
            now = tr[now].r;
        }
    }
    // cout << rank << endl;
    return rank;
}

int getnum(int rank){
    int now = root;
    while (now){
        if (tr[tr[now].l].sz+1<=rank && rank <= tr[tr[now].l].sz+tr[now].cnt){
            splay(now, root);
            break;
        }
        if (tr[tr[now].l].sz+1> rank) now = tr[now].l;
        else {
            rank -= tr[tr[now].l].sz + tr[now].cnt;
            now = tr[now].r;
        }
    }
    return tr[now].val;
}



int main()
{
    int T;
    cin >> T; 
    while (T--){
        int op, x;
        cin >> op >> x;
        // cout << op  << "|" << tr[root].size << endl;
        switch (op)
        {
            case 1: ins(root, x); break;
            case 2: del(root, x); break;
            case 3: cout << getrank(x) << endl; break;
            case 4: cout << getnum(x) << endl; break;
            case 5: cout << getnum(getrank(x)-1) << endl; break;
            case 6: cout << getnum(getrank(x+1)) << endl; break;
        }
    }
}

