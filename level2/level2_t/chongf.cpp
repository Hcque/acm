

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N =  1e5+10;
int n, a[N];

int find(int x){
    
}


int main()
{
    scanf("%d", &n);
    // cout << n;
    for (int i = 1; i <= n; i ++ ) {
        // cout << i ;
        scanf("%d", &a[i]);
    }
    
    int ans = 0;
    int i = 1, j = i;
    while (i <= n){
        while (j <= n && (j == 1 || a[j] != a[j-1])) {
            j ++ ;
        }
        ans = max(ans, j-i);
        while (a[j] == a[j-1]) j++;
        i = j;
    }
    cout << ans+1 << endl;
}
