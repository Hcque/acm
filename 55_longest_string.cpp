#include <iostream>
#include <string>

using namespace std;

#define MAXN 10
int dp[MAXN][MAXN];

int main(){
    string s;
    cin >> s;
    s = 'A' + s;
    cout << s << endl;
    char ans[2*MAXN];
    int head = MAXN;
    int tail = MAXN;
    int L = s.size();
    for (int ll=1;ll<=L;ll++){
        for (int i=1;i<=L;i++){
    	    int j = i+ll-1;
            if (j > L+1) {
                dp[i][j] = 0;
            }

            if (i==j) {
                dp[i][j] = 1;
                ans[head--] = s[i];
            }
            else if (j==i+1) {
                dp[i][j] = (s[i] == s[j]);
                ans[]
            }
            else {
                bool res = 0;
                if (s[i] == s[j]) res = dp[i+1][j-1];
                else {
                    res = dp[i+1][j] || dp[i][j+1];
                }
                dp[i][j] = res;
            }
            if (dp[i][j] && ans.size() < ll) ans = s.substr(i,ll);
        }
    }
    cout << ans;
    return 0;

}
