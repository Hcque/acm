#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1e5+10;
int a[maxn], N;

template <typename Type>
void insertion_sort(){
    int pos, first_unsorted;
    Type cur;
    for (first_unsorted=1;first_unsorted < N; first_unsorted++){
        if (a[first_unsorted] < a[first_unsorted-1]){
            pos = first_unsorted;
            cur = a[first_unsorted];
            do{
                a[pos] = a[pos-1];
                pos--;
            } while (pos>0 && a[pos-1]>cur);
            a[pos] = cur;
        }
    }
}

void sort_interval(int start, int inc){
    int pos, first_unsorted;
    int cur;
    for (first_unsorted=start;first_unsorted < N; first_unsorted+=inc){
        if (a[first_unsorted] < a[first_unsorted-inc]){
            pos = first_unsorted;
            cur = a[first_unsorted];
            do{
                a[pos] = a[pos-inc];
                pos-=inc;
            } while (pos-inc>=start && a[pos-inc]>cur);
            a[pos] = cur;
        }
    }
}

void shell_sort(){
    int inc = N, start;
    do{
        inc = inc/3+1;
        for (start=0;start<N;start+inc){
            sort_interval(start, inc);
        }
    } while (inc >= 1);

}

int main(){
     cin >> N;
     for (int i=0;i<N;i++){
         cin >> a[i];
     }

    //  sort(a,a+N);
    // insertion_sort<int>();
    shell_sort();
     for (int i=0;i<N-1;i++) cout << a[i] << " ";
     cout << a[N-1];

}
