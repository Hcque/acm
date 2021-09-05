//  base case return
// scanf char
// L,R
// if,if
// mid
// low, high


//  http://poj.org/problem?id=3468


#include <iostream>
using namespace std;

const int maxn = 1e5+10;
typedef long long ll;

struct Node{
    int l,r;
    ll sum, add;
} tree[maxn*4];

int a[maxn];
int root, cnt=0;
void newNode(int now, int l, int r, int val){
    tree[now].l=l; tree[now].r=r;
    tree[now].sum = val;
}

void build(int now, int low, int high){
    if (low > high) return ;
    tree[now].l = low; tree[now].r = high;
    if (low==high){
        newNode(now, low,high, a[low]);
    // cout <<L << "|"<< tree[now].sum  << "|"<<R<< endl;
        return;
    }
    int mid = (low+high)/2;
     build(2*now, low,mid);
     build(2*now+1, mid+1, high);
    tree[now].sum = tree[2*now].sum + tree[2*now+1].sum;
    // return now;
}

void pushDown(int now){
    if (tree[now].add){
        tree[2*now].add += tree[now].add;
        tree[2*now+1].add += tree[now].add;
        tree[2*now].sum += (tree[2*now].r-tree[2*now].l+1)*tree[now].add;
        tree[2*now+1].sum += (tree[2*now+1].r-tree[2*now+1].l+1)*tree[now].add;
        tree[now].add=0;
    }
}

void add(int now, int L, int R, int d){
    if (tree[now].l>R||tree[now].r<L) return;
    if (L<=tree[now].l&&tree[now].r<=R){
        tree[now].add += d;
        tree[now].sum += (ll)(tree[now].r-tree[now].l+1)*d;
        return;
    }
    pushDown(now);
    // int mid=(L+R)>>1;
    int mid = (tree[now].l+tree[now].r)/2;
    if (L<=mid) add(2*now, L,R,d);
    if (R>=mid+1) add(2*now+1, L,R,d);
}

ll range_q(int now, int L, int R){
    // cout <<L << "|"<< tree[now].sum  << "|"<<R<< endl;
    if (tree[now].l>R||tree[now].r<L) return 0;
    if (L<=tree[now].l&&tree[now].r<=R){

        // cout <<L << "|"<< tree[now].sum  << "|"<<R<< endl;
        return tree[now].sum;
    }
    pushDown(now);
    // int mid=(L+R)>>1;
    int mid = (tree[now].l+tree[now].r)/2;
    ll ret=0;
    if (L<=mid) ret+=range_q(2*now, L,R);
    if (R>=mid+1) ret+=range_q(2*now+1, L,R);
    return ret;
}

int main()
{
    int N, M, t;
    scanf("%d%d", &N, &M);
    for (int i=1;i<=N;i++) {
        scanf("%d", &t);
        a[i] = t;
    }
    build(1,1,N);
    // for (int i=1;i<=N;i++) cout << tree[i].l << " ";
    // cout << endl;
    for (int i=1;i<=M;i++){
        char op; int L,R,d;
        cin >> op;
        switch (op){
            case 'C':
                scanf("%d%d%d", &L, &R,&d);
                add(1,L,R,d);
                break;
            case 'Q':
                scanf("%d%d", &L, &R);
                printf("%lld\n", range_q(1,L,R));
                break;
        }
    }
    return 0;
}


