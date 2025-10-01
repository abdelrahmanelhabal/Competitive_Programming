template<typename T>
struct  Bit {
    vector<T>tree;
    int n ;
    void init(int n) {
        tree.assign(n+2,0);
        this->n=n;
    }
    T merge(T &a, T &b) {
        return a + b ;
    }
    void update(int x , int val) {
        for (; x<= n ; x += x & -x) {
            tree[x] = merge(tree[x],val);
        }
    }
    void update_range(int l , int r, int val) {
        if (l > r) return;
        update(l, val);
        if (r + 1 <= n) update(r + 1, -val);
    }
    T query(int x) {
        if (x <= 0){return 0;}
        T ans = 0 ;
        for (; x > 0 ; x -= x & -x) {
            ans = merge(tree[x],ans);
        }
        return ans;
    }
    T query(int l, int r) {
        return query(r) - query(l-1);
    }
    int lower_bound(T t){
        T sum = 0;
        int pos = 0;
        for(int i = n; i >= 0; i--){
            int next_pos = pos + (1 << i);
            if(next_pos <= n && sum + tree[next_pos - 1] < t){
                sum += tree[next_pos - 1];
                pos = next_pos;
            }
        }
        return pos; // zero-based index
    }
};
