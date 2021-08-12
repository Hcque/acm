#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;
#define MAXN 30

int lch[MAXN], rch[MAXN];
char pre_order[MAXN];
char in_order[MAXN];
int n;
int build(int l1,int r1, int l2, int r2)

{
    if (l1 > r1 ) return 0;
    char node = pre_order[l1];
    int pos;
    for (int i=0;i<r2-l2+1;i++){
        if (in_order[i+l2] == node) {
            pos = i+l2;
            break;
        }
    }
    int l_size = pos-l2;
    int r_size = r2 - pos;

    // int ll = pre_order[l1+1] -'A' + 1;
    int pp = node - 'A' + 1;
    // cout << node << endl;
    // int rr = pre_order[l1+1+l_size] -'A' + 1;
    // cout << "rr:" << l1+1 << "|" << l_size << "| " << n<<" " << ll << " "  << rr << " |"  << l1 << l2 <<  pre_order[l1+1+l_size] << endl;
    // assert(l1+1+l_size < n);
    // if (l1+1+l_size >= n) return;
    // p[ll] = pp;
    // p[rr] = pp;

    lch[pp] =  build(l1+1, l1+l_size, l2, pos-1);
    rch[pp] =  build(l1+l_size+1, r1, pos+1, r2);
    return pp;
}
void dfs(int x)
{
    
    if (lch[x]) dfs(lch[x]);
    if (rch[x]) dfs(rch[x]);
    printf("%c", x+'A'-1);
}
int main()
{
    while (cin >> pre_order >> in_order){
        n=0;
        while (pre_order[n] >= 'A' && pre_order[n] <= 'Z'){
            n++;
        }
        // cout << n << endl;
        
        build(0,n-1, 0,n-1);
        // for (int i=0;i<=n;i++) cout << rch[i] << " ";
        // cout << endl;
    dfs(pre_order[0]-'A'+1);
    printf("\n");
    fill(pre_order,pre_order+MAXN, ' ');
    fill(in_order,in_order+MAXN, ' ');
    }

}


