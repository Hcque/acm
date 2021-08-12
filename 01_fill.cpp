#include <iostream>
using namespace std;
int a[32][32],b[32][32];
int dx[5]={0,-1,1,0,0};
int dy[5]={0,0,0,-1,1};//向
int n,i,j;
void dfs(int p,int q){
    int i;
    if (p<0||p>n+1||q<0||q>n+1||a[p][q]!=0) return;//如果搜s回
    a[p][q]=1;//染色
    for (i=1;i<=4;i++) dfs(p+dx[i],q+dy[i]);//向四个方向搜索
}
int main(){
    cin>>n;
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++){
            cin>>b[i][j];//其实不啦
            if (b[i][j]==0) a[i][j]=0;
            else a[i][j]=2;
        }
    dfs(0,0);//搜索 从0，0开始搜
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++)
        if (a[i][j]==0) cout<<2<<' ';
        else cout<<b[i][j]<<' ';//因
        cout<<'\n';//换行
    }
}
