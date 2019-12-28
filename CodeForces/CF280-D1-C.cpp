/*
    Author: Arvind Ramaswami

    Solution: Let X_i be the variable that denotes whether or not
    vertex i is chosen in the game. We thus want to find
    E[X_1 + X_2 + ... + X_n] = \sum_{i = 1}^{n} E[X_i].

    Define depth[v] to be 1 at the root and to be equal
    depth[parent(v)] + 1 at the other nodes.
    
    When vertex i is deleted, we know that some vertex that is
    an ancestor of i (or i itself) must have been chosen.
    Each ancestor has an equal probability of being chosen (1 / depth[i]);
    thus, E[X_i] = (1 / depth[i]).

    Thus, the desired answer is \sum_{i = 1}^n 1 / depth[i].

*/

#include <bits/stdc++.h>

using namespace std;


const int maxn = 1e5 + 5;


int depth[maxn];
vector<int> adj[maxn];
int n;

void dfs(int u, int p = 1) {
    if (depth[u]) return;
    depth[u] = depth[p] + 1;
    for (int v: adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    long double ans = 0;
    // for (int i = 1; i <= n; i++) {
    //     cout << "depth: " << depth[i] << "\n";
    // }
    cout << setprecision(7) << fixed;
    for (int i = 1; i <= n; i++) {
        ans += (long double)1 / (long double)depth[i];
    }
    cout << ans << "\n";
}