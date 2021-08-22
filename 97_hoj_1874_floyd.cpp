// #include <iostream>
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 202;

int adj[MAXN][MAXN];
int N, M;


int main(){
    while (scanf("%d %d", &N, &M) != EOF){
        // init
        for (int i=0;i<N;i++){
            for (int j=0;j<N;j++){
                adj[i][j] = 1e9;
                if (i==j) adj[i][j] = 0;
            }
        }

        // data
        for (int i=0;i<M;i++){
            int A, B, X;
            scanf("%d %d %d", &A, &B, &X);
            adj[A][B] = min(X, adj[A][B]);
            adj[B][A] = min(X, adj[B][A]);
        }
        int S, T;
        scanf("%d %d", &S, &T);

        for (int k=0;k<N;k++)
            for (int i=0;i<N;i++)
                for (int j=0;j<N;j++)
                    adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
        if (adj[S][T] == 1e9) cout << -1 << endl;
        else cout << adj[S][T] << endl;
    }

}