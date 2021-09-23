// dfs, +2, +1<n

#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 18;
int n,q[maxn];
int w[5][maxn];
int f(){
    int tot=0;
    for (int i=0;i+1<n;i++){
        if (q[i]+1 != q[i+1]) tot++;
    }
    return (tot+2)/3;
}
bool check(){
    for (int i=1;i<=n;i++){
        if (i!=q[i-1]) return false;
    }
    return true;
}


bool dfs(int d, int maxdepth){
    if (d + f() > maxdepth) return false;
    if (check()) return true;

    for (int len=1;len<=n;len++){
        for (int l = 0;l+len-1<n;l++){

            int r = l+len-1;
            for (int k=r+1;k<n;k++){
                memcpy(w[d], q, sizeof(q));
                int x,y;
                for (x=r+1,y=l;x<=k;x++,y++) q[y] = w[d][x];
                for (x=l;x<=r;x++, y++) q[y] = w[d][x];
                if (dfs(d+1,maxdepth)) return true;
                memcpy(q,w[d], sizeof(q));
            }
        }
    }
    return false;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n); 
        for (int i=0;i<n;i++) scanf("%d", &q[i]);

        int depth = 0;
        while (depth <5 && !dfs(0,depth)) depth++;
        if (depth >= 5) cout << "5 or more" << endl;
        else cout << depth << endl;
    }
}