struct MergeSortTree {
    int sz , n ;
    vector<vector<int>> tree;

    MergeSortTree(int n) {
        sz = 1;
        this->n = n ; 
        while (sz < n) sz <<= 1;
        tree.resize(2 * sz);
    }

    void build(vector<vector<int>>& a, int node, int lx, int rx) {
        if (rx - lx == 1) {
            if(lx < n ) {
                tree[node] = a[lx];
                sort(all(tree[node]));
            }

            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2*node+1, lx, m);
        build(a, 2*node+2, m, rx);
        merge(all(tree[2*node+1]),all(tree[2*node+2]),back_inserter(tree[node]));
    }

    void build(vector<vector<int>>& a) {
        build(a, 0, 0, sz);
    }

    int query(int l, int r, int val, int node, int lx, int rx) {
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) {
            return lower_bound(all(tree[node]), val) - tree[node].begin();
        }
        int m = (lx + rx) / 2;
        return query(l, r, val, 2*node+1, lx, m) + query(l, r, val, 2*node+2, m, rx);
    }

    int query(int l, int r, int val) {
        return query(l, r, val, 0, 0, sz);
    }
};
