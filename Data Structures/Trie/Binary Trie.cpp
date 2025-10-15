struct node {
    node*ch[2];
    int freq[2] , cnt ;
    node() {
        ch[0] = ch[1] = nullptr ;
        freq[0] = freq[1] = 0;
        cnt = 0 ;
    }
};
struct trie {
    node*root = new node();

    void insert(int n) const  {
        node*cur = root;
        for (int i = 30 ; i >= 0 ; i--) {
            int idx =  (n >> i) & 1 ;
            if (cur->ch[idx] == nullptr ) {
                cur->ch[idx] = new node();
            }
            cur->freq[idx]++;
            cur = cur->ch[idx];
            cur->cnt++;
        }
    }
    void erase(int n , int bit , node*cur) const {
        if (bit == -1)return;
        int idx = (n >> bit) & 1 ;
        if (!cur->ch[idx]) return;
        erase(n,bit-1,cur->ch[idx]);
        cur->freq[idx]--;
        cur->cnt--;
        if (cur->freq[idx]==0) {
            delete cur->ch[idx];
            cur->ch[idx] = nullptr;
        }
    }
    int max_xor(int n) const {
        node*cur = root;
        int res = 0 ;
        for (int i = 30 ; i >= 0 ; i--) {
            int idx = (n >> i) & 1 ;
            if (cur->ch[idx^1] == nullptr) {
                cur = cur->ch[idx];

            }
            else {
                cur = cur->ch[idx^1];
                res |= (1 << i);
            }
        }
        return res;
    }
    int min_xor(int x) {
        node* cur = root;
        int res = 0;
        for (int i = 30; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (cur->ch[b] && cur->ch[b]->cnt > 0) {
                cur = cur->ch[b];
            } else {
                res |= (1LL << i);
                cur = cur->ch[b ^ 1];
            }
        }
        return res;
    }

    int query(int x, int k) const { // number of values  val ^ x < k
        node* cur = root;
        int ans = 0;
        for (int i = 30 ; i >= 0; i--) {
            if (cur == nullptr) break;
            int b1 = x >> i & 1, b2 = k >> i & 1;
            if (b2 == 1) {
                if (cur -> ch[b1]) ans += cur -> freq[b1]; // (val_bit ^ b1) = 0 branch → smaller
                cur = cur -> ch[!b1]; // (val_bit ^ b1) = 1 branch → equals
            } else cur = cur -> ch[b1];
        }
        return ans;
    }
    
    
    int mex_with_x(int x){
        node* cur = root;
        long long mex = 0;
        for(int i = 30; i >= 0; --i){
            if(!cur) break; 
            int xi = (x >> i) & 1;
            long long capacity = 1LL << i;
            node* child0 = cur->ch[xi]; 
            if(child0 == nullptr || child0->cnt < capacity){
                cur = child0;
            } else {
                mex |= (1LL << i);
                node* child1 = cur->ch[1 ^ xi];
                cur = child1;
            }
        }
        return mex;
    }
  
};
