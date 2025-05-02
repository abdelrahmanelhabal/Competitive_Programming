struct Node {
    int sum ;
    Node() { sum = 0 ; }

    Node(int val ){ sum = val; }

    void change(int val) { sum+=val; }
};

struct segTree {
    int treeSize ;
    vector<Node>segData;
    segTree(int n ) {
        treeSize = 1;
        while (treeSize < n) treeSize*=2 ;
        segData.assign(2*treeSize, Node());
    }

    Node merge(Node &l, Node& r) {
        Node ans = Node();
        ans.sum = l.sum + r.sum;

        return ans;
    }

    void init(vector<int>&a,int node , int lx , int rx) {
        if (rx-lx==1) {
            if (lx  < a.size()) {
                segData[node] = Node(a[lx]);
            }
            return;
        }
        int mid = (lx+rx)/2;
        init(a, 2*node+1 , lx , mid);
        init(a, 2*node+2 , mid , rx);
        segData[node] = merge(segData[2*node+2],segData[2*node+1]);

    }
    void init(vector<int>&a) {
        init(a,0,0,treeSize);
    }

    void set(int idx , int val , int node , int l , int r ) { // 0-indexed  r not included

        if (r-l == 1) {
            segData[node].change(val);
            return;
        }

        int mid = (l+r)/2;

        if (idx  < mid) {
            set(idx,val, 2*node+1 , l , mid);
        }
        else {
            set(idx,val, 2*node+2 , mid , r);
        }
        segData[node] = merge(segData[2*node+2],segData[2*node+1]);
    }

    void set(int idx , int val) { set(idx,val,0,0,treeSize); }

    Node get(int l , int r , int node , int lx , int rx ) { // 0-indexed  r not included
        int mid = (l+r)/2;
        if (lx>= l && r <= rx) { return segData[node]; }
        if (lx >= r || rx <= l){ Node();}

        Node lf = get(l,r,2*node+1,lx,mid);
        Node ri = get(l,r,2*node+2,mid,rx);

        return merge(lf,ri);
    }

    int get(int l , int r) { return get(l,r,0,0,treeSize).sum; }
 
};
