#include <iostream>
using namespace std;
// passed
const int MAXN = 1e5+4;

struct Node{
    int l,r,val, fa;
    int size, height;
} avl[MAXN];

int root, cnt;
void newNode(int &now, int val){
    avl[now = ++cnt].val = val;
    // avl[cnt].l = avl[cnt].r = 0;
    avl[cnt].size = 1;
//  avl[cnt].height = 1;
}

void update(int now){
    avl[now].size = avl[avl[now].l].size+avl[avl[now].r].size+1;
    avl[now].height = std::max(avl[avl[now].l].height, avl[avl[now].r].height)+1;
}

inline int factor(int now){
    return avl[avl[now].l].height-avl[avl[now].r].height;
}


void lrotate(int& now){
    int r = avl[now].r;
    avl[now].r = avl[r].l;
    avl[r].l = now;
    now = r;
    update(avl[now].l), update(now);
}

void rrotate(int& now){
    int l = avl[now].l;
    avl[now].l = avl[l].r;
    avl[l].r = now;
    now = l;
    update(avl[now].r), update(now); 
}

void check(int &now){

    int f = factor(now);
    if (f>1){
        int lf = factor(avl[now].l);
        if (lf>0) rrotate(now);
        else lrotate(avl[now].l), rrotate(now);
    }
    else if (f < -1){
        int rf = factor(avl[now].r);
        if (rf<0) lrotate(now);
        else { rrotate(avl[now].r); lrotate(now);}
    }
    if (now) update(now);

}

void insert(int &now, int val){
    if (!now) newNode(now, val);
    else if (val < avl[now].val) insert(avl[now].l, val), avl[avl[now].l].fa = now;
    else insert(avl[now].r, val), avl[avl[now].r].fa = now;
    check(now);
}

int find(int &now, int fa){
    int ret;
    if (!avl[now].l){
        ret = now;
        avl[fa].l = avl[now].r;
    }
    else {
        ret = find(avl[now].l, now);
        check(now);
    }
    return ret;
}

void del(int &now, int val){
    if (val == avl[now].val){
        // del_node(now);
        int l = avl[now].l, r = avl[now].r;
        if (!l||!r) now = l+r;
        else {
            now = find(r,r);
            if (now != r){
                avl[now].r = r;
            }
            avl[now].l = l;
        }
    }
    else if (val < avl[now].val) del(avl[now].l, val);
    else del(avl[now].r, val);
    check(now);

   
}

int getrank(int val){
    int now = root, rank = 1;
    while (now){
        if (val <= avl[now].val)
            now = avl[now].l;
        else {
            rank += avl[avl[now].l].size + 1;
            now = avl[now].r;
        }
    }
    return rank;
}
int getnum(int rank){
    int now = root;
    while (now){
        if (avl[avl[now].l].size+1==rank)
            break;
        if (avl[avl[now].l].size >= rank)
            now = avl[now].l;
        else {
            rank -= avl[avl[now].l].size+1;
            now = avl[now].r;
        }
    }
    return avl[now].val;
}

int main(){
    int T;
    cin >> T;
    while (T--){
        int op, x;
	cin >> op >> x;
    // cout << op << endl;
	switch (op){
	    case 1: insert(root, x); break;
	    case 2: del(root, x); break;
	    case 3: cout << getrank(x) << endl; break;
	    case 4: cout << getnum(x) << endl; break;
	    case 5: cout << getnum(getrank(x)-1) << endl; break;
	    case 6: cout << getnum(getrank(x+1)) << endl; break;
	}
    }

}

 // int x = root;
    // while (x){
    //     if (avl[x].val == val){
    //       del_node(x);
    //       return;
    //     }
    //     else if ( val < avl[x].val){
    //         x = avl[x].l;
    //     }
    //     else {
    //         x = avl[x].r;
    //     }
    // }
    

// int succ_h(int &x){
//     if (avl[x].l){
//         succ_h(avl[x].l);
//     }
// }
// int succ(int &now){
//     int x = avl[now].r;
//     while ( avl[x].l){
//         x = avl[x].l;
//     }
//     return x;
// }


// void del_node(int x){
//             int l = avl[x].l; int r = avl[x].r; int fa = avl[x].fa;
//             if (l == 0 && r==0) {
//                 if (x==avl[fa].l) avl[fa].l=0;
//                 else avl[fa].r = 0;
//             }
//             else if (l==1&&r==0){
//                 if (x==avl[fa].l) avl[fa].l=avl[x].l;
//                 else avl[fa].r = avl[x].l;
//             }
//             else if (l==0&&r==1){
//                 if (x==avl[fa].l) avl[fa].l=avl[x].r;
//                 else avl[fa].r = avl[x].r;
//             }
//             else {
//                 int s = succ(x);
//                 swap(avl[x].val , avl[s].val);
//                 // int m = s;
//                 // while ( avl[m].fa != x) check(m);
//                 del_node(s);
//             }
// }