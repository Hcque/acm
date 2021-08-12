#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 11
int N,K;
int count;

bool chess[MAXN][MAXN];
int col_occupied[MAXN];

void dfs(int line, int k)
{
    // cout << line << endl;

    if ( k == K) {
        // cout << line << endl;
        count++;
        return;
    }

    for (int a = line;a<=N;a++){

    for (int i=1;i<=N;i++){
        if (chess[a][i] && col_occupied[i] == 0){
            col_occupied[i] = 1;
            dfs(a+1, k+1);
            col_occupied[i] = 0;
        }
    }
    }

}


int main()
{
   while (1){
   
       cin >> N >> K;
       char ch;
    //    cout << N << K <<endl;
       if (N==-1 && K==-1) break;

	memset(chess, false, sizeof(chess));
	memset(col_occupied, 0, sizeof(col_occupied));
    count = 0;

       for (int i=1;i<=N;i++){
           for (int j=1;j<=N;j++){
               cin >> ch;
	       switch (ch){
	 	   case '#': chess[i][j] = true; break;

	       }
 	       
	   }
       }
       dfs(1,0);
    //    for (int i=1;i<=N;i++){
    //        for (int j=1;j<=N;j++){
 	//       cout << chess[i][j]<< " "; 
	//    }
	//    cout << endl;
    //    }
    cout << count << endl;
   }
}
