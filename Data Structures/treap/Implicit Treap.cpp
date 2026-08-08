mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct Treap {

    struct Node {
        int val;               
        long long sum;         
        int sz;                 
        uint32_t prior;         
        Node *l, *r;

        Node(int v) {
            val = v;
            sum = v;
            sz = 1;
            prior = rng();
            l = r = nullptr;
        }
    };

    using node = Node*;

    node root = nullptr;

    
    int sz(node t) {
        return t ? t->sz : 0;
    }

    long long get_sum(node t) {
        return t ? t->sum : 0;
    }


    void update(node t) {
        if (!t) return;
        t->sz = 1 + sz(t->l) + sz(t->r);
        t->sum = sum(t->l) + t->val + sum(t->r);
    }


    void split(node t, node &l, node &r, int k) {
        if (!t) {
            l = r = nullptr;
            return;
        }

        if (sz(t->l) >= k) {
            split(t->l , l , t->l , k);
            r = t;
        }
        else {
            split(t->r , t->r , r , k - sz(t->l) - 1);
            l = t;
        }
        update(t);
    }

    void merge(node &t, node l, node r) {
        if (!l || !r)
            t = (l ? l : r);
        else if (l->prior > r->prior) {
            merge(l->r, l->r, r);
            t = l;
        }
        else {
            merge(r->l, l, r->l);
            t = r;
        }
        update(t);
    }

    void insert(int idx, int val) {
        node a, b;
        split(root, a, b, idx);
        node cur = new Node(val);
        merge(a, a, cur);
        merge(root, a, b);
    }

    void erase(int idx) {
        node a, b, c;
        split(root, a, b, idx);
        split(b, b, c, 1);
        delete b;
        merge(root, a, c);
    }

    int kth(node t, int k) {
        if (!t) return -1;
        if (k < sz(t->l))
            return kth(t->l, k);
        if (k == sz(t->l))
            return t->val;
        return kth(t->r, k - sz(t->l) - 1);
    }

    int kth(int k) {
        return kth(root, k);
    }


    void reverse(int l, int r) {
        node a, b, c;
        split(root, a, b, l);
        split(b, b, c, r - l + 1);
        if (b)
            b->rev ^= 1;
        merge(b, b, c);
        merge(root, a, b);
    }

    void setValue(node t, int idx, int val) {
        if (!t) return;
        push(t);
        if (idx < sz(t->l))
            setValue(t->l, idx, val);
        else if (idx == sz(t->l))
            t->val = val;
        else
            setValue(t->r,idx - sz(t->l) - 1,val);
        update(t);
    }

    void setValue(int idx, int val) {
        setValue(root, idx, val);
    }
    void shiftLeft(int l, int r, int k) {
        int len = r - l + 1;
        if (len <= 1) return;
        k %= len;
        if (k == 0) return;
        node a, b, c, d;
        split(root, a, b, l);
        split(b, b, d, len);
        node x, y;
        split(b, x, y, k);
        merge(b, y, x);
        merge(b, b, d);
        merge(root, a, b);
    }

    void shiftRight(int l, int r, int k) {
        int len = r - l + 1;
        if (len <= 1) return;
        k %= len;
        if (k == 0) return;
        node a, b, c, d;
        split(root, a, b, l);
        split(b, b, d, len);
        node x, y;
        split(b, x, y, len - k);
        merge(b, y, x);
        merge(b, b, d);
        merge(root, a, b);
    }

    int getValue(node t, int idx) {
        while (t) {
            if (idx < sz(t->l))
                t = t->l;
            else if (idx == sz(t->l))
                return t->val;
            else {
                idx -= sz(t->l) + 1;
                t = t->r;
            }
        }
        return -1;
    }

    int getValue(int idx) {
        return getValue(root, idx);
    }


    long long query(int l, int r) {
        node a, b, c;
        split(root, a, b, l);
        split(b, b, c, r - l + 1);
        long long ans = sum(b);
        merge(b, b, c);
        merge(root, a, b);
        return ans;
    }


    void build(const vector<int> &v) {
        root = nullptr;
        for (int i = 0; i < (int)v.size(); i++)
            insert(i, v[i]);
    }


    int size() {
        return sz(root);
    }


    void inorder(node t) {
        if (!t) return;
        inorder(t->l);
        cout << t->val << ' ';
        inorder(t->r);
    }

    void print() {
        inorder(root);
        cout << endl;
    }

    void clear(node t) {
        if (!t) return;
        clear(t->l);
        clear(t->r);
        delete t;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }
};
