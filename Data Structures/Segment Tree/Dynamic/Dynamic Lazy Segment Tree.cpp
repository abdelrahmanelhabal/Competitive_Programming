struct Node {
  int val , lazy , is_lazy ;
  Node *left , *right;
  Node() {val = lazy = is_lazy = 0 ; left = right = nullptr;}
  Node(int x){val = x ; lazy = is_lazy = 0 ; left = right = nullptr;}
  void change(int lx , int rx , int x) {
    int len = (rx - lx) ;
    val += (x * len);
    lazy += x;
    is_lazy = 1 ;
  }
};
struct DynamicLazySegTree {
  int sz ;
  Node *root ;
  lazySegTree(int n) {
    sz = 1 ;
    while (sz < n) sz *= 2 ;
    root = new Node;
  }
  Node merge(Node *left , Node *right) {
    Node res ;
    res.val = (left ? left->val : 0) + (right ? right->val : 0) ;
    return res;
  }
  Node merge2(Node left , Node right) {
    Node res ;
    res.val = left.val + right.val ;
    return res;
  }
  void propagate(Node *node , int lx , int rx) {
    if (!node || node->is_lazy == 0 || rx - lx == 1) {return;}

    int mid = (lx + rx) / 2 ;
    if (!node->left) node->left = new Node();
    if (!node->right) node->right = new Node();

    node->left->change(lx,mid,node->lazy);
    node->right->change(mid,rx,node->lazy);
    node->is_lazy = node->lazy = 0  ;
  }
  void set(int idx , int val , Node *node , int lx , int rx) {
    if (rx - lx == 1) {
      *node = Node(val);
      return;
    }
    int mid = (lx + rx) / 2 ;
    if (idx < mid) {
      if (!node->left) node->left = new Node();
      set(idx,val,node->left,lx,mid);
    }
    else {
      if (!node->right)node->right = new Node();
      set(idx,val,node->right,mid,rx);
    }
    Node merged = merge(node->left,node->right);
    node->val = merged.val ;
  }
  void set(int idx , int val){set(idx,val,root,0,sz);}

  void update(int l , int r , int val , Node *node , int lx , int rx) {
    propagate(node,lx,rx);
    if (lx >= l && rx <= r) {
      node->change(lx,rx,val);
      return;
    }
    if (lx >= r || rx <= l)return;
    int mid = (lx + rx) / 2  ;
    if (l < mid) {
      if (!node->left) node->left = new Node();
      update(l,r,val,node->left,lx,mid);
    }
    if (r > mid) {
      if (!node->right) node->right = new Node();
      update(l,r,val,node->right,mid,rx);
    }
    Node merged = merge(node->left,node->right);
    node->val = merged.val ;
  }
  void update(int l , int r  , int val){update(l,r,val,root,0,sz);}

  Node get(int l , int r , Node *node , int lx , int rx) {
    if (!node || lx >= r || rx <= l)return Node();
    propagate(node,lx,rx);
    if (lx >=l && rx <= r) {
      return *node;
    }
    int mid = (lx + rx) / 2 ;
    Node left = get(l,r,node->left,lx,mid);
    Node right = get(l,r,node->right,mid,rx);
    return merge2(left,right);
  }
  Node get(int l , int r){return get(l,r,root,0,sz);}
};
