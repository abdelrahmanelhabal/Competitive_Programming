struct Node {
  int sum , lazy , is_lazy ;
  Node(){sum = lazy = is_lazy = 0 ;}
  Node(int x){sum = x ; lazy = is_lazy = 0 ;}
  void change(int lx , int rx , int x ) {
    int len = (rx - lx);
    sum += (x * len);
    lazy += x ;
    is_lazy = 1 ;
  }
};
struct lazySegTree {
  int sz ;
  vector<Node>segData;
  lazySegTree(int n) {
    sz = 1 ;
    while (sz < n) sz *= 2 ;
    segData.assign(2*sz,Node());
  }
  Node merge(Node left , Node right) {
    Node res ;
    res.sum = left.sum + right.sum ;
    return res;
  }
  void propagate(int node , int lx , int rx) {
    if (segData[node].is_lazy == 0 || rx - lx == 1)return;
    int mid = (lx + rx) / 2 ;
    int x = segData[node].lazy ;
    segData[2*node+1].change(lx,mid,x);
    segData[2*node+2].change(mid,rx,x);
    segData[node].is_lazy =segData[node].lazy = 0 ;
  }
  void set(int idx , int val , int node , int lx , int rx) {
    if (rx - lx == 1) {
      segData[node] = Node(val);
      return;
    }
    int mid = (lx + rx) / 2 ;
    if (idx < mid) {
      set(idx,val,2*node+1,lx,mid);
    }
    else {
      set(idx,val,2*node+2,mid,rx);
    }
    segData[node] = merge(segData[2*node+1],segData[2*node+2]);
  }
  void set(int idx , int val){set(idx,val,0,0,sz);}

  void update(int l , int r , int x , int node , int lx , int rx) {
    propagate(node,lx,rx);
    if (lx >= l && rx  <= r) {
      segData[node].change(lx,rx,x);
      return;
    }
    if (lx >= r || rx <= l) return;
    int mid = (lx + rx) / 2 ;
    update(l,r,x,2*node+1,lx,mid);
    update(l,r,x,2*node+2,mid,rx);
    segData[node] = merge(segData[2*node+1],segData[2*node+2]);
  }
  void update(int l , int r , int x){update(l,r,x,0,0,sz);}

  Node get(int l , int r , int node , int lx , int rx) {
    propagate(node,lx,rx);
    if (lx >= l && rx <= r) {
      return segData[node];
    }
    if (lx >= r || rx <=l) {
      return Node();
    }
    int mid = (lx + rx) / 2 ;
    Node left = get(l,r,2*node+1,lx,mid);
    Node right = get(l,r,2*node+2,mid,rx);
    return merge(left,right);
  }
  Node get(int l , int r){return get(l,r,0,0,sz);}
};
