// https://www.youtube.com/watch?v=2FShdqn-Oz8&ab_channel=Errichto2
// https://cses.fi/problemset/task/1646
#include <iostream>
#include <vector>
using namespace std;

int N,q;
vector<long long> tree;
long long f(int node, int n_left, int n_right, int q_low, int q_high, int v){
    if (q_low <= n_left && n_right <= q_high){
        if (v == -1){
             tree[node] = v;
        }
        return tree[node];
    }
    if (n_right < q_low || q_high < n_left) 
        return 0;
    int last_in_left = n_left + (n_right - n_left)/2;
    long long sum_ = f(2*node, n_left, last_in_left, q_low, q_high, v)
          + f(2*node+1, last_in_left+1, n_right, q_low, q_high, v);
    tree[node] = tree[2*node] + tree[2*node+1];    
    return sum_;
}
/*
void change(int node, int n_left, int n_right, int q_low, int q_high, int v){
    if (q_low <= n_left && n_right <= q_high){
        tree[node] = v;
        return;
    }
    if (n_right < q_low || q_high < n_left) 
        return;
    int last_in_left = n_left + (n_right - n_left)/2;
    change(2*node, n_left, last_in_left, q_low, q_high, v);
    change(2*node+1, last_in_left+1, n_right, q_low, q_high, v);
    tree[node] = tree[2*node] + tree[2*node+1];
}
*/

// https://cses.fi/problemset/task/1648

void update(int i, int v){
    tree[N+i] = v;
    for (int j = (N+i)/2; j>=1; j/=2){
        tree[j] = tree[2*j] + tree[2*j+1];
    }
}

int main()
{
    cin >> N >> q;
    vector<int> a(N);
    for (int i=0;i<N;i++){
        cin >> a[i];
    }
    int k = 0;
    while (N > (1<<k)) k++;
    for (int i=N;i<(1<<k);i++){
        N++;
        a.push_back(0);
    }

    tree.resize(2*N);
    // build the tree
    for (int i=0;i<N;i++){
        tree[i+N] = a[i];
    }
    for (int i= N-1;i>=1;i--){
        tree[i] = tree[2*i] + tree[2*i+1];
    }

    int low, high;
    int index, v;
    int type;
    for (int i=0;i<q;i++){
        cin >> type;
        if (type == 1){
            cin >> index >> v;
            index--;
            // update(index, v);

            change(1, 0, N-1, index, index, v);
        }
        else{
            cin >> low >> high;
            low--;
            high--;
            cout << f(1, 0, N-1, low, high) << endl;
        }
    }
}
