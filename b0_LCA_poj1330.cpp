// 1636K	172MS

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 1e4+10;
const int LOG = 14;
int fa[maxn][LOG+1];
int depth[maxn], root;

void dfs(int now, vector<vector<int>>& child){

    for (int i=0;i<child[now].size();i++){
        depth[child[now][i]] = depth[now]+1;
        dfs(child[now][i], child);
    }
}
void goUp(int &x, int len){
    int c=0;
    while ((1<<c) <= len) c++;

    for (int i=0;i<c;i++){
        if ((1<<i)&(len)){
            x = fa[x][i]; 
        }
    }
}

int LCA(int x, int y){
    if (depth[x] < depth[y]){
        swap(x, y);
    }
    // depth x > depth y
    goUp(x, depth[x]-depth[y]);
    if (x==y) return x;
    int c=0; while ((1<<c) <= depth[y]) c++;
    for (int i=c-1;i>=0;i--){
        if (fa[x][i] != fa[y][i]){
            x = fa[x][i], y=fa[y][i];
        }
    }
    return fa[x][0];
}

int main(){
    int T;
    scanf("%d", &T);
    while (T--){
        int N;
        memset(fa, 0, sizeof(fa));
        memset(depth, 0, sizeof(depth));
        scanf("%d", &N);
        vector<vector<int>> child(maxn);
        for (int i=1;i<=N-1;i++){
            int p, x;
            scanf("%d %d", &p, &x);
            fa[x][0] = p;
            child[p].push_back(x);
            // cout << p << "|" << x  << endl;
        }

        for (int j=1;j<=LOG;j++){
            for (int i=1;i<=N;i++){
                fa[i][j] = fa[ fa[i][j-1]][j-1];
            }
        }
        int qa, qb;
        scanf("%d %d", &qa, &qb);

        for (int i=1;i<=N;i++) {
            if (fa[i][0]==0) {
                root = i; 
                break;
            }
        }
        // get depth
        dfs(root, child);
        cout << LCA(qa, qb) << endl;
    }
}