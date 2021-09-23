 // passed

 // 

#include <iostream>
using namespace std;

const int maxn = 1e5+5;
struct Node{
    int l,r,val;
    int cnt,size;
} tr[maxn];
int root, cnt;

void newnode(int& now, int val){
    tr[now=++cnt].val = val;
    tr[cnt].cnt = 1;
    tr[cnt].size = 1;
}

void update(int now){
    tr[now].size = tr[tr[now].l].size+tr[tr[now].r].size+tr[now].cnt;
}

void zig(int &now){
    int l = tr[now].l;
    tr[now].l = tr[l].r;
    tr[l].r = now;
    now = l;
    update(tr[now].r), update(now); 
}

void zag(int &now){
    int r = tr[now].r;
    tr[now].r = tr[r].l;
    tr[r].l = now;
    now = r;
    update(tr[now].l), update(now);
}

void splaying(int x, int& y){
    if (x==y) return;
    int &l = tr[y].l, &r = tr[y].r;
    if (x==l) zig(y);
    else if (x==r) zag(y);
    else{
        if (tr[x].val < tr[y].val){
            if (tr[x].val < tr[l].val)
                splaying(x, tr[l].l),zig(y),zig(y);
            else splaying(x, tr[l].r), zag(l), zig(y);
        } 
        else{
            if (tr[x].val > tr[r].val)
                splaying(x, tr[r].r),zag(y),zag(y);
            else splaying(x, tr[r].l),zig(r), zag(y);
        }
    }
}

void ins(int &now, int val){
    if (!now) newnode(now, val), splaying(now, root);
    else if (val < tr[now].val) ins(tr[now].l, val);
    else if (val > tr[now].val) ins(tr[now].r, val);
    else tr[now].cnt++, tr[now].size++,splaying(now, root);
}

void delNode(int now){
    splaying(now, root);
    if (tr[root].cnt > 1) tr[root].cnt--, tr[root].size--;
    else if (tr[now].r){  //TODO
        int p = tr[root].r;
        while (tr[p].l) p = tr[p].l;
        splaying(p, tr[root].r);
        tr[tr[root].r].l = tr[root].l;
        root = tr[root].r;
        update(root);
    }
    else {
        root = tr[root].l;
    }
}
void del(int now, int& val){
    if (tr[now].val == val) delNode(now);
    else if (val < tr[now].val) del(tr[now].l, val);
    else del(tr[now].r, val);
}

int getrank(int val){
    // cout << "getrank";
    int now = root;
    int rank = 1;
    while (now) {
        if (tr[now].val == val){
            rank += tr[tr[now].l].size;
            splaying(now, root);
            break;
        }
        if (val <= tr[now].val) now = tr[now].l;
        else {
            rank += tr[now].cnt + tr[tr[now].l].size;
            now = tr[now].r;
        }
    }
    // cout << rank << endl;
    return rank;
}

int getnum(int rank){
    int now = root;
    while (now){
        if (tr[tr[now].l].size+1<=rank && rank <= tr[tr[now].l].size+tr[now].cnt){
            splaying(now, root);
            break;
        }
        if (tr[tr[now].l].size+1> rank) now = tr[now].l;
        else {
            rank -= tr[tr[now].l].size + tr[now].cnt;
            now = tr[now].r;
        }
    }
    // cout << tr[now].val << endl;
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
    // ins(root, 1);
    // ins(root, 2);
    // ins(root, 2);
    // ins(root, 4);
    // ins(root, 4);
    // ins(root, 50);
    // cout << getnum(getrank(4)+1) << endl;
}