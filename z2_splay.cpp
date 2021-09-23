#include <iostream>
using namespace std;

const int maxn = 1e5+10;
struct Node{
    int l,r,val;
    int size, cnt;
}tr[maxn];
int root, cnt;

void newNode(int &now, int val){
    tr[now=++cnt].val = val;
    tr[now].size = tr[now].cnt = 1;
}

void update(int now){
    tr[now].size = tr[now].cnt+tr[tr[now].l].size+tr[tr[now].r].size;
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

void splaying(int x, int &y){
    if (x == y) return;
    int &l = tr[y].l;int &r = tr[y].r;
    if (l==x) zig(y);
    else if (r==x) zag(y);
    else {
        if (tr[x].val < tr[y].val){
            if (tr[x].val < tr[l].val)splaying(x,tr[l].l), zig(l), zig(y);
            else splaying(x, tr[l].r), zag(l), zig(y);
        }
        else {
            if (tr[x].val > tr[r].val) splaying(x,tr[r].r), zag(r), zag(y);
            else splaying(x, tr[r].l), zig(r), zag(y);
        }
    }
}
void ins(int &now, int val){
    if (!now) newNode(now, val), splaying(now, root);
    else if (val == tr[now].val){
        tr[now].cnt++;
        tr[now].size++;
        splaying(now, root);
    }
    else if (val < tr[now].val) ins(tr[now].l, val);
    else ins(tr[now].r, val);
    update(now);
}

void del(int now, int val){
    if (tr[now].val == val){
        splaying(now, root);
        if (tr[now].cnt > 1) tr[now].cnt--,tr[now].size--;
        else {
            // if ()
            if (!tr[root].r){
                root = tr[root].l;
            }
            else{

            int n=tr[root].r;
            while (tr[n].l) n=tr[n].l;
            splaying(n,tr[root].r);
            tr[tr[root].r].l = tr[root].l;
            root = tr[root].r;
            update(root);
            }

        }
    }
    else if (val < tr[now].val) del(tr[now].l, val);
    else del(tr[now].r, val);
    update(now);
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
}
