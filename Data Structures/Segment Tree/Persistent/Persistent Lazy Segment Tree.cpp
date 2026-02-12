struct Node {
    long long sum, lazy;
    Node *l, *r;
    Node() : sum(0), lazy(0), l(nullptr), r(nullptr) {}
    Node(long long s, long long lz, Node* L, Node* R)
        : sum(s), lazy(lz), l(L), r(R) {}
};

struct PersistentLazySegTree {
    int n;
    PersistentLazySegTree(int _n) { n = _n; }

    Node* build(int lx, int rx, vector<int>& a) {
        if (rx - lx == 1) return new Node(a[lx], 0, nullptr, nullptr);
        int mid = (lx + rx) >> 1;
        Node* L = build(lx, mid, a);
        Node* R = build(mid, rx, a);
        return new Node(L->sum + R->sum, 0, L, R);
    }

    Node* clone(Node* node) {
        if (!node) return new Node();
        return new Node(node->sum, node->lazy, node->l, node->r);
    }

    void push(Node* node, int lx, int rx) {
        if (!node || node->lazy == 0 || rx - lx == 1) return;

        int mid = (lx + rx) >> 1;
        long long x = node->lazy;

        node->l = clone(node->l);
        node->r = clone(node->r);

        node->l->sum += x * (mid - lx);
        node->l->lazy += x;

        node->r->sum += x * (rx - mid);
        node->r->lazy += x;

        node->lazy = 0;
    }

    Node* update(Node* node, int lx, int rx, int l, int r, long long val) {
        node = clone(node);
        if (lx >= r || rx <= l) return node;

        if (lx >= l && rx <= r) {
            node->sum += val * (rx - lx);
            node->lazy += val;
            return node;
        }

        push(node, lx, rx);
        int mid = (lx + rx) >> 1;

        node->l = update(node->l, lx, mid, l, r, val);
        node->r = update(node->r, mid, rx, l, r, val);
        node->sum = node->l->sum + node->r->sum;
        return node;
    }

    long long querysum(Node* node, int lx, int rx, int l, int r) {
        if (!node || lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) return node->sum;

        push(node, lx, rx);
        int mid = (lx + rx) >> 1;
        return querysum(node->l, lx, mid, l, r)
             + querysum(node->r, mid, rx, l, r);
    }
};
