mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct Treap {

    struct Node {
        int key;        
        int prior;      
        int sz;         
        int val ; 
        Node *l, *r;

        Node(int v) {
            key = v;
            prior = rng();
            sz = 1;
            val = v ; 
            l = r = nullptr;
        }
    };

    Node* root = nullptr;

    int sz(Node* t) {
        return t ? t->sz : 0;
    }

    int get_val(Node *t){
        return t ? t->val : 0 ; 
    }

    void update(Node* t) {
        if (!t) return;
        t->sz = 1 + sz(t->l) + sz(t->r);
        t->val = get_val(t->l) + t->key +  get_val(t->r);
    }

     void split(Node* t, int key, Node*& l, Node*& r) {
        if (!t) {
            l = r = nullptr;
            return;
        }

        if (t->key <= key) {
            split(t->r, key, t->r, r);
            l = t;
        } else {
            split(t->l, key, l, t->l);
            r = t;
        }
        update(t);
    }

    Node* merge(Node* l, Node* r) {
        if (!l) return r;
        if (!r) return l;

        if (l->prior > r->prior) {
            l->r = merge(l->r, r);
            update(l);
            return l;
        } else {
            r->l = merge(l, r->l);
            update(r);
            return r;
        }
    }

    void insert(int x) {
        Node *a, *b;
        split(root, x, a, b);
        root = merge(merge(a, new Node(x)), b);
    }

    void erase(Node*& t, int x) {
        if (!t) return;
        if (t->key == x) {
            Node* cur = t;
            t = merge(t->l, t->r);
            delete cur;
        } else if (x < t->key) {
            erase(t->l, x);
        } else {
            erase(t->r, x);
        }
        update(t);
    }

    void erase(int x) {
        erase(root, x);
    }

    bool find(Node* t, int x) {
        if (!t) return false;
        if (t->key == x)
            return true;
        if (x < t->key)
            return find(t->l, x);
        return find(t->r, x);
    }

    bool find(int x) {
        return find(root, x);
    }

    int kth(Node* t, int k) {
        if (!t) return -1;
        if (sz(t->l) + 1 == k)
            return t->key;
        if (k <= sz(t->l))
            return kth(t->l, k);
        return kth(t->r, k - sz(t->l) - 1);
    }

    int kth(int k) {
        return kth(root, k);
    }

    int less(Node* t, int x) {
        if (!t) return 0;
        if (t->key >= x)
            return less(t->l, x);
        return sz(t->l) + 1 + less(t->r, x);
    }

    int less(int x) {
        return less(root, x);
    }

    int lessEqual(int x) {
        return less(x + 1);
    }

    int greater(int x) {
        return sz(root) - lessEqual(x);
    }

    int greaterEqual(int x) {
        return sz(root) - less(x);
    }

    int rank(int x) {
        return less(x) + 1;
    }

    int predecessor(int x) {
        Node* cur = root;
        int ans = INT_MIN;
        while (cur) {
            if (cur->key < x) {
                ans = cur->key;
                cur = cur->r;
            } else {
                cur = cur->l;
            }
        }
        return ans;
    }

    int successor(int x) {
        Node* cur = root;
        int ans = INT_MAX;
        while (cur) {
            if (cur->key > x) {
                ans = cur->key;
                cur = cur->l;
            } else {
                cur = cur->r;
            }
        }
        return ans;
    }

    int query(int L, int R) {
        Node *t1, *t2, *t3;
        split(root, R, t1, t3);
        split(t1, L - 1, t1, t2);
        int ans = 0 ;
        if (t2) {
            ans = t2->val ; 
        }
        root = merge(merge(t1, t2), t3);
        return ans;
    }

    void build(const vector<int>& a) {
        root = nullptr;
        for (int x : a)
            insert(x);
    }

    int size() {
        return sz(root);
    }
};
