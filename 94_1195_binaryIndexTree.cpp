
//https://www.cnblogs.com/man1304010109/p/3587199.html
#include <iostream>
#include <cstring>

using namespace std;

int S, X, Y, A, L, B, R, T;

const int MAXN = 1030;
// int a[MAXN][MAXN];
int tree[MAXN][MAXN];

inline int lowbit(int x){
    return x & (-x);
}

void insert(int X, int Y, int A){
    for (int i = X; i<=S; i += lowbit(i)){
        for (int j=Y;j<=S;j+=lowbit(j)){
            tree[i][j] += A;
        }
    }
}

int getSum(int X, int Y){
    // cout << X << Y;
    int ans =0;
    for (int i=X; i>0; i -= lowbit(i)){
        for (int j=Y;j>0;j-=lowbit(j)){
            ans += tree[i][j];
        }
    }
    return ans;
}

int main()
{
    int flag;
    while (1){

    cin >> flag;
    switch (flag){
        case 0:
         cin >> S; 
        memset(tree, 0, sizeof(tree));
         break;
        case 1:
        //  cin >> X >> Y >> A;
        scanf("%d %d %d", &X, &Y, &A);
         X+=1; Y+=1;
         insert(X, Y, A);
         break;

        case 2:
            // cin >> L >> B >> R >> T;
            scanf("%d %d %d %d", &L,&B,&R,&T);
            R+=1;T+=1;
            cout << getSum(R,T)-getSum(L,R)-getSum(B,T)+getSum(L,B);
            cout << endl;
            break;
        case 3:
         return 0;
    }
        }

}