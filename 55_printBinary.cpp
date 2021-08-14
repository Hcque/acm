#include <iostream>

using namespace std;
#define MAXN 4
char ans[MAXN];
void rec_print(int x)
{
    if (x == 0) {
        for (int i=1;i<MAXN;i++){
            cout << ans[i] << " ";    
        }
        cout << endl;
        return;
    }
    ans[x] = '0';
    rec_print(x-1);
    ans[x] = '1';
    rec_print(x-1);
}


int main()
{
    int N;
    cin >> N;
    rec_print(N);
    return 0;
}
