
// <=, >=, char

// Accepted	148K	0MS	C++	1104B	
// http://poj.org/problem?id=2255


#include <iostream>
using namespace std;

const int N = 300;

int lch[N], rch[N];

char preorder[N], inorder[N];

int build(int l1,int r1, int l2, int r2)
{
    if (l1 > r1) return 0;

    char ans = preorder[l1];
    int mid;
    for (int j = l2; j <= r2; j ++ )
    {
        if (inorder[j] == ans) {
            mid = j;
            break;
        }
    }
    int l_len = mid-l2;
    int r_len = r2-mid;

    lch[ans] = build(l1+1, l1 + l_len, l2, mid-1);
    rch[ans] = build(l1 + l_len + 1, r1, mid+1, r2);

    return ans;
}

void post_order(int now)
{
    if (now == 0) return;
    post_order(lch[now]);
    post_order(rch[now]);
    char ans = now;
    cout << ans;
}
int main()
{
    int a;
    while (   (cin >> preorder >> inorder) )
    {
        int n;
        for (int i = 0; ;i ++)
        {
            if (! (preorder[i]>= 'A' && preorder[i] <= 'Z') ) 
            {
                n = i;
                break;
            }
        }

        // cout << preorder << inorder << endl;
        build(0, n-1, 0, n-1);
        post_order(preorder[0]);
        cout << endl;
    }
    


}