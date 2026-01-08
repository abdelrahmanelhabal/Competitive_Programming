int const N = 1e9+8;
struct Node {
  int val ;
  Node *left , *right ;
  Node(){val = 0 , left = right = nullptr;}
  Node(int x) { val = x ; left = right = nullptr;}
  Node(Node*l , Node *r) {
    val = 0 ;
    left = l , right = r ;
    if (l) val += l->val ;
    if (r) val += r->val ;
  }
};
int getVal(Node*node){return node ? node->val : 0;}
Node*getL(Node*node){return node ? node->left : nullptr;}
Node*getR(Node*node){return node ? node->right : nullptr;}

Node*update(int idx , int val , Node*node , int lx = 0  , int rx = N) {
  if (!node) node = new Node();
  if (rx - lx == 1) return new Node(val + getVal(node));

  int mid = (lx + rx) / 2 ;
  if (idx < mid) {
    Node *left = update(idx,val,getL(node),lx,mid);
    return new Node(left,getR(node));
  }
  else {
    Node *right = update(idx,val,getR(node),mid ,rx);
    return new Node(getL(node),right);
  }
}
int get(int l , int r , Node*node , int lx = 0, int rx = N ) {
  if (!node || lx >= r || rx <= l) return 0;
  if (lx >= l && rx <= r) return getVal(node);

  int mid = (lx + rx) / 2 ;
  int left = get(l,r,getL(node),lx,mid);
  int right = get(l,r,getR(node),mid,rx);
  return left + right;
}
