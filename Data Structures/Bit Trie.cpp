struct Node {
    Node*child[2];
    int freq[2];
    Node() {
        child[0]=child[1]=0;
        freq[0]=freq[1]=0;
    }
};
struct Trie {
    Node* root = new Node();
    void insert(int n) {
        Node*curr = root;
        for (int i = 31 ; i >=0; i--) {
            int idx = (n >> i) & 1;
            if (curr->child[idx] == 0) {
                curr->child[idx] = new Node();
            }
            curr->freq[idx]++;
            curr = curr->child[idx];
        }
    }
    void erase(int n , int i , Node*curr) {
        if (i == -1) {return;}
        int idx = (n >> i) & 1;
        erase(n,i-1,curr->child[idx]);
        curr->freq[idx]--;
        if (curr->freq[idx] == 0) {
            delete curr->child[idx];
            curr->child[idx] = 0;
        }
    }

    int max_xor(int n) {
        Node*curr = root;
        int res = 0 ;
        for (int i = 29 ; i >= 0; i--) {
            int idx = (n >> i) & 1;
            if (curr->child[idx^1]==0) {
                curr=curr->child[idx];
            }
            else {
                curr=curr->child[idx^1];
                res|=(1<<i);
            }
        }
        return res;
    }
};