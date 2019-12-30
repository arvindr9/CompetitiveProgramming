#include <bits/stdc++.h>

using namespace std;

/*
    Author: Arvind Ramaswami

    Solution:

    Let the original graph be G.

    Consider the graph H with the edges with weight 1 removed. This will be a set of connected
    components. In order for there to be a spanning tree in G, there must be edges of weight
    1 that cause H to be connected. Thus, we can use dsu to find these desired edges.

    After finding the desired edges of weight 1, add arbitrary edges of weight 1 until
    the total number of edges is equal to K (using dsu). Then, add edges of weight 0
    to the dsu until the spanning tree is created.

*/

typedef pair<int, int> pi;

const int maxn = 1e5 + 5;
const int maxm = 2e5 + 5;

int n, m, k;

vector<pi> z_edges;
vector<pi> o_edges;

vector<int> z_adj[maxn];
int color = 0;
int component[maxn], link[maxn], sz[maxn];

int find(int x) {
    if (x == link[x]) return x;
    return link[x] = find(link[x]);
}

bool same(int x, int y) {
    return find(x) == find(y);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (sz[x] < sz[y]) {
        swap(x, y);
    }
    link[y] = x;
    sz[y] += sz[x];
}

void dfs(int u) {
    if (component[u]) return;
    component[u] = color;
    for (int v: z_adj[u]) {
        dfs(v);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("karb.in", "r", stdin);
    freopen("karb.out", "w", stdout);

    cin >> n >> m >> k;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (w == 0) {
            z_adj[u].push_back(v);
            z_adj[v].push_back(u);
            z_edges.push_back({u, v});
        } else {
            o_edges.push_back({u, v});
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!component[i]) {
            color++;
            dfs(i);
        }
    }

    int num_ones = 0;

    vector<pi> keep;

    for (int i = 1; i <= color; i++) {
        link[i] = i;
        sz[i] = 1;
    }

    for (pi p: o_edges) {
        int u = p.first;
        int v = p.second;
        int cu = component[u];
        int cv = component[v];
        if (cu != cv) {
            if (!same(cu, cv)) {
                unite(cu, cv);
                keep.push_back({u, v});
                num_ones++;
            }
        }
    }

    //now reset the graph dsu

    for (int i = 1; i <= n; i++) {
        link[i] = i;
        sz[i] = 1;
    }

    vector<pi> ans;

    for (pi p: keep) {
        int u, v;
        tie(u, v) = p;
        unite(u, v);
        ans.push_back({u, v});
    }

    int ind = 0;
    while (num_ones < k && ind < (int)o_edges.size()) {
        int u, v;
        tie(u, v) = o_edges[ind];
        // cout << "zero edge: " << u << " " << v << "\n";
        if (!same(u, v)) {
            unite(u, v);
            ans.push_back({u, v});
            num_ones++;
        }
        ind++;
    }

    for (pi p: z_edges) {
        int u, v;
        tie(u, v) = p;
        if (!same(u, v)) {
            unite(u, v);
            ans.push_back({u, v});
        }
    }

    for (pi p: ans) {
        cout << p.first << " " << p.second << "\n";
    }



}