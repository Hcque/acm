#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 28;
vector<int> G[maxn];

int cp[maxn]; // completed
int vis[maxn];
int pred[maxn];
int node[maxn];
int cycle;
vector<int> out;
int n, m;

void init(){
    for (int i=0;i<maxn;i++) G[i].clear();
    memset(cp, 0, maxn*sizeof(int));
    memset(vis, 0, maxn*sizeof(int));
    memset(pred, 0, maxn*sizeof(int));
    memset(node, 0, maxn*sizeof(int));
}

void dfs(int& s, int& cycle, vector<int>& out){
    for (int i=0;i<G[s].size();i++){
        int now = G[s][i];
        if (vis[now] && !cp[now]) cycle = 1;
        if (! vis[now]){
            dfs(now, cycle, out);
        }
    }
    out.push_back(s);
    printf("%c", s+'A');
}
int cntPred(){
        int cnt = 0;
        for (int j=0;j<n;j++){
            if (pred[j] == 0) cnt++;
        }
        return cnt;
}
int cntNode(){
    
                int c=0;
                for (int t=0;t<n;t++) if(node[t])c++;
                return c;
}

int main(){
    while (scanf("%d %d", &n, &m) != EOF){
        if (n==0&&m==0) break;
        char tmp[5];
        init();
        for (int II=1;II<=m;II++){
            cin >> tmp;
            int a = tmp[0]-'A';
            int b = tmp[2]-'A';
            G[a].push_back(b);
            node[a] = 1;node[b] = 1;
            pred[a]++;
            cout << a << "|"<< b<< endl;

            cycle =0;
            out.clear();
            dfs(b, cycle, out);
            if (cycle == 1) {
                printf("Inconsistency found after %d relations.\n", II);
                break;
            }
            else {
                int c=0;
                for (int t=0;t<n;t++) if(node[t])c++;
                if (c==n) {
                    if (cntPred() == 1) {
                        char outchar[n];
                        for (int k=0;k<n;k++) outchar[k] = out[n-k-1]+'A';
                        printf("Sorted sequence determined after %d relations: %s.\n",
                        II, outchar);
                        // break;
                    }
                }
            }
        }

        if (cntNode()==n && cntPred()> 1)
            cout << "Sorted sequence cannot be determined.\n";
    }



}


