struct Node {
    Node* character[26];
    int prefix , end ;
    Node() {
        prefix = end = 0;
        memset(character , 0 , sizeof(character));
    }
};

struct Trie {
    Node* root = new Node();

    void insert(str &s) {
        Node* cur = root;
        for (auto i : s) {
            int idx = i - 'a';
            if (cur->character[idx] == 0) {
                cur->character[idx] = new Node();
            }
            cur = cur->character[idx];
            cur->prefix++;
        }
        cur->end++;
    }

    int count(str &s) {
        Node* cur = root;
        for (auto i : s) {
            int idx = i - 'a';
            if (cur->character[idx] == 0) {
                return 0;
            }
            cur = cur->character[idx];
        }
        return cur->end;
    }
};