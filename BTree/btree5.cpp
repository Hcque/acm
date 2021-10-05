#include <algorithm>
#include <iostream>
using namespace std;

#define NODE Node<Record, order>
template <class Record, int order>
struct Node
{
    int count;
    Record data[order-1];
    NODE *branch[order];
    Node()
    {
        count = 0;
        fill(data, data+order-1,0);
        fill(branch, branch+order,nullptr);
    }
};

template <class Record, int order>
class BTree
{
public:
    BTree() { root = nullptr; }
    int ins(NODE *cur, const Record& target)
    {
        if (!root) {
            root = new NODE;
            root->data[0] = target;
            return -1;
        }
        Record median; NODE *right;
        int res = pushdown(cur, target, median, right);
        if (res == -1)
        {
            NODE *new_root = new NODE;
            new_root->data[0] = median;
            new_root->branch[0] = root;
            new_root->branch[1] = right;
            root = new_root;
        }
        return res;
    }

    int rec_search(NODE *cur, const Record& target)
    {
        if (!cur) return 0;
        int pos;
        int res = search_node(cur, target, pos);
        res = rec_search(cur->branch[pos], target);
        return res;
    }

private:
    int pushdown(NODE *cur, const Record& entry, Record& median, NODE* &right)
    {
        if (!cur)
        {
            median = entry;
            right = 0;
            return -1;
        }

        int pos;
        int res = search_node(cur, entry, pos);
        cout << "======"<<pos << endl;
        if (res == 1) return -2;
        Record extra; NODE* extra_branch;
        res = pushdown(cur->branch[pos], entry, extra, extra_branch);
        if (res == -1)
        {
            if (cur->count < order-1){
                res = 0;
                push_in(cur, extra,extra_branch, pos );
            }
            else split(cur, extra, extra_branch, pos, median, right);
        }
        return res;
    }

    void split(NODE * cur, Record& extra, NODE * extra_branch, int pos, Record &median, NODE* &right)
    {
        int mid = (cur->count-1)/2;
        right = new NODE;
        if (pos <= mid)
        {
            for (int i = mid; i < cur->count; i ++ )
            {
                right->data[i-mid] = cur->data[i];
                right->branch[i-mid+1] = cur->branch[i+1];
            }
            right->count = order-1-mid; cur->count = mid;
            push_in(cur, extra, extra_branch, pos);
        }
        else{
            mid++;
            for (int i = mid; i < cur->count; i ++ )
            {
                right->data[i-mid] = cur->data[i];
                right->branch[i-mid+1] = cur->branch[i+1];
            }
            right->count = order-1-mid; cur->count = mid;
            push_in(right, extra, extra_branch, pos -mid);
        }
        median = cur->data[cur->count-1];
        right = cur->branch[cur->count];
        cur->count--;
    }

    void push_in(NODE* cur, const Record &target, NODE *extra_branch, int pos)
    {
        for (int i = cur->count-1; i >= pos; i --)
        {
            cur->data[i+1] = cur->data[i];
            cur->branch[i+2] = cur->branch[i+1];
        }
        cur->data[pos] = target;
        cur->branch[pos] = extra_branch;
        cur->count ++ ;
    }

    int search_node(NODE *cur, const Record& target, int &pos)
    {
        pos = 0;
        while (pos < cur->count && cur->data[pos] < target) pos++;
        if (pos < cur->count && cur->data[pos] == target) return 1;
        else return 0;
    }
public:

    NODE *root;


};

int main(int argc, char *argv[])
{
    BTree<int , 5> bt;
    for (int i = 1; i <= atoi(argv[1]); i ++ )
    {
        bt.ins(bt.root, i);
        cout << bt.rec_search(bt.root, i);
    }
    return 0;
}