// splaying pos
// splaying cmp 
// inupdate cnt + size, + / max
//del now
// now changed so: ins splaying last??

#include <iostream>
#include <cassert>
using namespace std;

const int maxn = 1e5+10;
struct Node{
    int l,r,val;
    int cnt, siz;
} tr[maxn];
int root, cnt=0;


void newNode(int &now, int val){
    tr[now=++cnt].val = val;
    tr[now].siz = tr[now].cnt = 1;
}

void update(int now){
    tr[now].siz = tr[now].cnt + (tr[tr[now].l].siz + tr[tr[now].r].siz);
}

void zig(int &now){
    int l = tr[now].l;
    tr[now].l = tr[l].r;
    tr[l].r = now;
    now = l;
    update(tr[now].r); update(now);
}
void zag(int &now){
    int r = tr[now].r;
    tr[now].r = tr[r].l;
    tr[r].l = now;
    now = r;
    update(tr[now].l); update(now);
}

void splaying(int &now, int &y){
    if (!now) return;
    int &l = tr[y].l; int &r = tr[y].r; 
    if (now==l) zig(y);
    else if (now==r) zag(y);
    else if (tr[y].val>tr[now].val) {
        if (tr[l].val > tr[now].val) splaying(now, tr[l].l), zig(y),zig(y);
        else splaying(now,tr[l].r), zag(l), zig(y);
    }
    else if (tr[now].val > tr[y].val){
        if (tr[now].val > tr[r].val) splaying(now, tr[r].r), zag(y),zag(y);
        else splaying(now,tr[r].l), zig(r), zag(y);
    }
    // update(y);
}
void ins(int &now, int val){
    if (!now) newNode(now, val), splaying(now, root);
    else if (tr[now].val == val){
        tr[now].cnt++;
        tr[now].siz++;
        splaying(now, root);
        // assert(now==root);
    }
    else if (val < tr[now].val) ins(tr[now].l, val);
    else ins(tr[now].r, val);
    update(now);
}

void del(int now, int val){
    if (!now) return;
    if (tr[now].val == val){
        splaying(now, root);
        assert(now==root);
        if (tr[now].cnt>1) {
            tr[now].cnt--;
            tr[now].siz--;
        }
        else if (!tr[now].r){
            root = tr[now].l;
        }
        else{
            int p = tr[now].r;
            while (tr[p].l) p = tr[p].l;
            splaying(p,tr[now].r);
            tr[tr[now].r].l = tr[now].l;
            root = p;
            update(p);
        }
    }
    else if (val < tr[now].val) del(tr[now].l, val);
    else del(tr[now].r, val);
    update(now);
}



int getrank(int val){
    int now = root;
    int rank = 1;
    while (now) {
        if (tr[now].val == val){
            rank += tr[tr[now].l].siz;
            splaying(now, root);
            break;
        }
        if (val <= tr[now].val) now = tr[now].l;
        else {
            rank += tr[now].cnt + tr[tr[now].l].siz;
            now = tr[now].r;
        }
    }
    return rank;
}

int getnum(int rank){
    int now = root;
    while (now){
        if (tr[tr[now].l].siz+1<=rank && rank <= tr[tr[now].l].siz+tr[now].cnt){
            splaying(now, root);
            break;
        }
        if (tr[tr[now].l].siz+1> rank) now = tr[now].l;
        else {
            rank -= tr[tr[now].l].siz + tr[now].cnt;
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