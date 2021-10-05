

#include <iostream>
#include <algorithm>
using namespace std;

template <class Record, int order>
struct Node
{
    int count;
    Record data[order-1];
    Node<Record, order> *branch[order];
    Node()
    {
        count = 0;
        fill(data, data+order-1, 0);
        fill(branch, branch+order, nullptr);
    }
};

#define NODE Node<Record, order> 
template <class Record, int order>
class Btree
{
    public:
    NODE *root;

    Btree(){ root = NULL; }
    void ins(NODE *cur, const Record &target)
    {
        if (root == NULL)
        {
            root = new NODE;
            push_in(root,target, 0,0);
            return;
        }

        NODE *right_branch; Record median;
        int res = pushdown(cur, target, median, right_branch);
        if (res == -1)
        {
            NODE* new_root = new NODE;
            new_root->data[0] = median;
            new_root->branch[0] = root;
            new_root->branch[1] = right_branch;
            new_root->count++;
            root = new_root;
        }


    }
            int search_node(NODE *cur,  const Record& target, int &pos)
        {
            if (!cur || cur->count == 0) {
                pos = 0;
                return 0;
            }
            else if (cur->data[cur->count-1] < target)
            {
                pos = cur->count;
                return 0;
            }

            int l = 0, r = cur->count-1;
            while (l < r)
            {
                int mid = l+r >> 1;
                if (cur->data[mid] >= target) r = mid;
                else l = mid + 1;
            }
            pos = r;
            if (cur->data[r] == target) return 1;
            else return 0;
        }

        int rec_search(NODE *cur, const Record &target)
        {
            if (!cur) return 0;

            int pos;
            int res = search_node(cur, target, pos);
            if (res == 1) return 1;
            else{
                res = rec_search(cur->branch[pos], target);
                return res;
            }
        }

        int pushdown(NODE* cur, const Record& target, Record& median, NODE* & right_branch)
        {
            if (!cur )
            {
                median = target;
                right_branch = 0;
                return -1;
            }

            int pos;
            int res = search_node(cur, target, pos);
            if (res == 1) return -2;
            Record extra; NODE* right;
            res = pushdown(cur->branch[pos], target, extra, right);
            if (res == -1)
            {
                if (cur->count < order -1)
                {
                    push_in(cur, target, right, pos);
                    res = 0;
                }
                else split(cur, extra, right, pos, median, right_branch);
            }
            return res;
        }

    void push_in(NODE *cur, const Record& target, NODE* extra_branch, int pos)
    {
        for (int i = cur->count - 1; i >= pos; i --)
        {
            cur->data[i+1] = cur->data[i];
            cur->branch[i+2] = cur->branch[i+1];
        }
        cur->data[pos] = target;
        cur->branch[pos+1] = extra_branch;
        cur->count ++;
    }

    void split(NODE* cur, Record& extra, NODE* extra_branch, int pos, 
                    Record &median, NODE*& right)
    {

        right = new NODE;
        int mid = (order -1 )/2;

        if (pos <= mid)
        {
            for (int i = 0 ; i < mid+1; i ++ )
            {
                right->data[i] = cur->data[i+mid];
                right->branch[i+1] = cur->branch[i+mid+1];
            }
            cur->count = mid; right->count = order-1-mid;
            push_in(cur, extra, extra_branch, pos);
        }
        else {
            mid++;
            for (int i = 0 ; i < mid; i ++ )
            {
                right->data[i] = cur->data[i+mid];
                right->branch[i+1] = cur->branch[i+mid+1];
            }
            cur->count = mid; right->count = order-1-mid;
            push_in(right, extra, extra_branch, pos-mid);
        }
        median = cur->data[cur->count-1];
        right->branch[0] = cur->branch[cur->count];
        cur->count--;
    }

    int remove(const Record& target)
    {
        int res = rec_remove(root, target);
        if (root != NULL && root->count == 0)
        {
            NODE *old_root = root;
            root = root->branch[0];
            delete old_root;
        }
        return res;
    }

    int rec_remove(NODE *cur, const Record &target)
    {
        int pos, res;
        if (!cur) return -1;
        else {
            if (search_node(cur, target, pos))
            {
                res= 1;
                if (cur->branch[pos] != NULL)
                {
                    copy_in_pred(cur, pos);
                    rec_remove(cur->branch[pos], target);
                }
                else remove_data(cur, pos);
            }
            else  res = rec_remove(cur->branch[pos], target);
            if (cur->branch[pos] != NULL)
            {
                if (cur->branch[pos]->count < (order -1 ) /2)
                    restore(cur, pos);
            }
        }
        return res;
    }

    void remove_data(NODE *cur, int pos)
    {
        for (int i = pos; i < cur->count-1; i ++ )
        {
            cur->data[i] = cur->data[i+1];
        }
        cur->count--;
    }

    void copy_in_pred(NODE *cur, int pos)
    {
        NODE *leaf = cur->branch[pos];
        while (leaf->branch[leaf->count]) 
            leaf = leaf->branch[leaf->count];
        cur->data[pos] = leaf->data[cur->count-1];
    }

    void restore(NODE *cur, int pos)
    {
        if (pos == cur->count)
            if (cur->branch[pos-1]->count > (order-1) / 2)
                move_right(cur, pos-1);
            else 
                combine(cur, pos);
        else if (pos == 0)
            if (cur->branch[1]->count > (order-1) / 2)
                move_left(cur, 1);
            else 
                combine(cur, 1);
        else
            if (cur->branch[pos-1]->count  > (order-1)/2)
                move_right(cur, pos-1);
            else if (cur->branch[pos+1]->count  > (order-1)/2)
                move_left(cur, pos+1);
            else 
                combine(cur, pos);
    }
    void move_right(NODE *cur, int pos)
    {
        NODE *left_branch = cur->branch[pos], *right_branch = cur->branch[pos+1];
        right_branch->branch[right_branch->count+1] = right_branch->branch[right_branch->count];
        for (int i = cur->count - 1; i >= 0; i -- )
        {
            right_branch->data[i+1] = right_branch->data[i];
            right_branch->branch[i+1] = right_branch->branch[i];
        }
        right_branch->count++;
        right_branch->data[0] = cur->data[pos];
        right_branch->branch[0] = left_branch->branch[left_branch->count--];
        cur->data[pos] = left_branch->data[left_branch->count];
    }

    void move_left(NODE *cur, int pos)
    {
        NODE *left_branch = cur->branch[pos-1], *right_branch = cur->branch[pos];

        left_branch->data[left_branch->count] = cur->data[pos-1];
        left_branch->branch[left_branch->count+1] = right_branch->branch[0];
        left_branch->count++;
        right_branch->count--;
        for (int i = 0; i < right_branch->count-1; i ++ )
        {
            right_branch->data[i] = right_branch->data[i+1];
            right_branch->branch[i] = right_branch->branch[i+1];
        }
        right_branch->branch[right_branch->count] = right_branch->branch[right_branch->count+1];
    }
    void combine(NODE *cur, int pos)
    {
        NODE *left_branch = cur->branch[pos-1], *right_branch = cur->branch[pos];

        left_branch->data[left_branch->count] = cur->data[pos-1];
        left_branch->branch[left_branch->count+1] = right_branch->branch[0];
        left_branch->count++;
        for (int i = 0; i < right_branch->count; i ++ )
        {
            left_branch->data[i+left_branch->count] = right_branch->data[i];
            left_branch->branch[i + left_branch->count] = right_branch->branch[i+1];
        }
        left_branch->count += right_branch->count ;
        delete right_branch;
        cur->count--;
        for (int i = pos-1; i < cur->count; i ++ )
        {
            cur->data[i] = cur->data[i+1];
            cur->branch[i+1] = cur->branch[i+2];
        }
    }

};

int main(int argc, char *argv[])
{
    Btree<int , 5> bt;
    for (int i = 1 ; i <= atoi(argv[1]); i ++){
        bt.ins(bt.root, i);
        cout <<  bt.rec_search(bt.root, i);
    }
    cout << endl;

    for (int i = 1 ; i <= atoi(argv[1]); i ++){
        bt.remove( i);
        cout <<  bt.rec_search(bt.root, i);
    }
    return 0;



}

