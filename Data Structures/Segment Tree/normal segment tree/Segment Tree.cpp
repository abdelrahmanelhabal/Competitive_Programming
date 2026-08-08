struct Node {
    int val   ;
    Node(){ val = 0 ;   }
    Node(int x) { val = x ; }
    void change(int x) { val =x ;  }
};
struct segment_tree {
    int tree_size;
    vector<Node>segData;
    segment_tree(int n) {
        tree_size = 1;
        while (tree_size < n)tree_size*=2;
        segData.assign(2*tree_size, Node());
    }
    Node merge(Node &left ,Node &right) {
        Node res;
        res.val = left.val + right.val  ;
        return res;
    }
    void init(vector<int> &a , int node , int lx , int rx) {
        if (rx- lx == 1) {
            if (lx < (int)a.size())
                segData[node] = Node(a[lx]);
            return;
        }
        int mid = (lx + rx)/2;
        init(a,2*node+1,lx,mid);
        init(a,2*node+2,mid,rx);
        segData[node] = merge(segData[2*node+1],segData[2*node+2]);
    }
    void init(vector<int>&a) {
        init(a,0,0,tree_size);
    }
    Node get(int l, int r , int node , int lx , int rx) {
        if (lx >=l && rx <= r) return segData[node];
        if (rx <= l || lx >=r) return Node();
        int mid = (lx + rx)/2;
        Node left = get(l,r,2*node+1,lx,mid);
        Node right =  get(l,r,2*node+2,mid,rx);
       return  merge(left,right);
    }
    int get(int l, int r) {
        return get(l,r,0,0,tree_size).val;
    }
    void update(int idx, int val,int node , int lx , int rx) {
        if (rx - lx == 1) {
            segData[node].change(val);
            return;
        }
        int mid = (lx + rx)/2;
        if (idx < mid) {
        update(idx,val,2*node+1,lx,mid);
        }
        else {
        update(idx,val,2*node+2,mid,rx);
        }
        segData[node] = merge(segData[2*node+1],segData[2*node+2]);
    }
    void update(int idx, int val) {
        update(idx,val,0,0,tree_size);
    }
};
