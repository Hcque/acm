#include <iostream>
#include <cstring>
#include <string>
#include <set>
using namespace std;

const int MAXN =92;
set<string> m;

void strCvt(char* s1, char* s2, int len){
    s2[len] = '\0';
    int ps = 0;
    for (int i=len-1;i>=0;i--){
        s2[i] = s1[ps++];
    }
    return;
}

void strCut(char* s, char* s1, char* s2, int k, int len){
    int p = 0;
    for (int i=k;i<len;i++){
        s2[p++] = s[i];
    }
    s2[p++] = '\0';
    s1[k] = '\0';
    for (int i=0;i<k;i++){
        s1[i] = s[i];
    }
}

void strCat(char* s1, char *s2, char* str){
    strcpy(str, s1);
    strcpy(str + strlen(s1), s2);
}

void doit(char *st){
    // cout << st ;
    m.insert(string(st));
    // cout << " " << m.size() << endl;

}

int main()
{
    int N;
    cin >> N;
    char tmp[MAXN];
    while (N--){
        m.clear();
        cin >> tmp;
        int tmp_size = strlen(tmp);
        if (tmp_size == 1) {
            cout<< 1 << endl; 
            continue;
        }

        // cout << strlen(tmp) << endl;
        char A[MAXN], B[MAXN];
        char iA[MAXN], iB[MAXN];
        char str[MAXN];

        for (int i=1;i<=tmp_size-1;i++){
            // cout << tmp_size << endl;
            strCut(tmp, A, B, i, tmp_size);
            strCvt(A, iA, i);
            strCvt(B, iB, tmp_size-i);
            doit(tmp);

            strCat(B, A, str);
            doit(str);
            strCat(A, iB, str);
            doit(str);
            strCat(iB, A, str);
            doit(str);
            strCat(iA, B, str);
            doit(str);
            strCat(B, iA, str);
            doit(str);
            strCat(iA, iB, str);
            doit(str);
            strCat(iB, iA, str);
            doit(str);
        }
        cout << m.size() << endl;

    }
    return 0;
}
