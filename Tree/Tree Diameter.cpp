pair<int,int> calc(int node , int parent) { // return pair(diameter , height)
    int diam = 0 ;
    vector<int> mxHeight {-1,-1,-1}; // keep 2 highest trees
    for (auto child : adj[node]) {
        if (child != parent) {
            pair<int,int> d = calc(child, node);
            diam = max(diam,d.first);
            mxHeight[0]=d.second+1;
            sort(all(mxHeight));
        }
    }
    for (int i = 0 ; i < 3; i ++) {
        if (mxHeight[i]==-1) { mxHeight[i]=0; }
    }
    diam = max(diam,mxHeight[1]+mxHeight[2]);
    return make_pair(diam,mxHeight[2]);
}
int diameter(int root){ return calc(root,-1).first; }