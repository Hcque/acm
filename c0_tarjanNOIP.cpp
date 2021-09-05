
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int maxn = 2e5+5;
std::vector<int> E[maxn];
std::stack<int> s;

int dfsn[maxn], onStack[maxn], low[maxn];
int idx=0, ans = 1e9;
void targan(int &u){
    low[u] = dfsn[u] = ++idx;
    onStack[u]=1; s.push(u);
    for (int i=0;i<E[u].size();i++){
        int v = E[u][i];
        if (!dfsn[v]) targan(v);
        if (onStack[v]) low[u] = min(low[u], low[v]);
    }

    if (low[u]==dfsn[u]){
        int c = 0;
        while (1) {
            int x = s.top(); s.pop();
            onStack[x] = 0;
            c++;
            if (x == u) break;
        }
        if(c>1) ans = min(ans, c);
    }
}
int main(){
    int T;
    cin >> T;
    for (int i=1;i<=T;i++){
        int t;
        cin >> t;
        E[i].push_back(t);
    }

    for (int i=1;i<=T;i++){
        if (!dfsn[i]) {
            targan(i);
        }
    }
    cout << ans << endl;

}