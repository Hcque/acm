#include <iostream>
using namespace std;
#define MAXN 15

int N;
int A[MAXN];
int count = 0;

void dfs(int nown)
{
 if (nown == N+1 ){
   count++;
   if (count <= 3){
   for (int i=1;i<=N;i++) cout << A[i] << " ";
   cout << endl;
   }
   return;
 }
 for (int i=1;i<=N;i++){
   int ok = 1;
   for (int j=1;j<nown;j++){
     if (A[j] == i || A[j]+j == nown+i || A[j]-j == i-nown ) ok = 0;
   }
   if (ok){
     A[nown] = i;
     dfs(nown+1);
   }
 }
 return;
}
int main()
{
  cin >> N;
  dfs(1);
  cout << count << endl;
  return 0;
}
