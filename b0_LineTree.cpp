#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;

const int MAXN = 1e5+10;
const int MAXM = 1e7+10;
int arr[MAXN][2];
int points[MAXN*2];
int maped[MAXN*2];
int dupl[MAXM];
int ansdup[MAXN];
int color_dup[MAXN];

struct Node{
    int l, r;
    int color;
    int low, high;
} LT[MAXN];

int root = 1, cntNode = 0;

int newNode(int L, int R){
    LT[++cntNode].low= L;
    LT[cntNode].high= R;
    return cntNode;
}
int createLT( int L, int R){
    // cout << "LT";
    if (L > R) return 0;
    else if (L==R) return newNode(L,R);
    else {
        int cur = newNode(L, R);
        int mid = (L+R)>>1;
        LT[cur].l = createLT(L, mid);
        LT[cur].r = createLT(mid+1, R);
        return cur;
    }
}
void insertColor(int now, int L, int R, int color){
        // cout << color << " ";
    if (LT[now].high < L || LT[now].low > R){
        return;
    }
    else if (L <=LT[now].low && LT[now].high<=R){
        LT[now].color = color;
        // cout << color << " ";
        return;
    }
    else {
        if (LT[now].color > 0){
            LT[LT[now].l].color = LT[LT[now].r].color = LT[now].color;
        }
        LT[now].color = -1; // indicate multiple color
        insertColor(LT[now].l, L, R, color);
        insertColor(LT[now].r, L, R, color);
    }
}
void dfs(int now, int& ans){
    // cout << LT[now].color << " ";
    if (!now) return;
    else if (LT[now].color == 0) return;
    else if (LT[now].color > 0){
        // cout << LT[now].color << " ";
        if (color_dup[LT[now].color] == 0){
            ans++;
            color_dup[LT[now].color] = 1;
        }
    }
    else {
        dfs(LT[now].l, ans);
        dfs(LT[now].r, ans);
    }
}


int main(){
    int T;
    cin >> T;
    while (T--){
        int N;
        cin >> N;
        memset(arr, 0, sizeof(arr));
        memset(points, 0, sizeof(points));
        memset(maped, 0, sizeof(maped));
        memset(dupl, 0, sizeof(dupl));
        memset(color_dup, 0, sizeof(color_dup));
        int c = 0;
        for (int i=1;i<=N;i++){
            int a, b;
            cin >> arr[i][0] >> arr[i][1];
            for (int k = 0;k <=1; k++){

            if (dupl[arr[i][k]] == 0) {
                points[++c] = arr[i][k];
                dupl[arr[i][k]] = 1;
            }
            
            }

        }
        sort(points+1, points+c+1);
        int cnt = 0;
        for (int i= 1;i<=c;i++){
            maped[points[i]] = ++cnt;
        }

        createLT(1, cnt);
        int color = 0;
        for (int i = 1; i<=N;i++){
            color++;
            int lo = maped[arr[i][0]];
            int hi = maped[arr[i][1]];
            insertColor(root, lo, hi, color);
        }

        int ans = 0;
        dfs(root, ans);
        cout << ans << endl;
    }
}