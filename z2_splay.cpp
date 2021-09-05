#include <iostream>
using namespace std;

const int maxn = 1e5+10;
struct Node{
    int l,r,val;
    int size, cnt;
}spl[maxn];
int root, cnt;

void newNode(int &now, int val){
    spl[now=++cnt].val = val;
    spl[now].size = spl[now].cnt = 1;
}

void update(int now){
    spl[now].size = spl[now].cnt+spl[spl[now].l].size+spl[spl[now].r].size;
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

void splaying(int x, int &y){
    if (x == y) return;
    int &l = spl[y].l;int &r = spl[y].r;
    if (l==x) zig(y);
    else if (r==x) zag(y);
    else {
        if (spl[x].val < spl[y].val){
            if (spl[x].val < spl[l].val)splaying(x,spl[l].l), zig(l), zig(y);
            else splaying(x, spl[l].r), zag(l), zig(y);
        }
        else {
            if (spl[x].val > spl[r].val) splaying(x,spl[r].r), zag(r), zag(y);
            else splaying(x, spl[r].l), zig(r), zag(y);
        }
    }
}
void ins(int &now, int val){
    if (!now) newNode(now, val), splaying(now, root);
    else if (val == spl[now].val){
        spl[now].cnt++;
        spl[now].size++;
        splaying(now, root);
    }
    else if (val < spl[now].val) ins(spl[now].l, val);
    else ins(spl[now].r, val);
    update(now);
}

void del(int now, int val){
    if (spl[now].val == val){
        splaying(now, root);
        if (spl[now].cnt > 1) spl[now].cnt--,spl[now].size--;
        else {
            // if ()
            if (!spl[root].r){
                root = spl[root].l;
            }
            else{

            int n=spl[root].r;
            while (spl[n].l) n=spl[n].l;
            splaying(n,spl[root].r);
            spl[spl[root].r].l = spl[root].l;
            root = spl[root].r;
            update(root);
            }

        }
    }
    else if (val < spl[now].val) del(spl[now].l, val);
    else del(spl[now].r, val);
    update(now);
}



int getrank(int val){
    // cout << "getrank";
    int now = root;
    int rank = 1;
    while (now) {
        if (spl[now].val == val){
            rank += spl[spl[now].l].size;
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
        // cout << op  << "|" << spl[root].size << endl;
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
