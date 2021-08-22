// debug: zimu caouctics
// noip infom pass

#include <vector>
#include <stack>
#include <iostream>
using namespace std;

const int MAXN = 2e5+7;
int low[MAXN], dfsn[MAXN], idx = 0, ans=MAXN, n, onStack[MAXN];
stack<int> s;
vector<int> E[MAXN];

void tarjan(int x){
    // for (int i=1;i<=n;i++) cout << dfsn[i] << " ";
    // cout << endl;
    low[x] = dfsn[x] = ++idx;
    s.push(x); onStack[x] = 1;
    for (int i=0;i<E[x].size();i++){
        int v = E[x][i];

        if (!dfsn[v]) 
            tarjan(v);
        if (onStack[v]) low[x] = min(low[x], low[v]);
        else if (onStack[v]) low[x] = min(low[x], dfsn[v]);
    }
    
    if (low[x] == dfsn[x]){
        int cnt = 0;
        while (1){
            int now = s.top(); s.pop();
            onStack[now] = 0;
            cnt++;
            if (now == x) break;
        }
        // cout << "ans:" << ans << "cnt:" <<  cnt << endl;
        if (cnt > 1) ans = min(ans, cnt);
    }

}

int main()
{
    scanf("%d", &n);
    for (int i=1;i<=n;i++){
        int m;
        scanf("%d", &m);

        E[i].push_back(m);
    }
    // for (int i=1;i<=n;i++) cout << dfsn[i] << " ";
    // cout << endl;
    for (int i=1;i<=n;i++){
        if (!dfsn[i]){
            tarjan(i);
        }
    }
    cout << ans << endl;
}
