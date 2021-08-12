#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;
#define MAXV 200000

int in_order[MAXV];
int post_order[MAXV];
int lch[MAXV];
int rch[MAXV];

int n;
int best_;
int best_n;

bool read_list(int* arr)
{
    n = 0;
    int i;
    int a = 0;
    string L;
    getline(cin, L);
    // cout << L << endl;
    stringstream ss(L);
    while (ss >> i) arr[a++] = i;
    n = a;
    return true;
}

int build(int l1, int r1, int l2, int r2)
{
    if (l1>r1) return 0;
    // cout << l1 << " " << r1 << endl;
    int root = post_order[r2];
    int p = l1;
    while (in_order[p] != root) p++;
    int cnt = p-l1;
    lch[root] =  build(l1, p-1, l2,l2+cnt-1);
    rch[root] =  build(p+1,r1, l2+cnt,r2-1);
    return root;
}

void dfs(int u, int sum)
{
    sum += u;
    if (!lch[u] && !rch[u]){
       if (sum < best_){
          best_ = sum;
	  best_n = u;
	  sum = 0;
       }
    }
    
    if (lch[u]) dfs(lch[u], sum);
    if (rch[u]) dfs(rch[u], sum);
}

int main()
{
   while (!cin.eof()){
    best_ = INT_MAX;
    best_n = -1;
    fill(lch, lch+MAXV, 0);
    fill(rch, rch+MAXV, 0);

   read_list(in_order);
   read_list(post_order);
   build(0,n-1, 0, n-1);
   dfs(post_order[n-1], 0);
   cout << best_n << endl;
   }

   return 0;
}
