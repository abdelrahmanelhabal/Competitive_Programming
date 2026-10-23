/*
 * ============================================================
 * PROBLEM: Prime Gift
 * ============================================================
 * We are given n distinct primes (1 <= n <= 16, each <= 100).
 * Consider all positive integers whose prime divisors all
 * belong to this set (1 is included). Find the k-th smallest
 * of them. The answer is guaranteed to be <= 10^18.
 *
 * Example:
 *   primes = {2, 3, 5}, k = 7
 *   sequence: 1, 2, 3, 4, 5, 6, 8, ...  -> answer = 8
 *
 * ============================================================
 * SOLUTION: Meet in the middle + binary search on the answer
 * ============================================================
 * Why not generate everything?
 *   With 16 primes, there are far too many valid numbers
 *   <= 10^18 to store and sort.
 *
 * Idea:
 *   1. Split the primes into two groups (alternating: 1st, 3rd,
 *      5th... go to group 1; 2nd, 4th, 6th... go to group 2).
 *      Alternating keeps both groups balanced in size, because
 *      small primes produce many more numbers than large ones.
 *   2. For each group, generate (by DFS) every product <= 10^18.
 *      Call the sorted lists A1 and A2. Each has at most a few
 *      million values.
 *   3. Every valid number is exactly x = a * b with a in A1 and
 *      b in A2, and this representation is unique, because the
 *      two groups use different primes.
 *   4. Binary search the answer X in [1, 10^18]:
 *        count(X) = number of pairs (a, b) with a * b <= X.
 *      Find the smallest X such that count(X) >= k.
 *   5. count(X) uses two pointers: as a grows in A1, the largest
 *      usable b in A2 only moves left, so one pass is enough.
 *      The check INF / a < b prevents overflow in a * b.
 *
 * Complexity:
 *   Generation : O(|A1| + |A2|) after sorting
 *   Each count : O(|A1| + |A2|)
 *   Total      : O((|A1| + |A2|) * log(10^18)), about 60 passes
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(x) begin(x), end(x)
#define endl '\n'

int const INF = 1e18;

// Generate all products of the primes in c that are <= INF
vector<int> divide(vector<int> c) {
    int len = c.size();
    vector<int> res;
    function<void(int, int)> go = [&](int i, int p) {
        if (i == len) {
            res.emplace_back(p);
            return;
        }
        while (true) {
            go(i + 1, p);                  // use prime c[i] zero or more times
            if (INF / c[i] < p) break;     // next multiplication would overflow
            p *= c[i];
        }
    };
    go(0, 1);
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(all(a));

    // Split primes alternately into two balanced groups
    vector<int> g1, g2;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) g1.push_back(a[i]);
        else g2.push_back(a[i]);
    }

    auto a1 = divide(g1);
    auto a2 = divide(g2);
    sort(all(a1));
    sort(all(a2));

    int k;
    cin >> k;

    // How many valid numbers are <= x ? Return true if at least k.
    auto can = [&](int x) {
        int cnt = 0, j = a2.size() - 1;
        for (int y : a1) {
            while (j >= 0 && INF / y < a2[j]) j--;   // avoid overflow
            while (j >= 0 && a2[j] * y > x) j--;     // shrink to fit <= x
            if (j >= 0) cnt += j + 1;
        }
        return cnt >= k;
    };

    // Binary search for the smallest x with count(x) >= k
    int l = 1, r = 1e18, res = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (can(mid)) {
            r = mid - 1;
            res = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << res << endl;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
