// luogu 3369

#include <iostream>
#include <cassert>
using namespace std;

const int maxn = 1e5+5;
const double alpha = 0.75;
struct Node{
    int l,r,val;
    int size,fact;
    bool exist;
} TZY[maxn];

int cnt, root;
void newNode(int &now, int val){
   now = ++cnt;
   TZY[now].val = val;
   TZY[now].size = TZY[now].fact = 1;
   TZY[now].exist = true;
}

bool imbalance(int now){
    if (std::max(TZY[TZY[now].l].size , TZY[TZY[now].r].size) > TZY[now].size*alpha 
    || (TZY[now].size-TZY[now].fact) > TZY[now].size * 0.3){
    return true;
    }
    return false;
}

#include <vector>
std::vector<int> v;

void inorder(int now){
    if (!now) return;
    inorder(TZY[now].l);
    if (TZY[now].exist) v.push_back(now);
    inorder(TZY[now].r);
}

void lift(int l, int r, int &now){
    if (l == r){
        now = v[l];
        TZY[now].l = TZY[now].r = 0;
        TZY[now].size = TZY[now].fact = 1;
        return;
    }
    int mid = (l+r)>>1;
    while (mid>l && TZY[v[mid]].val==TZY[v[mid-1]].val) 
        mid--;
    now = v[mid];
    if (l<mid) 
        lift(l, mid-1, TZY[now].l);
    else TZY[now].l = 0;

    lift(mid+1,r, TZY[now].r);
    TZY[now].size = TZY[TZY[now].l].size + TZY[TZY[now].r].size + 1;
    TZY[now].fact = TZY[TZY[now].l].fact + TZY[TZY[now].r].fact + 1;
}

void rebuild(int &now){
    v.clear();
    inorder(now);
    if (v.empty()) {
        now = 0;
	return;
    }
    lift(0, v.size()-1, now);
}

void update(int &now, int end){
    if (!now) return;
    if (TZY[end].val < TZY[now].val){
        update(TZY[now].l, end);
    }
    else update(TZY[now].r, end);
    TZY[now].size = TZY[TZY[now].l].size + TZY[TZY[now].r].size + 1;
}

void check(int &now, int end){
    if (now == end) return;
    if (imbalance(now)){
        rebuild(now);
        update(root, now);
        return;
    }
    if (TZY[end].val < TZY[now].val) 
        check(TZY[now].l, end);
    else check(TZY[now].r, end);
}

void insert(int &now, int val){
    if (!now){
        newNode(now, val);
        check(root, now);
        return;
    }
    TZY[now].size++;
    TZY[now].fact++;
    if (val < TZY[now].val) 
        insert(TZY[now].l, val);
    else insert(TZY[now].r, val);
}


// assume has this node
void del(int &now, int val){
    if ( TZY[now].exist && TZY[now].val == val){
        TZY[now].exist = false;
        TZY[now].fact--;
	check(root, now);
	return;
    }
    TZY[now].fact--;
    if (val < TZY[now].val) del(TZY[now].l, val);
    else del(TZY[now].r, val);
}

int get_rank(int val){
    // cout << "get rank" << endl;
    int now = root, rank = 1;
    while (now){
        if (val<=TZY[now].val){
            now = TZY[now].l;
        }
        else{
            rank += TZY[now].exist + TZY[TZY[now].l].fact;
            now = TZY[now].r;
        }
    }
    return rank;
}

int getnum(int rank){
    // cout << "getnum" << endl;
    int now = root;
    while (now) {
        // assert(TZY[now].l != 0);
        if (TZY[now].exist && TZY[TZY[now].l].fact+ TZY[now].exist == rank) 
            break;
        else if (TZY[ TZY[now].l].fact >= rank)
            now = TZY[now].l;
        else {
            rank -= TZY[TZY[now].l].fact + TZY[now].exist;
            now = TZY[now].r;
        }
    }
    return TZY[now].val;
}

int main(){
    int T;
    cin >> T;
    while (T--){
        int op, x;
        cin >> op >> x;
        switch (op)
        {
            case 1: insert(root, x); break;
            case 2: del(root, x); break;
            case 3: cout << get_rank(x) << endl; break;
            case 4: cout << getnum(x) << endl; break;
            case 5: cout << getnum(get_rank(x)-1) << endl; break;
            case 6: cout << getnum(get_rank(x+1)) << endl; break;
        }

    }


}



