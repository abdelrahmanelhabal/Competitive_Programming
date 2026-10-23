/*
 * ============================================================
 * PROBLEM: Number Clicker
 * ============================================================
 * Allen starts with an integer u on the screen. Each second
 * he presses one of 3 buttons (all arithmetic is modulo a
 * prime p, 3 <= p <= 10^9 + 9):
 *   1. u -> u + 1
 *   2. u -> u - 1          (u + p - 1)
 *   3. u -> u^(p-2)        (modular inverse of u, 0 stays 0)
 * Using at most 200 presses, reach the value v.
 * Print the number of presses and the sequence of buttons.
 * A solution is always guaranteed to exist.
 *
 * Example:
 *   u = 1, v = 3, p = 5  ->  2 presses: "1 1"   (1 -> 2 -> 3)
 *
 * ============================================================
 * SOLUTION: Bidirectional BFS
 * ============================================================
 * The graph has p nodes (up to 10^9), so a plain BFS is too big.
 * But the three operations behave like a random graph, so
 * paths between nodes are short (about log p levels), and two
 * searches that meet in the middle only need about sqrt(p)
 * states each (birthday paradox).
 *
 * Steps:
 *   1. BFS forward from u, limited to ~300000 discovered states.
 *      Store dis (distance), par (parent) and op (button used).
 *      If v is reached here, print the path and finish.
 *   2. Otherwise BFS backward from v, again limited to ~300000
 *      states. Moving backwards we use the inverse operations:
 *        - the reverse of "+1" is "-1", so a step to u + 1
 *          records button 2 (pressing 2 goes back to u),
 *        - the reverse of "-1" is "+1", so a step to u - 1
 *          records button 1,
 *        - button 3 (inverse) is its own reverse.
 *      Stop as soon as a newly found node is already known to
 *      the forward search. Call that node "ee".
 *   3. Answer = forward path u -> ee  followed by
 *               backward path ee -> v.
 *      Each side is under 100 levels deep (the "step" limit),
 *      so the total length is at most 200.
 *
 * Complexity:
 *   About 300000 states per side, each with a modular
 *   exponentiation of O(log p) for the inverse.
 *   Memory: a few maps with ~300000 entries each.
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(x) begin(x), end(x)
#define endl '\n'

int fast_pow(int base, int power, int mod) {
    int res = 1;
    while (power > 0) {
        if (power & 1) res = res * base % mod;
        base = base * base % mod;
        power >>= 1;
    }
    return res;
}

int inv(int x, int mod) { return fast_pow(x, mod - 2, mod); }  // button 3
int add(int x, int mod) { return (x + 1) % mod; }              // button 1
int sub(int x, int mod) { return (x + mod - 1) % mod; }        // button 2

void solve() {
    int s, e, p;
    cin >> s >> e >> p;
    int step = 100;  // max depth per side, so total <= 200

    // ---------- Forward BFS from s ----------
    map<int, int> dis, par, op;
    queue<int> q;
    dis[s] = 0;
    par[s] = op[s] = -1;
    q.emplace(s);
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        if (u == e) break;
        if (dis.size() > 300000) break;

        int v = add(u, p);
        if (dis.count(v) == 0) {
            dis[v] = dis[u] + 1;
            if (dis[v] < step) q.emplace(v);
            par[v] = u;
            op[v] = 1;
        }
        v = sub(u, p);
        if (dis.count(v) == 0) {
            dis[v] = dis[u] + 1;
            if (dis[v] < step) q.emplace(v);
            par[v] = u;
            op[v] = 2;
        }
        v = inv(u, p);
        if (dis.count(v) == 0) {
            dis[v] = dis[u] + 1;
            if (dis[v] < step) q.emplace(v);
            par[v] = u;
            op[v] = 3;
        }
    }

    // Target reached directly by the forward search
    if (dis.count(e)) {
        cout << dis[e] << endl;
        vector<int> path;
        int cur = e;
        while (cur != -1) {
            path.push_back(op[cur]);
            cur = par[cur];
        }
        path.pop_back();  // remove the -1 of the start node
        reverse(all(path));
        for (auto x : path) cout << x << " ";
        cout << endl;
        return;
    }

    // ---------- Backward BFS from e (inverse operations) ----------
    int ee = -1;  // meeting node
    map<int, int> dis2, par2, op2;
    queue<int> q2;
    dis2[e] = 0;
    par2[e] = op2[e] = -1;
    q2.emplace(e);
    while (!q2.empty()) {
        auto u = q2.front();
        q2.pop();
        if (dis2.size() > 300000) break;

        int v = add(u, p);  // from v, pressing "-1" reaches u
        if (dis2.count(v) == 0) {
            dis2[v] = dis2[u] + 1;
            if (dis2[v] < step) q2.emplace(v);
            par2[v] = u;
            op2[v] = 2;
            if (dis.count(v)) { ee = v; break; }
        }
        v = sub(u, p);      // from v, pressing "+1" reaches u
        if (dis2.count(v) == 0) {
            dis2[v] = dis2[u] + 1;
            if (dis2[v] < step) q2.emplace(v);
            par2[v] = u;
            op2[v] = 1;
            if (dis.count(v)) { ee = v; break; }
        }
        v = inv(u, p);      // inverse is its own reverse
        if (dis2.count(v) == 0) {
            dis2[v] = dis2[u] + 1;
            if (dis2[v] < step) q2.emplace(v);
            par2[v] = u;
            op2[v] = 3;
            if (dis.count(v)) { ee = v; break; }
        }
    }

    // ---------- Join the two halves ----------
    vector<int> path1, path2;

    // ee -> e (already in the correct order)
    int cur = ee;
    while (cur != -1) {
        path2.push_back(op2[cur]);
        cur = par2[cur];
    }
    path2.pop_back();

    // s -> ee (collected backwards, so reverse)
    cur = ee;
    while (cur != -1) {
        path1.push_back(op[cur]);
        cur = par[cur];
    }
    path1.pop_back();
    reverse(all(path1));

    for (auto x : path2) path1.push_back(x);

    cout << path1.size() << endl;
    for (auto x : path1) cout << x << " ";
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
