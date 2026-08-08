struct Node {
    int val ;
    Node() { val = 0;}
    Node(int x ) {val = x;}
};

struct SegTree_2D {
    vector<vector<Node>> segData;
    int n = 0, m = 0;

    SegTree_2D(int n, int m) {
        this->n = n;
        this->m = m;
        int r = 1, c = 1;
        while (r < n) r *= 2;
        while (c < m) c *= 2;
        segData = vector<vector<Node>>(2 * r, vector<Node>(2 * c));
    }

    Node merge(Node left , Node right) {
        Node res ;
        res.val = left.val + right.val ;
        return res;
    }
    void buildY(int vx, int lx, vector<vector<int>> &a, int rx, int vy, int ly, int ry) {
        if (ly == ry) {
            if (lx == rx) {
                segData[vx][vy] = Node(a[lx][ly]);
            } else {
                segData[vx][vy] = merge(segData[vx * 2][vy] , segData[vx * 2 + 1][vy]);
            }
        } else {
            int mid = (ly + ry) / 2;
            buildY(vx, lx, a, rx, vy * 2, ly, mid);
            buildY(vx, lx, a, rx, vy * 2 + 1, mid + 1, ry);
            segData[vx][vy] = merge(segData[vx][vy * 2] , segData[vx][vy * 2 + 1]);
        }
    }

    void buildX(vector<vector<int>> &a, int vx, int lx, int rx) {
        if (lx != rx) {
            int mid = (lx + rx) / 2;
            buildX(a, vx * 2, lx, mid);
            buildX(a, vx * 2 + 1, mid + 1, rx);
        }
        buildY(vx, lx, a, rx, 1, 0, m - 1);
    }

    Node getY(int vx, int vy, int tly, int try_, int ly, int ry) {
        if (ly > ry) return Node();
        if (ly == tly && try_ == ry) return Node(segData[vx][vy]);
        int mid = (tly + try_) / 2;
        Node left = getY(vx, vy * 2, tly, mid, ly, min(ry, mid)) ;
        Node right = getY(vx, vy * 2 + 1, mid + 1, try_, max(ly, mid + 1), ry);
        return merge(left,right);
    }

    Node getX(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
        if (lx > rx)
            return Node();
        if (lx == tlx && trx == rx)
            return getY(vx, 1, 0, m - 1, ly, ry);
        int mid = (tlx + trx) / 2;
        Node left = getX(vx * 2, tlx, mid, lx, min(rx, mid), ly, ry) ;
        Node right = getX(vx * 2 + 1, mid + 1, trx, max(lx, mid + 1), rx, ly, ry);
        return merge(left,right);
    }

    void updateY(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int nval) {
        if (ly == ry) {
            if (lx == rx)
                segData[vx][vy] = nval;
            else
                segData[vx][vy] = merge(segData[vx * 2][vy] , segData[vx * 2 + 1][vy]);
        } else {
            int mid = (ly + ry) / 2;
            if (y <= mid)
                updateY(vx, lx, rx, vy * 2, ly, mid, x, y, nval);
            else
                updateY(vx, lx, rx, vy * 2 + 1, mid + 1, ry, x, y, nval);
            segData[vx][vy] = merge(segData[vx][vy * 2] , segData[vx][vy * 2 + 1]);
        }
    }

    void updateX(int vx, int lx, int rx, int x, int y, int nval) {
        if (lx != rx) {
            int mid = (lx + rx) / 2;
            if (x <= mid)
                updateX(vx * 2, lx, mid, x, y, nval);
            else
                updateX(vx * 2 + 1, mid + 1, rx, x, y, nval);
        }
        updateY(vx, lx, rx, 1, 0, m - 1, x, y, nval);
    }



    void build(vector<vector<int>> &a) {
        buildX(a, 1, 0, n - 1);
    }

    Node get(int x, int y, int xx, int yy) {
        return getX(1, 0, n - 1, x, xx, y, yy);
    }

    void set(int r, int c, int val) {
        updateX(1, 0, n - 1, r, c, val);
    }
};

