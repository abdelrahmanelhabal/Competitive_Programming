struct Node {
  int val ;
  Node *left , *right;
  Node(){val = 0 ; left = right = nullptr; }
  Node(int x){val = x ; left = right = nullptr; }
  void change(int x) {
    val = x ;
  }
};
struct DynamicSegTree {
  Node *root;
  int L , R ;
  SegTree(int l , int r) {
    L = l ;
    R = r ;
    root = new Node() ;
  }
  Node merge(Node* left , Node* right) {
    Node res;
    res.val = (left ? left->val : 0)  + (right ? right->val : 0) ;
    return res;
  }
  void update(int idx , int val , Node* node , int lx , int rx) {
    if (rx - lx == 1) {
      node->change(val) ;
      return;
    }
    int mid = (lx + rx) / 2 ;
    if (idx < mid) {
      if (!node->left)node->left = new Node() ;
      update(idx,val,node->left,lx,mid);
    }
    else {
      if (!node->right)node->right = new Node() ;
      update(idx,val,node->right,mid,rx);
    }
    Node res = merge(node->left,node->right);
    node->val = res.val ;
  }
  void update(int idx , int val){update(idx,val,root,L,R);}

  Node get(int l , int r  ,Node *node ,  int lx , int rx) {
    if (!node || lx >= r || rx <= l) {
      return Node();
    }
    if (lx >= l && rx <= r) { return *node; }
    int mid = (lx + rx) / 2 ;
    Node left = get(l,r,node->left,lx,mid);
    Node right = get(l,r,node->right,mid,rx);
    return merge(&left, &right);
  }
  Node get(int l , int r) {
    return get(l,r,root,L,R);
  }
};
