// BTREE tested

#include <iostream>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <vector>


using namespace std;
using milli = std::chrono::milliseconds;

int search_way = 0;

template <class Record, int order>
struct B_node
{
    int count;
    Record data[order-1];
    B_node<Record, order>* branch[order];// = {nullptr};
    B_node():count(0) {
        fill(data,data+order-1, 0);
        fill(branch,branch+order, nullptr);
    }
};

template <class Record, int order>
class B_tree
{
public:
B_tree(){
    root = NULL;
}

int search_tree(Record &target);
void insert(const Record& new_entry);
int remove(const Record &target);

void ff_vis()
{
    // cout << " ========= VISIT +++++++++=============\n";
    visit(root);
}
// traserval
void visit(B_node<Record, order>* cur)
{
    if (!cur) return;

    for (int i = 0; i < cur->count; i ++ ){
        visit(cur->branch[i]);
        cout << cur->data[i] << endl;
    }

    visit(cur->branch[cur->count]);
}

private:
int rec_search_tree(B_node<Record, order>*cur, Record &target);
int search_node(B_node<Record, order>*cur, const Record &target, int& pos);

// insert
int pushdown(B_node<Record, order>*cur,
                             const Record &new_entry,
                                Record &median,
                                 B_node<Record, order>* &right_branch);
void push_in(B_node<Record, order>*cur,
                             const Record &new_entry,
                             B_node<Record, order>*right_branch, int pos);

void split_node(B_node<Record, order>*cur,
                             const Record &extra_entry,
                             B_node<Record, order>*extra_branch, int pos,
                              B_node<Record,order> *&right_half,
                             Record &median);

// delete
int rec_remove(B_node<Record, order> *cur,
                                    const Record &target);

void remove_data(B_node<Record, order> *cur,
                                    int pos);

void copy_in_predecessor(B_node<Record, order> *cur,int pos);
void restore(B_node<Record, order> *cur,int pos);

void move_left(B_node<Record, order> *cur,int pos);
void move_right(B_node<Record, order> *cur,int pos);
void combine(B_node<Record, order> *cur,int pos);

private:
    B_node<Record, order>* root;
};


template <class Record, int order>
int B_tree<Record, order>::search_tree(Record &target)
{
    return rec_search_tree(root, target);
}

template <class Record, int order>
int B_tree<Record, order>::rec_search_tree(B_node<Record, order>*cur, 
Record &target)
{
    int pos;
    int res = 0;
    cout << cur << "|" << target << endl;
    if (cur != NULL)
    {
        res = search_node(cur, target, pos);
        if (!res) res = rec_search_tree(cur->branch[pos], target);

    }
    return res;
}

template <class Record, int order>
int B_tree<Record, order>::search_node(B_node<Record, order>* cur, 
                    const Record &target, int &pos)
{
if (search_way){
    if (cur->count == 0) 
    {
        pos = 0;
        return 0;
    }
    if (cur->data[cur->count-1] < target) {
        pos = cur->count;
        return 0;
    }

    // find bisect
    cout << "begin bisect" << endl;
    int l = 0 , r = cur->count-1;
    while (l < r)
    {
        int mid = l+r >> 1;
        if (cur->data[mid] >= target ) r = mid;
        else l = mid+1;
    }
    pos = l;
    if (cur->data[l] == target) return 1;
    else return 0;
}
else {
    pos = 0;
    while (pos < cur->count && target > cur->data[pos]) pos++;
    if (pos < cur->count && target == cur->data[pos]) return 1;
    return 0;
}
}

template <class Record, int order>
void B_tree<Record, order>::insert(const Record& new_entry)
{
    // cout << "insert begin  " << new_entry << endl;

    if (!root) {
        root = new B_node<Record, order>;
        root->data[0] = new_entry;
        root->count ++;
        return;
    }
    Record median;
    B_node<Record, order> *right_branch, *new_root;
    int result = pushdown(root, new_entry, median, right_branch);
    if (result == -1)
    {
        new_root = new B_node<Record, order>;
        // cout << "==============insert new root"  << new_root << endl;
        new_root->count = 1;
        new_root->data[0] = median;
        new_root->branch[0] = root;
        new_root->branch[1] = right_branch;
        root = new_root;

        result = 0;
    }
}

template <class Record, int order>
int B_tree<Record, order>::pushdown(B_node<Record, order>*cur,
                             const Record &new_entry,
                                Record &median,
                                 B_node<Record, order>* &right_branch)
{
    int pos;
    // cout << "pushdown to cur:" << cur << endl;
    if (cur == NULL)
    {
        // cout << "no way of insert to null" << endl;
        median = new_entry;
        right_branch = 0;
        return -1;
    }
    else{
        int res = search_node(cur, new_entry, pos);
        if ( res ) {
            // cout << res << "search dup" << endl;
            return -2;
        }

        else{

            Record extra_entry; B_node<Record, order>* extra_branch;
            int res = pushdown(cur->branch[pos], new_entry, extra_entry, extra_branch);
            if (res == -1)
            {
                // cout <<  " =======cur count: " << cur->count << endl;
                if (cur->count < order-1){
                    res = 0;
                    push_in( cur, extra_entry, extra_branch, pos );
                }
                else split_node(cur, extra_entry, extra_branch, pos,right_branch, median);
            }
            return res;
        }
    }
}


template <class Record, int order>
void B_tree<Record, order>::push_in(B_node<Record, order>*cur,
                             const Record &new_entry,
                             B_node<Record, order>*right_branch, int pos)
{
    for (int i = cur->count ; i > pos; i--)
    {
        cur->data[i] = cur->data[i-1];
        cur->branch[i+1] = cur->branch[i];
    }
    cur->data[pos] = new_entry;
    cur->branch[pos+1] = right_branch;
    cur->count++;
}

template <class Record, int order>
void B_tree<Record, order>::split_node(B_node<Record, order>*cur,
                             const Record &extra_entry,
                             B_node<Record, order>* extra_branch, 
                             int pos,
                             B_node<Record,order>*&right_half,
                             Record &median)
{
    right_half = new B_node<Record, order>;
    // cout << "====================begin split" << right_half << endl;
    // cout << pos << endl;
    int mid = order/2;
    if (pos <= mid)
    {
        for (int i = mid; i < order-1; i++)
        {
            right_half->data[i-mid] = cur->data[i];
            right_half->branch[i+1-mid] = cur->branch[i+1];
        }
        cur->count = mid; right_half->count = order-1-mid;
        push_in(cur, extra_entry, extra_branch, pos);
    }
    else {
        mid++;
        for (int i = mid; i < order-1; i++)
        {
            right_half->data[i-mid] = cur->data[i];
            right_half->branch[i+1-mid] = cur->branch[i+1];

        }
        cur->count = mid; right_half->count = order-1-mid;
        push_in(right_half, extra_entry, extra_branch, pos-mid);
    }

    median = cur->data[cur->count-1];
    right_half->branch[0] = cur->branch[cur->count];
    cur->count--;

}

// delete
template <class Record, int order>
int B_tree<Record, order>::remove(const Record &target)
{
    int res = rec_remove(root, target);
    if (root != NULL && root->count == 0)
    {
        B_node<Record, order> *old_root = root;
        root = root->branch[0];
        delete old_root;
    }
    return res;
}


template <class Record, int order>
int B_tree<Record, order>::rec_remove(B_node<Record, order> *cur,
                                    const Record &target)
{
    int pos; int res;
    if (cur == NULL) return -1;
    else{
        if (search_node(cur, target, pos) == 1)
        {
            res = 1;
            if (cur->branch[pos] != NULL){ // not a leaf node
                copy_in_predecessor(cur, pos);
                rec_remove(cur->branch[pos], cur->data[pos]);
            }
            else remove_data(cur, pos); // leaf node
        }
        else res = rec_remove(cur->branch[pos], target);
        if (cur->branch[pos] != NULL)
        {
            if (cur->branch[pos]->count < (order-1)/2)
                restore(cur, pos);
        }
    }
    return res;
}                                    

template <class Record, int order>
void B_tree<Record, order>::remove_data(B_node<Record, order> *cur,int pos)
{
    for (int i = pos; i < cur->count-1; i ++ )
        cur->data[i] = cur->data[i+1];
    cur->count--;
}


template<class Record, int order>
void B_tree<Record, order>::copy_in_predecessor(B_node<Record, order> *cur,int pos)
{
    B_node<Record, order> *leaf = cur->branch[pos];
    while (leaf->branch[leaf->count] != NULL)
        leaf = leaf->branch[leaf->count];
    cur->data[pos] = leaf->data[leaf->count-1];
}

template<class Record, int order>
void B_tree<Record, order>::restore(B_node<Record, order> *cur,int pos)
{
    if (pos == cur->count)
        if (cur->branch[pos-1]->count > (order-1)/2 )
            move_right(cur, pos-1);
        else   
            combine(cur, pos);

    else if (pos == 0)
        if (cur->branch[1]->count > (order-1)/2 )
            move_left(cur, 1);
        else   
            combine(cur, 1);
    else   
        if (cur->branch[pos-1]->count > (order-1)/2 )
            move_right(cur, pos-1);
        else if (cur->branch[pos+1]->count > (order-1)/2)
            move_left(cur, pos+1);
        else   
            combine(cur, pos);
}

template<class Record, int order>
void B_tree<Record, order>::move_left(B_node<Record, order> *cur,int pos)
{
    B_node<Record, order> *left_branch = cur->branch[pos-1],
                            *right_branch = cur->branch[pos];
    left_branch->data[left_branch->count] = cur->data[pos-1];
    left_branch->branch[++left_branch->count] = right_branch->branch[0];

    cur->data[pos-1] = right_branch->data[0];

    right_branch->count--;
    for (int i = 0; i < right_branch->count; i ++ )
    {
        right_branch->data[i] = right_branch->data[i+1];
        right_branch->branch[i] = right_branch->branch[i+1];
    }
    right_branch->branch[right_branch->count] = right_branch->branch[right_branch->count+1];
}

template<class Record, int order>
void B_tree<Record, order>::move_right(B_node<Record, order> *cur,int pos)
{
    B_node<Record, order> *left_branch = cur->branch[pos],
                            *right_branch = cur->branch[pos+1];
    right_branch->branch[right_branch->count+1] = right_branch->branch[right_branch->count];
    for (int i = right_branch->count; i > 0; i -- )
    {
        right_branch->data[i] = right_branch->data[i-1];
        right_branch->branch[i] = right_branch->branch[i-1];
    }
    right_branch->count++;
    right_branch->data[0] = cur->data[pos];
    right_branch->branch[0] = left_branch->branch[left_branch->count--];
    cur->data[pos] = left_branch->data[left_branch->count];//!
}

template<class Record, int order>
void B_tree<Record, order>::combine(B_node<Record, order> *cur,int pos)
{
    int i;
    B_node<Record, order> *left_branch = cur->branch[pos-1],
                            *right_branch = cur->branch[pos];
    left_branch->data[left_branch->count] = cur->data[pos-1];
    left_branch->branch[++left_branch->count] = right_branch->branch[0];

    for (i = 0; i < right_branch->count; i ++ )
    {
        left_branch->data[left_branch->count] = right_branch->data[i];
        left_branch->branch[++left_branch->count] = right_branch->branch[i+1];
    }
    cur->count--;
    for (i = pos-1; i < cur->count; i ++ )
    {
        cur->data[i] = cur->data[i+1];
        cur->branch[i+1] = cur->branch[i+2];
    }
    delete right_branch;
}


vector<int> vv;
int main(int argc, char *argv[])
{
    /*
   search_way = atoi(argv[2] );
//    r int ORDER = atoi(argv[2]);

    double tot_time = 0;
    int cnt = 0;
    // for (int ORDER = 3; ORDER < 80; ORDER ++ )
    // {

    B_tree<int, 80> btree;
    int ins_num = atoi(argv[1]);
    int search_num = ins_num;
    int del_num = ins_num;

    auto start = std::chrono::high_resolution_clock::now();

    // for (int i = 1; i <= ins_num; i ++ ) {
    //     vv.push_back(rand() % 1000000);
    // }
    // for (int i = 1; i <= ins_num; i ++ ) btree.insert(i);
    // btree.ff_vis();
    // return 0;
    for (int i = 1; i <= search_num; i ++ )
    {
        int v = i; int ans = btree.search_tree( vv[i] );
        // assert(ans == 1);
    }

    for (int i = 1; i <= del_num; i ++ )btree.remove(vv[rand() % ins_num]);
    for (int i = 1; i <= search_num; i ++ )
    {
        int v = i; int ans = btree.search_tree( vv[rand() % ins_num] );
        assert(ans == 0);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "task took "
              << (finish - start).count() / 10000
              << " milliseconds\n";
    
    cnt++;
    tot_time += (finish - start).count() / 10000;
    // }
    // std::cout << "task avg took "
    //           << tot_time / cnt
    //           << " milliseconds\n";

*/

    B_tree <int , 5> bt;
    for (int i = 1 ; i <= atoi(argv[1]); i ++){
        bt.insert( i);
        cout <<  bt.search_tree(i);
    }
    cout << endl;

    for (int i = 1 ; i <= atoi(argv[1]); i ++){
        bt.remove( i);
        cout <<  bt.search_tree(i);
    }
    return 0;


}