// all elem sorting

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5+10;

int a[N];
int n, m;



// void insertionSort()
// {
//     int i,j;
//     for (i = 2;i <= n; i ++ )
//     {
//         if (a[i] < a[i-1]){
//             a[0] = a[i];
//             for (j=i-1; a[j] > a[0]; j -- )
//             {
//                 a[j+1] = a[j];
//             }
//             a[j+1] = a[0];
//         }
//     }
    
// }


// void insertionSort()
// {
//     int i,j;
//     for (i = 2;i <= n; i ++ )
//     {
//         if (a[i] < a[i-1]){
//             a[0] = a[i];
            
//             int l = 0, r = i-1;
//             while (l<r)
//             {
//                 int mid = l+r+1>>1;
//                 if (a[mid] <= a[0]) l = mid;
//                 else r = mid-1;
//             }
//             // cout << a[l];
//             for (int k=i-1;k>=l+1;k--) a[k+1] = a[k];
//             a[l+1] = a[0];
//         }
//     }
    
// }

// void bubbleSort()
// {
//     for (int i = 1; i <= n-1; i ++ ){
//         int flag = 0;
//         for (int j = 1; j <= n-i; j ++ )
//         {
//             if (a[j] > a[j+1]) 
//             {
//                 swap(a[j],a[j+1]);
//                 flag = 1;
//             }
//         }
//         if (!flag) return;
        
//     }
// }

void quickSort(int l,int r)
{
    if (l>=r) return;
    
    int pivot = a[r];
    // int i = l-1, j = r +1;
    // while (i < j)
    // {
    //     do (i++); while(a[i]<pivot);
    //     do (j--); while(a[j]>pivot);
    //     if (i < j)
    //     {
    //         swap(a[i],a[j]);
    //     }
    // }
    
    int i = l-1;
    for (int k = l;k<r; k++)
    {
        if (a[k] < pivot) {
            i++;
            swap(a[i],a[k]);
        }
    }
    swap(a[i+1],a[r]);
    
    int mid = i+1;
    
    quickSort(l,mid-1);
    quickSort(mid+1,r);

}


void selectionSort()
{
    
    for (int i=n;i>1;i--)
    {
        int max_ = 1;
        for (int j = 2;j<=i;j++) if (a[j] > a[max_]) max_ = j;
        swap(a[max_], a[i]);
    }
}


int main()
{
    cin >> n>>m;
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    // insertionSort();
    // quickSort(1,n);
    selectionSort();
    
    
    for (int i = 1; i <= m; i ++ ) cout << a[i] << " ";


}
