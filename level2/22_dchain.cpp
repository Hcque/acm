const int N = 1e5+10;

int e[N], l[N], r[N], idx;

void init(){
    r[0] = 1,l[1] = 0;
    idx = 2;
}

// add to rioght

void add(int l, int x)
{
    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    l[r[k]] = idx;
    r[k] = idx;
}
void remove(int k){
    r[l[k]] = r[k];
    l[r[k]] = l[k];
}
int main(){

}