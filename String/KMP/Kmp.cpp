struct KMP {
    vector<int> pi, z;

    /**
     * Computes the prefix-function (pi array) for string s:
     * pi[i] = length of the longest proper prefix of s[0..i] which is also a suffix of s[0..i].
     * Time: O(n)
     */
    void prefixFunction(const string&s) {
        int n = (int)s.size();
        if (pi.size()  <= n) {pi.clear();pi.resize(n);}
        for (int i = 1, j = 0 ; i < n ; i++) {
            j = pi[i-1];
            while (j && s[i]!=s[j]) j = pi[j-1];
            if (s[i] == s[j])j++;
            pi[i] = j ;
        }
    }

    /**
     * Computes the Z-array for string s:
     * z[i] = length of the longest substring starting at i which is also a prefix of s.
     * Time: O(n)
     */
    void Z_function(const string&s) {
        int n = (int)s.size(),l=0,r=0;
        z.assign(n,0);
        for (int i = 1 ; i< n ; i++) {
            if (i <=r) z[i] = min(r - i + 1 , z[i - l]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
            if (i + z[i]-1 > r) l = i , r = i + z[i] - 1 ;
        }
    }

    /**
     * Finds all occurrences of pattern t in text s using KMP matching.
     * Time: O(n + m) where n = s.size(), m = t.size()
     */
    vector<int> pattern(const string&s , const string &t) {
        KMP temp ;
        temp.prefixFunction(t);
        int n = (int) s.size() , m = (int) t.size() , k = 0;
        vector<int>pos;
        for (int i = 0 ; i< n; i ++) {
            while (k && s[i] != t[k]) { k = temp.pi[k-1]; }
            if (s[i] == t[k]) { k++; }
            if (k == m) {
                pos.emplace_back(i - m + 1);
                k = temp.pi[k-1];
            }
        }
        return pos;
    }

    /**
     * Compute the minimum characters to append to the end of s to make it a palindrome.
     * Uses prefix-function on reversed + '#' + original to detect the longest palindromic suffix.
     * Time: O(n)
     */
    pair<int,string> LongestPalindromicSuffix(const string&s) {
        KMP temp ;
        string rev = s ;
        reverse(all(rev));
        string x = rev + '#' + s ;
        temp.prefixFunction(x);
        int res = temp.pi[x.size()-1];
        string t = s.substr(0,s.size()-res);
        reverse(all(t));
        string res2 = s + t ;
        return {res,res2};
    }

    /**
     * Compute the minimum characters to prepend to the beginning of s to make it a palindrome.
     * Uses prefix-function on s + '@' + reverse(s) to detect the longest palindromic prefix.
     * Time: O(n)
     */
    static pair<int,string> longestPalindromicPrefix(const string &s) {
        KMP temp;
        string rev = s;
        reverse(rev.begin(), rev.end());
        string x = s + '@' + rev;
        temp.prefixFunction(x);
        int res = temp.pi[x.size() - 1];
        string t = s.substr(res) ;
        reverse(t.begin() , t.end());
        string res1 = t + s;
        return make_pair(res , res1);
    }

    /**
     * For every prefix length L (1..n) computes how many times the prefix s[0..L-1]
     * appears as a substring (specifically as a border) across all prefixes of s.
     * Time: O(n)
     * Usage: useful to count how many times each border occurs, or to detect repeated prefixes.
     */
    vector<int> freqAllPrefix(const string&s) {
        KMP temp ;
        temp.prefixFunction(s);
        vector<int>freq(s.size()+1);
        for (int i = 0 ; i< s.size();i++) { freq[temp.pi[i]]++; }
        for (int i = s.size()-1 ; i >=0 ; i--) {
            freq[temp.pi[i]] += freq[i];
        }
        freq.erase(freq.begin());
        for (auto&val : freq) val++;
        return freq;
    }

    /**
     * Count how many prefixes of s occur exactly once in the string (i.e., unique prefixes).
     * Implementation: reuses freqAllPrefix and counts entries equal to 1.
     * Time: O(n)
     */
    int CountUniquePrefixes(const string &s){
        vector<int> temp = KMP::freqAllPrefix(s);
        return count(temp.begin() , temp.end() , 1);
    }

     /**
     * Check whether pattern pat appears at least twice in s (non-overlap allowed).
     * Uses prefix-function computed on pat and runs KMP over s to count occurrences.
     * Time: O(n + m)
     */
    bool hasRepeatKMP(const string &s, const string &pat) {
        int n = s.size(), m = pat.size(), j = 0;
        prefixFunction(pat);
        int count = 0;

        for (int i = 0; i < n; i++) {
            while (j > 0 && s[i] != pat[j]) j = pi[j - 1];
            if (s[i] == pat[j]) j++;
            if (j == m) {
                count++;
                j = pi[j - 1];
                if (count >= 2) return true;
            }
        }
        return false;
    }

    /**
     * Finds one longest substring that occurs at least twice in s.
     * Complexity:
     *  - Worst-case O(n^2 * log n) in this particular implementation (because for each mid we iterate all substrings and KMP over s).
     *  - Note: there are faster approaches (suffix array / suffix automaton / rolling-hash + hash map) to obtain O(n log n) or O(n).
     */
    string longestRepeatingSubstring(const string &s) {
        int n = s.size();
        int low = 1, high = n - 1, bestLen = 0;
        string bestSub = "-1";

        while (low <= high) {
            int mid = (low + high) / 2;
            bool found = false;
            string candidate;

            for (int i = 0; i + mid <= n; i++) {
                string sub = s.substr(i, mid);
                if (hasRepeatKMP(s, sub)) {
                    found = true;
                    candidate = sub;
                    break;
                }
            }

            if (found) {
                bestLen = mid;
                bestSub = candidate;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return bestSub;
    }

    /**
     * Compute number of distinct substrings of s using a trick with prefix-function:
     * Implementation detail:
     *  - For each suffix starting at i, we consider the reversed prefix and count unique prefixes via CountUniquePrefixes.
     * Complexity:
     *  - This is an O(n^2) approach because for each i it computes CountUniquePrefixes on a growing string.
     *  - For large strings consider suffix array / suffix automaton which compute distinct substrings in O(n).
     * Note: This function uses reversing trick and CountUniquePrefixes to count distinct substrings.
     */
    int uniqueSubString(const string&s) {
        string cur ;
        int n = (int) s.size();
        int res = 0 ;
        for (int i = 0; i < n ; i++) {
            cur+=s[i];
            string tt = cur;
            reverse(all(tt));
            res += CountUniquePrefixes(tt);
        }
        return res;
    }

    /**
     * Finds longest palindromic substring of s using a manacher-like transform:
     *  - builds interleaved string t = # s[0] # s[1] # ... to treat even/odd lengths uniformly
     *  - computes array Z (here named Z but function is similar to Manacher radius)
     *  - recovers longest palindrome in original string coordinates
     * Time: O(n)
     * Note: This is effectively Manacher's algorithm implemented with an explicit transformed string.
     */
    string longestPalindromicSubstring(const string &s) {
        int n = s.size();
        if (n == 0) return "";
        if (n == 1) return s;

        string t = "#";
        for (int i = 0 ; i < n ; i++) {
            t += s[i];
            t += '#';
        }

        int m = t.size();
        vector<int> Z(m, 0);
        int l = 0 , r = 0 ;
        for (int i = 1; i < m; i++) {
            int minR = 2 * l - i;
            if (i < r) Z[i] = min(r - i, Z[minR]);
            while (i + Z[i] + 1 < m && i - Z[i] - 1 >= 0 && t[i + Z[i] + 1] == t[i - Z[i] - 1])
                Z[i]++;
            if (i + Z[i] > r) {
                l = i;
                r = i + Z[i];
            }
        }

        int maxLen = 0, center = 0;
        for (int i = 0; i < m; i++) {
            if (Z[i] > maxLen) {
                maxLen = Z[i];
                center = i;
            }
        }
        int start = (center - maxLen) / 2;
        return s.substr(start, maxLen);
    }

    /**
     * Finds the lexicographically smallest rotation (cyclic shift) of s.
     * Implementation is similar in spirit to Booth's algorithm:
     * Time: O(n)
     */
    string minimalRotation(const string &s) {
        // min rotation to get a smallest lexicographically string rotation is shift the string For example, the rotations of acab are acab, caba, abac, and baca.
        int n = s.size();
        string doubled = s + s;
        vector<int> f(2 * n, -1);
        int k = 0;
        for (int j = 1; j < 2 * n; j++) {
            char c = doubled[j];
            int i = f[j - k - 1];
            while (i != -1 && c != doubled[k + i + 1]) {
                if (c < doubled[k + i + 1]) k = j - i - 1;
                i = f[i];
            }
            if (c != doubled[k + i + 1]) {
                if (c < doubled[k]) k = j;
                f[j - k] = -1;
            } else {
                f[j - k] = i + 1;
            }
        }
        return doubled.substr(k, n);
    }
};

