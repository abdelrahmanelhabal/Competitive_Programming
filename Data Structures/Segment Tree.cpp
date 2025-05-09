const int INF = 1e18;

struct Node {
    int val ;
    Node() { val = INF ;}
    Node(int val) { this->val = val ;}
    void change(int x) { val = x ; }
};

struct segTree {
    int tree_size;
    vector<Node> segData;

    segTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size *= 2;
        segData.resize(2 * tree_size, Node());
    }

    Node merge(Node &left, Node &right) {
        Node ans;
        ans.val = min(left.val , right.val);
        return ans;
    }

    void init(vector<int> &a, int node, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size()) {
                segData[node] = Node(a[lx]);
            }
            return;
        }
        int mid = (lx + rx) / 2;
        init(a, 2 * node + 1, lx, mid);
        init(a, 2 * node + 2, mid, rx);
        segData[node] = merge(segData[2 * node + 1], segData[2 * node + 2]);
    }

    void init(vector<int> a) {
        init(a, 0, 0, tree_size);
    }

    void set(int idx, int val, int node, int lx, int rx) {
        if (rx - lx == 1) {
            segData[node].change(val);
            return;
        }
        int mid = (lx + rx) / 2;
        if (idx < mid) set(idx, val, 2 * node + 1, lx, mid);
        else set(idx, val, 2 * node + 2, mid, rx);
        segData[node] = merge(segData[2 * node + 1], segData[2 * node + 2]);
    }

    void set(int idx, int val) {
        set(idx, val, 0, 0, tree_size);
    }

    Node get(int l, int r, int node, int lx, int rx) {
        if (lx >= r || rx <= l) return Node();
        if (lx >= l && rx <= r) return segData[node];
        int mid = (lx + rx) / 2;
        Node left = get(l, r, 2 * node + 1, lx, mid);
        Node right = get(l, r, 2 * node + 2, mid, rx);
        return merge(left, right);
    }

    Node get(int l, int r) {
        return get(l, r, 0, 0, tree_size);
    }
};