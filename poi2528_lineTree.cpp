#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

class LineTree_Node{
public:
    int s, e;
    int col;
    LineTree_Node(): s(0), e(0), col(0){}
};

class solve{
public:
    solve(int n): N(n) {
        Initial();
	Input();
	CreateLineTree(1, maxP, 1);
	Solution();
    }
    ~solve(){

        cout << "des" << endl;
        for (int i=1;i<=N;i++)
            delete [] reg[i];
        // delete [] reg;
        delete [] ep;
        delete [] colored;
        delete [] LT;
    }
    void Initial();
	void Input();
	void CreateLineTree(int s, int e, int p);
	void Solution();
    void Insert(int a, int b, int p, int color);

    void dfs(int p);
protected:
    int **reg;
    int maxP;
    int N;
    LineTree_Node *LT;
    int *ep;
    int *dis;
    int cnt;
    bool *colored;

};

void solve::Initial(){
    cout << "initial" << endl;
    reg = new int*[N+1];
    for (int i=1;i<=N;i++){
        reg[i] = new int[2];
    }
    ep = new int[2*N+1];
    dis = new int[10000000+1];
    memset(dis, 0, sizeof(int)* (10000000+1));
    LT = new LineTree_Node[N+1];
    colored = new bool[N+1];
    memset(colored, false, (N+1)* sizeof(bool));
    
    cnt = 0;
}

void solve::Input(){
    cout << "input" << endl;
    int index = 0;
    for (int i=1;i<=N;i++){
        cin >> reg[i][0] >> reg[i][1];
        // cout << reg[i][0];
        if (dis[reg[i][0]] == 0){
            ep[index++] = reg[i][0];
            dis[reg[i][0]] = 1;
        }
        if (dis[reg[i][1]] == 0){
            ep[index++] = reg[i][1];
            dis[reg[i][1]] = 1;
        }
    }
    sort(ep, ep+index);
    int hash = 0;
    for (int j=0;j<index;j++){
        dis[ep[j]] = ++hash;
    }
    maxP = hash;
    // for (int i=0;i<2*N;i++) cout << ep[i] << " ";
}
void solve::CreateLineTree(int s, int e, int p)
{
    LT[p].s = s;
    LT[p].e = e;
    if (s == e) return;

    int mid = (s+e)>>1;
    CreateLineTree(s, mid, 2*p);
    CreateLineTree(mid+1, e, 2*p+1);
}

void solve::Solution(){
    for (int i=1;i<=N;i++){
        Insert(dis[reg[i][0]], dis[reg[i][1]], 1, i);
    }
    dfs(1);
    printf("%d\n", cnt);
    return;
}

void solve::dfs(int p){
    if (LT[p].col == 0) return;
    else if (LT[p].col > 0){
        if ( !colored[ LT[p].col ]){
            colored[ LT[p].col] = true;
            cnt++;
        }
        return;
    }
    else{
        //col < 0 multi colored
        dfs(2*p);
        dfs(2*p+1);
        return;    
    }
}
void solve::Insert(int a, int b, int p, int color){
    if (a > LT[p].e || b < LT[p].s) return;
    else if (a < LT[p].e || b > LT[p].s) {
        LT[p].col = LT[2*p].col = LT[2*p+1].col = color;
        return;
    }
    else{
        LT[p].col = -1; // multi colored
        int mid = (a+b) >> 1;
        Insert(a, mid, 2*p, color);
        Insert(mid+1, b, 2*p+1, color);
        return;
    }
}

int main()
{
    int num, M;
    cin >> num;
    while (num--){
	cin >> M;
        solve s(M);
    }
    return 0;
}
