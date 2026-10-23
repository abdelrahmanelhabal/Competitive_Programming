/*
 * ============================================================
 * PROBLEM: Make Them Similar
 * ============================================================
 * Two numbers are "similar" if their binary representations
 * contain the same number of 1 bits.
 * Given an array a[1..n] (2 <= n <= 100, 0 <= a[i] < 2^30),
 * choose a non-negative integer x (x < 2^30) and form
 *   b[i] = a[i] XOR x.
 * Can all b[i] be similar to each other? If yes, print any
 * valid x, otherwise print -1.
 *
 * Example:
 *   a = {7, 2}  ->  x = 1  gives {6, 3}, both have two 1 bits.
 *
 * ============================================================
 * SOLUTION: Meet in the middle on the bits of x
 * ============================================================
 * Brute force: 2^30 candidates for x, each checked in O(n)
 * -> too slow.
 *
 * Idea:
 *   1. Split the 30 bits into a low half (15 bits) and a high
 *      half (15 bits). Write x = (xHigh << 15) | xLow.
 *      Then for every i:
 *        popcount(a[i] ^ x) = popcount(low part ^ xLow)
 *                           + popcount(high part ^ xHigh)
 *   2. All elements are similar iff popcount(b[i]) equals
 *      popcount(b[0]) for every i, i.e. for i = 1..n-1:
 *        (lowDiff[i] + highDiff[i]) = 0
 *      where  lowDiff[i]  = pc(low(a[i]) ^ xLow) - pc(low(a[0]) ^ xLow)
 *             highDiff[i] = same thing for the high halves.
 *   3. For every xLow in [0, 2^15) compute the vector lowDiff
 *      and store it in a map: vector -> xLow.
 *   4. For every xHigh in [0, 2^15) compute the vector highDiff,
 *      negate it, and look it up in the map. A hit means
 *      lowDiff + highDiff = 0 for all i, so x = (xHigh << 15) | xLow
 *      works.
 *   5. If no xHigh finds a match, print -1.
 *
 * Complexity:
 *   Time : O(2^15 * n * log(2^15))  (map comparisons of vectors)
 *   Space: O(2^15 * n)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(x) begin(x), end(x)
#define endl '\n'

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int B = 15, M = (1 << B) - 1;

    // Low half: map (popcount differences relative to a[0]) -> xLow
    map<vector<int>, int> f;
    for (int mask = 0; mask < (1ll << B); mask++) {
        vector<int> b;
        int q1 = __builtin_popcountll((a[0] & M) ^ mask);
        for (int i = 1; i < n; i++) {
            int q2 = __builtin_popcountll((a[i] & M) ^ mask);
            b.emplace_back(q2 - q1);
        }
        f[b] = mask;
    }

    // High half: look for the negated difference vector
    for (int mask = 0; mask < (1ll << B); mask++) {
        vector<int> b;
        int q1 = __builtin_popcountll((a[0] >> B) ^ mask);
        for (int i = 1; i < n; i++) {
            int q2 = __builtin_popcountll((a[i] >> B) ^ mask);
            b.emplace_back(-(q2 - q1));
        }
        auto it = f.find(b);
        if (it == f.end()) continue;
        cout << ((mask << B) | it->second) << endl;
        return;
    }
    cout << -1 << endl;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
