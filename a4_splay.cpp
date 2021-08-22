#include <iostream>
using namespace std;

const int maxn = 1e5+5;
struct Node{
    int l,r,val;
    int cnt,size;
} spl[maxn];
int root, cnt;

void newnode(int& now, int& val){
    spl[now=++cnt].val = val;
    spl[cnt].cnt++;
    spl[cnt].size++;
}

void update(int now){
    spl[now].size = spl[spl[now].l].size+spl[spl[now].r].size+spl[now].cnt;
}

void zig(int now){
    int l = spl[now].l;
    spl[now].l = spl[l].r;
    spl[l].r = now;
    now = l;
    update(spl[now].r), update(now); 
}

void zag(int now){
    int r = spl[now].r;
    spl[now].r = spl[r].l;
    spl[r].l = now;
    now = r;
    update(spl[now].l), update(now);
}

void splaying(int x, int y){
    if (x==y) return;
    int &l = spl[y].l, &r = spl[y].r;
    if (x==l) zig(y);
    else if (x==r) zag(y);
    else{
        if (spl[x].val < spl[y].val){
            if (spl[x].val < spl[l].val)
                splaying(x, spl[l].l),zig(y),zig(y);
            else splaying(x, spl[l].r), zag(l), zig(y);
        } 
        else{
            if (spl[x].val > spl[r].val)
                splaying(x, spl[r].r),zag(y),zag(y);
            else splaying(x, spl[r].l),zig(r), zag(y);
        }
    }
}
void ins(int &now, int& val){
    if (!now) newnode(now, val), splaying(now, root);
    if (val < spl[now].val) ins(spl[now].l, val);
    else if (val > spl[now].val) ins(spl[now].r, val);
    else spl[now].cnt++, spl[now].size++;
    update(now);
}

void delNode(int &now){
    splaying(now, root);
    if (spl[now].cnt > 1) spl[now].cnt--, spl[now].size--;
    else if (spl[now].r){
        int p = spl[now].r;
        while (spl[p].l) p = spl[p].l;
        splaying(p, spl[now].r);
        spl[spl[now].r].l = spl[now].l;
        root = spl[now].r;
    }
    else {
        root = spl[now].l;
    }
}
void del(int &now, int& val){
    if (spl[now].val == val) delNode(now);
    else if (spl[now].val < val) del(spl[now].l, val);
    else del(spl[now].r, val);
}

int getrank(int val){
    cout << "getrank";
    int now = root;
    int rank = 1;
    while (now) {
        if (spl[now].val == val){
            rank += spl[now].size;
            splaying(now, root);
            break;
        }
        if (val <= spl[now].val) now = spl[now].l;
        else {
            rank += spl[now].cnt + spl[spl[now].l].size;
            now = spl[now].r;
        }
    }
    // cout << rank << endl;
    return rank;
}

int getnum(int rank){
    cout << "getnum";
    int now = root;
    while (now){
        if (spl[spl[now].l].size+1<=rank && rank <= spl[spl[now].l].size+spl[now].cnt){
            splaying(now, root);
            break;
        }
        if (spl[spl[now].l].size+1> rank) now = spl[now].l;
        else {
            rank -= spl[spl[now].l].size + spl[now].cnt;
            now = spl[now].r;
        }
    }
    // cout << spl[now].val << endl;
    return spl[now].val;
}

int main()
{
    int T;
    cin >> T; 
    while (T--){
        int op, x;
        cin >> op >> x;
        cout << op  << "|" << T << endl;
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