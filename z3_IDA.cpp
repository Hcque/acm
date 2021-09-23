 // ac

#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 16;
int n, q[maxn];
int w[5][maxn];
int f(){
    int tot=0;
    for (int i=0;i+1<n;i++){
        if (q[i]+1 != q[i+1]) tot++;
    }
    return (tot+2)/3;
}

bool check(){
    for (int i=0;i<n;i++){
        if (q[i] != i+1) return false;
    }
    return true;
}

bool dfs(int depth, int maxdepth){
    // cout << "depth" <<  depth << endl;

    if (depth + f() > maxdepth) return false;
    if (check()) return true;

    for (int len = 1;len<=n;len++){
        for (int l=0;l+len-1<n;l++){
            int r =l+len-1;
            for (int k=r+1;k<n;k++){
                memcpy(w[depth],q, sizeof(q));
                int x,y;
                for (x=r+1,y=l;x<=k;x++,y++) q[y] = w[depth][x];
                for (x=l;x<=r;x++,y++) q[y] = w[depth][x];
                if (dfs(depth+1,maxdepth)) return true;
                memcpy(q,w[depth], sizeof(q));
            }
        }
    }
    return false;
}
int main(){
    int T;
    scanf("%d", &T);
    // cout << T << endl;
    while (T--){
        scanf("%d", &n);
        for (int i=0;i<n;i++) scanf("%d",&q[i]);

        int depth=0;
        while (depth<5 && !dfs(0,depth)) depth++;
        if (depth>=5) cout << "5 or more" << endl;
        else cout << depth<< endl;
    }
}