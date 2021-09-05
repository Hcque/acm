#include <unordered_map>
#include <queue>
#include <iostream>
using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

const int maxn = 1e4+6;
class Solution {
public:
unordered_map<TreeNode*, int> m;
queue<TreeNode*> que;
        TreeNode newRoot[maxn];
        unordered_map<TreeNode*,TreeNode*> fa;
        int cnt = 0;

    TreeNode* balanceBST(TreeNode* root) {
        while (que.size()) que.pop();
        m.clear();
         build(root);
         fa[newRoot]=0;
        // for (int i=0;i<=5;i++) cout << newRoot[i].right << " ";
        // cout << endl;
        height(newRoot);
        // for (auto i:fa) {
        //     cout <<((i.first==0) ?0:i.first->val) <<"|"<< ((i.second==0)?0:i.second->val )<< " ";
        // }
        rebalance(newRoot);
        for (int i=0;i<=5;i++) cout << newRoot[i].val << " ";
        cout << endl;
        return newRoot;
    }
    TreeNode* build(TreeNode* now){
        if (now==0) {
            newRoot[cnt++]=0;
            return 0;
        }
        else newRoot[cnt++] = now->val;
        TreeNode* nodeptr = newRoot + cnt-1;
        nodeptr->left = build(now->left); if (now->left)fa[now->left] = nodeptr;
        nodeptr->right = build(now->right); if(now->right) fa[now->right] = nodeptr;
        // cout << "nodeptr" << nodeptr << endl;
        return nodeptr;
    }

    void height(TreeNode* now){
        if (now==NULL) { m[0]=0; return; }
         height(now->left);
         height(now->right);
        m[now] = max(m[now->left] , m[now->right]) + 1;
    }

    void rr(TreeNode*& now){
        cout << "rr" << now << endl;
        TreeNode* l = now->left;
        now->left = l->right;
        l->right = now;
        now = l;
        update(now->right); update(now);
    }
    void lr(TreeNode*& now){
        cout << "lr" << now << endl;
        TreeNode* r = now->right;
        now->right = r->left;
        r->left = now;
        now = r;
        update(now->left); update(now);
    }
    inline void update(TreeNode* now){
        m[now] = max(m[now->left] , m[now->right])+1;
    }

    inline int factor(TreeNode* now){
        if (now==0) return 0;
        return m[now->left] - m[now->right];
    }
    void rebalance(TreeNode* now){
        if (now==0) return;
        rebalance(now->left);
        rebalance(now->right);
        cout << "reb" << now << endl;
        while (now){
            if (factor(now)>1){
                if (factor(now->left)>0) {
                    rr(now->left); rr(now);
                }
                else{
                    lr(now->left); rr(now);
                }
            }
            if (factor(now) < -1){
                if (factor(now->right) < 0){
                    lr(now->right); lr(now);
                }
                else {
                    rr(now->right); lr(now);
                }
            }
            now = fa[now];
        }
    }
};

int main(){
    TreeNode arr[9];
    arr[0] = TreeNode(1);
    arr[1] = TreeNode(2);
    arr[2] = TreeNode(3);
    TreeNode* root1 = arr+0;
    TreeNode* root2 = arr+1;
    TreeNode* root3 = arr+2;

    root1->left = 0; root1->right = root2;
    root2->left = 0; root2->right = root3;
    root3->left = 0; root3->right = 0;
    Solution().balanceBST(arr);
}