struct DominatorTree {
    int n, T = 0;
    vector<vector<int>> g, rg, bucket, tree;
    vector<int> arr, rev, par, sdom, dom, dsu, label;
    vector<int> idom;

    DominatorTree(int n) : n(n) {
        g.resize(n+1);
        rg.resize(n+1);
        bucket.resize(n+1);
        tree.resize(n+1);

        arr.resize(n+1);
        rev.resize(n+1);
        par.resize(n+1);
        sdom.resize(n+1);
        dom.resize(n+1);
        dsu.resize(n+1);
        label.resize(n+1);
        idom.resize(n+1, -1);

        for(int i=0;i<=n;i++){
            sdom[i]=dom[i]=dsu[i]=label[i]=i;
        }
    }

    void addEdge(int u,int v){
        g[u].push_back(v);
    }

    void dfs(int v){
        T++;
        arr[v]=T;
        rev[T]=v;
        label[T]=sdom[T]=dsu[T]=T;

        for(int to:g[v]){
            if(!arr[to]){
                dfs(to);
                par[arr[to]]=arr[v];
            }
            rg[arr[to]].push_back(arr[v]);
        }
    }

    int find(int v,int x=0){
        if(v==dsu[v]) return x?-1:v;
        int u=find(dsu[v],x+1);
        if(u<0) return v;
        if(sdom[label[dsu[v]]] < sdom[label[v]])
            label[v]=label[dsu[v]];
        dsu[v]=u;
        return x?u:label[v];
    }

    void unite(int u,int v){
        dsu[v]=u;
    }

    vector<vector<int>> build(int src){
        dfs(src);
        int N=T;

        for(int i=N;i>=1;i--){
            for(int j:rg[i])
                sdom[i]=min(sdom[i], sdom[find(j)]);
            if(i>1) bucket[sdom[i]].push_back(i);

            for(int j:bucket[i]){
                int v=find(j);
                if(sdom[v]==sdom[j]) dom[j]=sdom[j];
                else dom[j]=v;
            }

            if(i>1) unite(par[i],i);
        }

        for(int i=2;i<=N;i++){
            if(dom[i]!=sdom[i])
                dom[i]=dom[dom[i]];

            int u = rev[dom[i]];
            int v = rev[i];

            tree[u].push_back(v);
            // tree[v].push_back(u);

            idom[v] = u;
        }

        idom[src] = -1;
        return tree;
    }
};
