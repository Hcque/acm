#include <iostream>

using namespace std;

void perm(int n, int* A, int nown)
{
        
    if (nown == n+1){
	for (int i=1;i<=n;i++)
 	    cout << A[i] << " ";
	cout << endl;
	return;
    }
    else {
    	for (int i=1;i<=n;i++){
	    int ok = 1;
	    for (int j=1;j<nown;j++)
	        if (A[j] == i) ok = 0;
	    if (ok){
	        A[nown] = i;
		perm(n, A, nown+1);
	    }

	}
   }

    return;

}

int main()
{
    int N;
    cin >> N;

    int A[100];
    perm(N, A, 1);
}
