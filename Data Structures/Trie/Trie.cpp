struct node {
    node* ch[26];
    int prefix , end ;
    node() {
        prefix = end = 0 ;
        memset(ch,0,sizeof(ch));
    }
};
struct trie {
    node *root = new node();
    void insert(str &s) const {
        node *cur = root;
        for (auto c : s) {
            int idx = c - 'a' ;
            if (cur->ch[idx] == nullptr) {
                cur->ch[idx] = new node();
            }
            cur = cur->ch[idx];
            cur->prefix++;
        }
        cur->end++;
    }
    int count(str &s) const {
        node *cur = root;
        for (auto c : s) {
            int idx = c - 'a';
            if (cur->ch[idx] == nullptr) {
                return 0;
            }
            cur = cur->ch[idx];
        }
        return cur->end;
    }
};

