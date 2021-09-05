#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;

const int MAXN = 1e5+10;
const int MAXM = 1e7+10;
int arr[MAXN][2];
int points[MAXN*2];
int wall[MAXN*2];
int maped[MAXN*2];
int dupl[MAXM];
int ansdup[MAXN];


int main(){
    int T;
    cin >> T;
    while (T--){
        int N;
        cin >> N;
        memset(arr, 0, sizeof(arr));
        memset(points, 0, sizeof(points));
        memset(wall, 0, sizeof(wall));
        memset(maped, 0, sizeof(maped));
        memset(dupl, 0, sizeof(dupl));
        memset(ansdup, 0, sizeof(ansdup));
        // set<int> pointset;
        // pointset.clear();
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
        int color = 0;
        for (int i = 1; i<=N;i++){
            color++;
            for (int j =maped[ arr[i][0] ]; j <= maped[ arr[i][1]] ; j++){
                wall[j] = color;
            }
        }
        // for (int i=1;i<10;i++) cout << wall[i] << " ";

        int ans = 0;
        
        for (int i=1;i<=cnt;i++){
            if (wall[i] != 0 && ansdup[wall[i]] == 0){
                ansdup[wall[i]] = 1;
                ans++;
            }
        }
        cout << ans << endl;
    }
}