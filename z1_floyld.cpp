
// ++;
//0MS	1432K
// 15MS	1440K

// 31MS	1552K
#include <vector>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 200+10;
int s, t;
int n, m;
int E[maxn][maxn];

const int INF = 1e9;
void init(){
    for (int i=0;i<maxn;i++){
        for (int j=0;j<maxn;j++){
            E[i][j] = INF;
            if (i==j) E[i][j] = 0;
        }
    }
}

int floyd(int &s){
    for (int k=0;k<n;k++){
        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                E[i][j] = min(E[i][j], E[i][k]+E[k][j]);
            }
        }
    }
    if (E[s][t] < INF) return E[s][t];
    else return -1;
}

int main()
{
    while (scanf("%d%d", &n,&m)!=EOF){
		init();
	    while (m--){
            int a, b, w;
            scanf("%d%d%d", &a,&b,&w);
            // a++,b++;
            E[a][b]  = min(w, E[a][b]);
            E[b][a]  = min(w, E[b][a]);
	    }
	    scanf("%d%d", &s, &t);
	    printf("%d\n", floyd(s));
	}

}

