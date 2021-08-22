#include <iostream>
using namespace std;

const int N = 5e4 + 4;
const int INF = 0x7fffffff;

struct Splay_Tree{
    struct Node{
        int val,Size, Max, add, child[2];
        bool rev;
        void init(int _val){ 
            child[0] = child[1] = rev = add = 0;
            val = Max = _val;
            Size = 1;
        }
    } T[N];
    int fa[N], root;

    void push_up(int x){
        T[x].Max = T[x].val; T[x].Size = 1;
        if (T[x].child[0]){
            T[x].Max = max(T[x].Max, T[T[x].child[0]].Max);   
            T[x].Size += T[T[x].child[0]].Size;
        }
        if (T[x].child[1]){
            T[x].Max = max(T[x].Max, T[T[x].child[1]].Max);   
            T[x].Size += T[T[x].child[1]].Size;
        }
    }

    void push_down(int x){
        if (x==0) return;
        if (T[x].add){
            if (T[x].child[0]){
                T[T[x].child[0]].Max += T[x].add;
                T[T[x].child[0]].val += T[x].add;
                T[T[x].child[0]].add += T[x].add;
            }
            if (T[x].child[1]){
                T[T[x].child[1]].Max += T[x].add;
                T[T[x].child[1]].val += T[x].add;
                T[T[x].child[1]].add += T[x].add;
            }
            T[x].add = 0;
        }
        if (T[x].rev){
            if (T[x].child[0]) T[T[x].child[0]].rev ^= 1;
            if (T[x].child[1]) T[T[x].child[1]].rev ^= 1;
            swap(T[x].child[0], T[x].child[1]);
            T[x].rev = 0;
        }
    }

    // 0 left rotate, i right rotate
    void Rotate(int x, int kind){
        int y = fa[x], z = fa[y];
        T[y].child[!kind] = T[x].child[kind], fa[T[x].child[kind]] = y;
        T[x].child[kind] = y, fa[y] = x;
        T[z].child[T[x].child[1]==y] = x, fa[x] = z;
        push_up(y);
    }

    void zig(int x){
        // int y = fa[x];
        // ch[y][0] = ch[x][1];
        // fa[ch[x][1]] = y;
        // ch[x][1] = y;
        // fa[x] = fa[y];
        // if (y == ch[fa[y]][0]){
        //     ch[fa[y]][0] = x;
        // }
        // else if (y == ch[fa[y]][1]) {
        //     ch[fa[y]][1] = x;
        // }
        // fa[y] = x;
        // push_up(y);
        // if (y == root) root = x;
    }

    void zag(int x){

    }

    void Splay(int x, int goal){
        if (x == goal) return;
        while (fa[x] != goal){
            int y = fa[x], z = fa[y];
            push_down(z), push_down(y), push_down(x);
            int rx = T[y].child[0] == x, ry = T[z].child[0] == y;
            if (z==goal) Rotate(x, rx);
            else {
                if (rx == ry) Rotate(y, ry);
                else Rotate(x, rx);
                Rotate(x, ry);
            }
        }
        push_up(x);
        if (goal==0) root==x;
    }

    int Select(int pos){
        int u = root;
        push_down(u);
        while (T[T[u].child[0]].Size != pos) {
            if (pos < T[T[u].child[0]].Size ){
                u = T[u].child[0];
            }
            else{
                pos -= (T[T[u].child[0]].Size + 1);
                u = T[u].child[1];   
            }
            push_down(u);
        }
        return u;
    }

    void update(int L, int R, int val){
        int u = Select(L-1), v = Select(R+1);
        Splay(u, 0);
        Splay(v, u);
        T[T[v].child[0]].Max += val;
        T[T[v].child[0]].add += val;
        T[T[v].child[0]].val += val;
    }

    void Reverse(int L, int R){
        int u = Select(L-1), v = Select(R+1);
        Splay(u, 0);
        Splay(v, u);
        T[T[v].child[0]].rev ^= 1;
    }

    int query(int L, int R){
        int u = Select(L-1), v = Select(R+1);
        Splay(u, 0);
        Splay(v, u);
        return T[T[v].child[0]].Max;
    }

    int build(int L, int R){
        if (L > R) return 0;
        if (L==R) return L;
        int mid=(L+R)>>1, sL, sR;
        T[mid].child[0] = sL = build(L, mid-1);
        T[mid].child[1] = sR = build(mid+1, R);
        fa[sL] = fa[sR] = mid;
        push_up(mid);
        return mid;
    }

    void init(int n){
        T[0].init(-INF); T[1].init(-INF); T[n+2].init(-INF);
        for (int i=2;i<=n+1;i++) T[i].init(0);
        root = build(1, n+2); fa[root]=0;
        fa[0] = 0;
        T[0].child[1] = root;
        T[0].Size = 0;
    }
};

Splay_Tree hehe;
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    hehe.init(n);
    for (int i=0;i<m;i++){
        int flag;
        int L, R;
        scanf("%d", &flag);
        if (flag == 1){
            int v;
            scanf("%d%d%d", &L, &R, &v);
            hehe.update(L, R, v);
        }
        if (flag == 2){
            scanf("%d%d", &L, &R);
            hehe.Reverse(L, R);
        }
        if (flag == 3){
            scanf("%d%d", &L, &R);
            cout << hehe.query(L, R) << endl;
        }
    }
}