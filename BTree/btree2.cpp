//const
// int &



#include <iostream>
#include <algorithm>

using namespace std;

template < class Record, int order>
struct B_node
{
    int count;
    Record data[order-1];
    B_node<Record, order> *branch[order];
    B_node()
    {
        count = 0;
        fill(data, data+order-1, 0);
        fill(branch, branch+order, nullptr);
    }
};

#define NODE B_node<Record,order>

template <class Record, int order>
class B_tree
{
public:
    NODE *root;
    B_tree(){ root = NULL; } 

    void vis(NODE *cur)
    {
        if (!cur) return;
        for (int i = 0; i < cur->count; i ++ )
        {
            vis(cur->branch[i]);
            cout << cur->data[i] << endl;
        }
        vis(cur->branch[cur->count]);

    }

    int rec_search(NODE *cur, const Record &target)
    {
        if (cur == NULL) return 0;
        int pos, res;
        res = search_node(cur, target, pos);
        if (!res) res = rec_search(cur->branch[pos], target);
        return res;
    }
    
    void insert(NODE *cur, const Record& target)
    {
        if (root == NULL)
        {
            root = new NODE;
            root->count = 1;
            root->data[0] = target;
        }
        else {
            NODE *right_branch; Record median;
            int res = pushdown(cur, target, median, right_branch);
            if (res == -1){
                NODE *new_root = new NODE;
                new_root->count = 1;
                new_root->data[0] = median;
                new_root->branch[0] = root;
                new_root->branch[1] = right_branch;
                root = new_root;
            }
        }
    }

    int pushdown(NODE *cur,const Record &new_entry, Record& median, NODE *&right_branch)
    {
        if (cur== NULL){
            median = new_entry;
            right_branch = 0;
            return -1;
        }
        else {
            int pos;
            int res = search_node(cur, new_entry, pos);
            if (res == 1) return -2;
            NODE *extra_branch; Record extra_entry;
            res = pushdown(cur->branch[pos], new_entry, extra_entry, extra_branch);
            if (res == -1)
            {
                if (cur->count < order -1 )
                {
                    res = 0;
                    push_in(cur, extra_entry, extra_branch, pos);
                }
                else split(cur, extra_entry, extra_branch, pos, right_branch, median);
            }
            return res;
        }
    }

    int search_node(NODE *cur, const Record& target, int &pos)
    {
        pos = 0;
        while (pos < cur->count && cur->data[pos]< target) pos++;
        if (pos < cur->count && cur->data[pos] == target) return 1;
        return 0;
    }

    void push_in(NODE *cur, Record& new_entry, NODE *right_branch, int pos)
    {
        // not full
        for (int i = cur->count-1; i >= pos; i -- )
        {
            cur->data[i+1] = cur->data[i];
            cur->branch[i+2] = cur->branch[i+1];
        }
        cur->data[pos] = new_entry;
        cur->branch[pos+1] = right_branch;
        cur->count++;
    }

    void split(NODE *cur, Record& extra_entry, NODE *extra_branch, int pos, 
    NODE *&right_branch, Record &median)
    {
        right_branch = new NODE;
        int mid = order >>1;
        if (pos <= mid)
        {
            for (int i = mid; i < order-1; i ++)
            {
                right_branch->data[i-mid] = cur->data[i];
                right_branch->branch[i+1-mid] = cur->branch[i+1];
            }
            cur->count = mid; right_branch->count = order -1 - mid;
            push_in(cur, extra_entry, extra_branch, pos);
        }

        else{
            mid++;
            for (int i = mid; i < order-1; i ++)
            {
                right_branch->data[i-mid] = cur->data[i];
                right_branch->branch[i+1-mid] = cur->branch[i+1];
            }
            cur->count = mid; right_branch->count = order -1 - mid;
            push_in(right_branch, extra_entry, extra_branch, pos-mid);
        }
        median = cur->data[cur->count-1];
        right_branch->branch[0] = cur->branch[cur->count];
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
        cur->data[pos-1] = right_branch->data[0];
        left_branch->count++;
        right_branch->count--;
        for (int i = 0; i < right_branch->count; i ++ )
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

int main(int argc, char* argv[])
{
    B_tree<int , 5> bt;
    int I = atoi(argv[1]);
    int R = atoi(argv[2]);
    for (int i = 1; i <= I; i ++)
        bt.insert(bt.root,i);
    for (int i = 1; i <= I; i ++)
        cout << bt.rec_search(bt.root,i) << endl;
    
    cout << "=========" << endl;
    bt.vis(bt.root);
    cout << "remove=========" << endl;
    
    for (int i = 1; i <= R; i ++)
        cout << bt.remove(i) << endl;
cout << "after remove=========" << endl;
  for (int i = 1; i <= R; i ++)
    cout << bt.rec_search(bt.root,i) << endl;
cout << "=========" << endl;
bt.vis(bt.root);
}

