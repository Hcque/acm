
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;


const int N = 1e5+10;

char tr[N][27], cnt[N];
int idx;

int n;

void ins(const string& ss){
    int p = 0;
    for (int i=0;i<ss.size();i++){
        char now = ss[i];
        int k = now-'a';
        if (!tr[p][k]) tr[p][k] = ++idx;
        p = tr[p][k]; 
        
    }
    cnt[p] ++;
}

int query(const string& ss)
{
    int p = 0;
    for (int i=0;i<ss.size();i++){
        char now = ss[i];
        int k = now-'a';
        if (!tr[p][k]) return 0;
        p = tr[p][k]; 
        
    }
    return cnt[p];
    
}


int main()
{
    cin >> n;
    while (n -- )
    {
        string op, ss;
        cin >> op >> ss;
        // cout << op ;
        if (op == "I"){
            ins(ss);
        }
        else{
            cout << query(ss) << endl;
        }
        
  
    }
}