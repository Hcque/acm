#include <iostream>
#include <cstring>
using namespace std;

const int MAXN =80;
const int mod = 99992;

int count = 0;

typedef struct HASH{
    char s[MAXN];
    struct HASH* next;
    HASH(){ next = 0; }     
} Hashtable;

Hashtable* hh[mod];

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


void hash_(char *s){
    // cout << s << endl;
    int key = 0;
    char *ps = s;
    for (int i=1;*ps;i++){
        key += *(ps++) * i;
    }
    // cout << key << endl;
    key %= mod;
    if (!hh[key]){
        Hashtable* pn = new Hashtable;
        strcpy(pn->s, s);
        hh[key] = pn;
        count++;
    }
    else {
        Hashtable* pn = hh[key];
        // cout << pn->s << endl;
        if ( ! strcmp(pn->s, s) ) return;
        while (pn->next){
            if (  ! strcmp(pn->next->s, s) ) return;
            pn = pn->next;
        }

        Hashtable* tmp = new Hashtable;
        strcpy(tmp->s, s);
        count++;
        pn->next = tmp;
    }
}

void strCat(char* s1, char *s2, char* str){
    strcpy(str, s1);
    strcpy(str + strlen(s1), s2);
}

int main()
{
    int N;
    cin >> N;
    char tmp[MAXN];
    while (N--){
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
        count = 0;
        memset(hh, 0, sizeof(hh));

        for (int i=1;i<=tmp_size-1;i++){
            // cout << tmp_size << endl;
            strCut(tmp, A, B, i, tmp_size);
            strCvt(A, iA, i);
            strCvt(B, iB, tmp_size-i);
            hash_(tmp);

            strCat(B, A, str);
            hash_(str);
            strCat(A, iB, str);
            hash_(str);
            strCat(iB, A, str);
            hash_(str);
            strCat(iA, B, str);
            hash_(str);
            strCat(B, iA, str);
            hash_(str);
            strCat(iA, iB, str);
            hash_(str);
            strCat(iB, iA, str);
            hash_(str);

        }
        cout << count << endl;

    }
    return 0;
}
