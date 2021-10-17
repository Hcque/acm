
// left - 1 in move left 
// move right +1
// right / left 

// ++ / --

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;
#define NODE Node<Record, order>

const int N = 1e5+10;

int n,m;
int a[N];

template <class Record, int order>
struct Node{
    int size;
    Record data[order-1];
    NODE* branch[order];
    Node(): size(0) {
        fill(branch, branch+order, nullptr);
        fill(data, data+order-1, 0);
    }
};


template <class Record, int order>
class B_tree
{
public:
    B_tree() { root = nullptr; }
    ~B_tree(){
        void clear();
    }

    void rec_visit(NODE* cur, int cnt)
    {
        if (!cur) return;
        rec_visit(cur->branch[0], cnt);
        for (int i = 0; i < cur->size; i ++ )
        {
            cout << cur->data[i] << " "; cnt ++;
            rec_visit(cur->branch[i+1],cnt);
        }
    }
    int insert(NODE* cur, const Record& new_entry)
    {
        if (!root)
        {
            root = new NODE;
            root->data[0] = new_entry;
            root->size++;
            return 0;
        }
        int pos; Record median; NODE* right;
        int res = push_down(cur, new_entry, median, right);
        NODE* new_root;
        if (res == -1)
        {
            new_root = new NODE;
            new_root->size = 1;
            new_root->data[0] = median;
            new_root->branch[0] = root;
            new_root->branch[1] = right;
            root = new_root;
        }
    }

    int push_down(NODE* cur, const Record& new_entry, Record& median, NODE*& right_branch)
    {
        if (!cur)
        {
            median = new_entry;
            right_branch = 0;
            return -1;
        }
        int pos, res;
        res = find_record(cur, new_entry, pos);
        if (res) return -2;
        NODE* extra_branch; Record extra;
        res = push_down(cur->branch[pos], new_entry, extra, extra_branch);
        if (res == -1)
        {
            if (cur->size < order-1)
            {
                res = 0;
                push_in(cur, extra, extra_branch,pos);
            }
            else{
                split(cur, median, right_branch,extra, extra_branch, pos );
            }
            return res;
        }
    }
    void split(NODE* cur, Record& median, NODE*& right, Record& extra, NODE* extra_branch, int pos)
    {
        assert(cur->size == order-1);
        int mid = (cur->size+1) / 2;
        right = new NODE;
        if (pos <= mid)
        {
            for (int i = mid; i < cur->size; i ++ )
            {
                right->data[i-mid] = cur->data[i];
                right->branch[i-mid+1] = cur->branch[i+1];
            }
            cur->size = mid; right->size = order-1 - mid;
            push_in(cur, extra, extra_branch, pos);
        }
        else{
            mid++;
            for (int i = mid; i < cur->size; i ++ )
            {
                right->data[i-mid] = cur->data[i];
                right->branch[i-mid+1] = cur->branch[i+1];
            }
            cur->size = mid; right->size = order-1 - mid;
            push_in(right, extra, extra_branch, pos-mid);
        }
        median = cur->data[cur->size-1];
        right->branch[0] = cur->branch[cur->size];
        cur->size--;
    }

    int push_in(NODE* cur, const Record& new_entry,NODE* right, int pos)
    {
        for (int i = cur->size; i > pos; i -- )
        {
            cur->data[i] = cur->data[i-1];
            cur->branch[i+1] = cur->branch[i];
        }
        cur->data[pos] = new_entry;
        cur->branch[pos+1] = right;
        cur->size++;
        return 0;
    }

    bool find_record(NODE* cur,const Record& target, int& pos)
    {
        pos = 0;
        while (pos < cur->size && cur->data[pos] < target ) pos++;
        if (pos < cur->size && cur->data[pos] == target ) return true;
        return false;
    }

    bool search(NODE* cur, Record& target)
    {
        if (!cur) return false;
        int pos;
        if (find_record(cur, target, pos)) return true;
        else return search(cur->branch[pos], target);
    }
    NODE* root;

    // remove

    bool remove(const Record& entry)
    {
        int res = rec_remove(root, entry);
        if (root != nullptr && root->size == 0)
        {
            NODE* old_root = root;
            root = root->branch[0];
            delete old_root;
        }
        return res;
    }

    bool rec_remove(NODE* cur, const Record& entry)
    {
        if (!cur) return false;
        int pos;
        if (find_record(cur,entry, pos)) 
        {
            if (cur->branch[pos])
            {
                copy_pred(cur, pos);
                rec_remove(cur->branch[pos], cur->data[pos]);
            }
            else remove_node(cur, pos);
        }
        else return rec_remove(cur->branch[pos], entry);

        if (cur->branch[pos] && cur->branch[pos]->size < (order-1)/2)
            restore(cur, pos);
        return 1;
    }

    void restore(NODE* cur, int pos)
    {
        cerr << "restore\n";
        if (pos == 0)
        {
            if (cur->branch[pos+1]->size > (order-1)/2) move_left(cur, pos+1);
            else combine(cur, pos+1);
        }
        else if (pos == cur->size)
        {
            if (cur->branch[pos-1]->size > (order-1)/2) move_right(cur, pos-1);
            else combine(cur, pos);
        }
        else{
            if (cur->branch[pos-1]->size > (order-1)/2) move_right(cur, pos-1);
            else if (cur->branch[pos+1]->size > (order-1)/2) move_left(cur, pos+1);
            else combine(cur, pos);
        }
    }
    void move_left(NODE* cur, int pos)
    {
        NODE* left = cur->branch[pos-1];
        NODE* right = cur->branch[pos];
        left->data[left->size] = cur->data[pos-1];
        left->branch[++left->size] = right->branch[0];
        cur->data[pos-1] = right->data[0];
        right->size--;

        for (int i = 0; i < right->size; i ++ )
        {
            right->data[i] = right->data[i+1];
            right->branch[i] = right->branch[i+1];
        }
        right->branch[right->size] = right->branch[right->size+1];
    }
    void move_right(NODE* cur, int pos)
    {
        NODE* left = cur->branch[pos];
        NODE* right = cur->branch[pos+1];

        right->branch[right->size+1] = right->branch[right->size];
        for (int i = right->size;i >0; i -- )
        {
            right->data[i] = right->data[i-1];
            right->branch[i] = right->branch[i-1];
        }
        right->size++;
        right->data[0] = cur->data[pos];
        right->branch[0] = left->branch[left->size--];
        cur->data[pos] = left->data[left->size];
    }

     void combine(NODE* cur, int pos)
    {
        NODE* left = cur->branch[pos-1];
        NODE* right = cur->branch[pos];
        left->data[left->size] = cur->data[pos-1];
        left->branch[++left->size] = right->branch[0];

        for (int i = 0; i < right->size; i ++ )
        {
            left->data[left->size] = right->data[i];
            left->branch[++left->size] = right->branch[i+1];
        }
        cur->size--;
        for (int i = pos-1; i < cur->size; i ++ )
        {
            cur->data[i] = cur->data[i+1];
            cur->branch[i+1] = cur->branch[i+2];
        }
        delete right;
    }



    void remove_node(NODE* cur, int pos)
    {
        std::cerr << "remove node"  << cur->data[pos] << "\n";
        for (int i = pos; i < cur->size-1; i ++)
            cur->data[i] = cur->data[i+1];
        cur->size--;
    }
    void copy_pred(NODE* cur, int pos)
    {
        NODE* tmp = cur->branch[pos];
        while ( tmp->branch[tmp->size]) tmp = tmp->branch[tmp->size];
        cur->data[pos] = tmp->data[tmp->size-1];
    }
};


// int main()
// {
//     BTree<int, 20> bt;
//     for (int i = 1; i <= n; i ++ ) {
//         bt.insert(bt.root, i);
//     }

//     bt.rec_visit(bt.root,0);
//     for (int i = 1; i <= n; i ++ ) {
//         bt.remove( i);
//     }
//     bt.rec_visit(bt.root,0);
    
    
    
// }

B_tree<int, 5> bt;
int main(int argc, char* argv[])
{
    int II = atoi(argv[1]);

    for (int i = 1; i <= II; i ++ ) 
        bt.insert(bt.root, i);
    for (int i = 1; i <= II; i ++ ) 
        bt.remove( i);

    for (int i = 1; i <= II; i ++ ) 
        cout << bt.search(bt.root, i) ;
}