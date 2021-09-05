
int n, m;
const int maxn = 1e6+10;
int a[maxn];
struct Node{
    int l,r, val;
} hjt[maxn*40]; 
int cnt, root[maxn];


int main(){
    scanf("%d%d", &n,&m);
    for (int i=0;i<n;i++) scanf("%d", a+i);

    while (m--){
        int op, x, y, z;
        scanf("%d", &op);
        switch (op){
            case 1:
                cin >> x >> y;
                modify();
                break;
            case 


        }
    }
    
}