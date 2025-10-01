#define int long long
const int N = 1e9 + 9;
map<int,int> tree;
struct Bit {
    void update(int x, int val) {
        for(++x; x < N; x += (x & -x))  tree[x-1] += val;
    }
    int query(int x){
        int res = 0;
        for(++x;x > 0; x -= (x & -x)) res += tree[x-1];
        return res;
    }
    int query(int l , int r){ return query(r) - query(l - 1); }
};
