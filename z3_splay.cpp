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
} spl[maxn];
int root, cnt=0;


void newNode(int &now, int val){
    spl[now=++cnt].val = val;
    spl[now].siz = spl[now].cnt = 1;
}

void update(int now){
    spl[now].siz = spl[now].cnt + (spl[spl[now].l].siz + spl[spl[now].r].siz);
}

void zig(int &now){
    int l = spl[now].l;
    spl[now].l = spl[l].r;
    spl[l].r = now;
    now = l;
    update(spl[now].r); update(now);
}
void zag(int &now){
    int r = spl[now].r;
    spl[now].r = spl[r].l;
    spl[r].l = now;
    now = r;
    update(spl[now].l); update(now);
}

void splaying(int &now, int &y){
    if (!now) return;
    int &l = spl[y].l; int &r = spl[y].r; 
    if (now==l) zig(y);
    else if (now==r) zag(y);
    else if (spl[y].val>spl[now].val) {
        if (spl[l].val > spl[now].val) splaying(now, spl[l].l), zig(y),zig(y);
        else splaying(now,spl[l].r), zag(l), zig(y);
    }
    else if (spl[now].val > spl[y].val){
        if (spl[now].val > spl[r].val) splaying(now, spl[r].r), zag(y),zag(y);
        else splaying(now,spl[r].l), zig(r), zag(y);
    }
    // update(y);
}
void ins(int &now, int val){
    if (!now) newNode(now, val), splaying(now, root);
    else if (spl[now].val == val){
        spl[now].cnt++;
        spl[now].siz++;
        splaying(now, root);
        assert(now==root);
    }
    else if (val < spl[now].val) ins(spl[now].l, val);
    else ins(spl[now].r, val);
    update(now);
}

void del(int now, int val){
    if (!now) return;
    if (spl[now].val == val){
        splaying(now, root);
        if (spl[now].cnt>1) {
            spl[now].cnt--;
            spl[now].siz--;
        }
        else if (!spl[now].r){
            root = spl[now].l;
        }
        else{
            int p = spl[now].r;
            while (spl[p].l) p = spl[p].l;
            splaying(p,spl[now].r);
            spl[spl[now].r].l = spl[now].l;
            root = p;
            update(p);
        }
    }
    else if (val < spl[now].val) del(spl[now].l, val);
    else del(spl[now].r, val);
    update(now);
}



int getrank(int val){
    int now = root;
    int rank = 1;
    while (now) {
        if (spl[now].val == val){
            rank += spl[spl[now].l].siz;
            splaying(now, root);
            break;
        }
        if (val <= spl[now].val) now = spl[now].l;
        else {
            rank += spl[now].cnt + spl[spl[now].l].siz;
            now = spl[now].r;
        }
    }
    return rank;
}

int getnum(int rank){
    int now = root;
    while (now){
        if (spl[spl[now].l].siz+1<=rank && rank <= spl[spl[now].l].siz+spl[now].cnt){
            splaying(now, root);
            break;
        }
        if (spl[spl[now].l].siz+1> rank) now = spl[now].l;
        else {
            rank -= spl[spl[now].l].siz + spl[now].cnt;
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