// https://acm.hdu.edu.cn/showproblem.php?pid=1874
// floyd 
// 46MS	1596K

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int maxn = 205;
int G[maxn][maxn];

int n, m;
const int INF = 1e9;
void init(){
    for (int i=0;i<maxn;i++){
        for (int j=0;j<maxn;j++){
            if (i==j) G[i][j] = 0;
            else G[i][j] = INF;
        }
    }
}
typedef pair<int, int> P ;

void floyd(int& s){
    for (int k=0;k<n;k++){
        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                G[i][j] = min(G[i][k] + G[k][j], G[i][j]);
            }
        }
    }
}

int main(){
    while (cin >> n >> m){
        init();
        int u, v, w;
        for (int i=0;i<m;i++){
            cin >> u>>v>>w;
            G[u][v] = min(w,G[u][v]);
            G[v][u] = min(w, G[v][u]);
        }
        int s, t;
        scanf("%d %d", &s, &t);

       floyd(s);
       if (G[s][t] == INF) cout << -1 << endl;
       else cout << G[s][t] << endl;
    }

}
