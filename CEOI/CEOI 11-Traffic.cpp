#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;

const int maxn = 3e5 + 5;
int x[maxn], y[maxn], keep[maxn], visited[maxn], maxreach[maxn], minreach[maxn], endindex[maxn], orderindex[maxn];


int maxval, minval;

int n, m, A, B;

vector<int> start_nodes;
vector<int> end_nodes;
vector<int> adj[maxn];
vector<int> adjr[maxn];

/*

Author: Arvind Ramaswami

The graph is planar, so each start node will be able to reach an interval of end nodes.

First, mark all start nodes that can reach an end node and mark all end nodes that can
be reached by a start node.

For each start node (in order from bottom to top), use dfs to find the topmost end node that
can be reached. Similarly (in order from top to bottom), use dfs to find the bottommost end node
that can be reached. This gives the reachable intervals for each start node.

The answer for each start node is the number of nodes in its interval (if it can reach an end node)
or 0 otherwise.

*/

void dfs(int u) {
    if (visited[u]) return;
    visited[u] = 1;
    if (x[u] == A) {
        maxval = max(maxval, u);
        minval = min(minval, u);
    }
    for (int v: adj[u]) {
        dfs(v);
    }
}

void dfs2(int u) {
    if (visited[u]) return;
    visited[u] = 1;
    for (int v: adjr[u]) {
        dfs2(v);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("traffic.in", "r", stdin);
    // freopen("traffic.out", "w", stdout);
    cin >> n >> m >> A >> B;

    vector<pair<pi,int>>  coordinates;

    for (int i = 1; i <= n; i++) {
        int _x, _y;
        cin >> _x >> _y;
        coordinates.push_back(make_pair(make_pair(_x, _y), i));
    }

    sort(coordinates.begin(), coordinates.end());

    for (int i = 1; i <= n; i++) {
        pi coord = coordinates[i - 1].first;
        x[i]= coord.first;
        y[i] = coord.second;

        int index = coordinates[i - 1].second;
        orderindex[index] = i;

        if (x[i] == 0) {
            start_nodes.push_back(i);
        }
        if (x[i] == A) {
            end_nodes.push_back(i);
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v, k;
        cin >> u >> v >> k;
        u = orderindex[u];
        v = orderindex[v];
        adj[u].push_back(v);
        adjr[v].push_back(u);
        if (k == 2) {
            adj[v].push_back(u);
            adjr[u].push_back(v);
        }
    }

    // eliminate end nodes

    for (int u: start_nodes) {
        dfs(u);
    }

    for (int u: end_nodes) {
        if (visited[u]) {
            keep[u] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }

    // eliminate start nodes

    for (int u: end_nodes) {
        dfs2(u);
    }

    for (int u: start_nodes) {
        if (visited[u]) {
            keep[u] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }

    // give indices to the reachable end nodes

    int index = 0;
    for (int u: end_nodes) {
        if (keep[u]) {
            index++;
            endindex[u] = index;
        }
    }

    // find max values of intervals for start nodes

    maxval = -1;
    for (int u: start_nodes) {
        if (keep[u]) {
            dfs(u);
            maxreach[u] = maxval;
        }
    }

    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }

    // find min values of intervals for start nodes

    minval = 1e9 + 5;

    for (auto it = start_nodes.rbegin(); it != start_nodes.rend(); it++) {
        int u = *it;
        if (keep[u]) {
            dfs(u);
            minreach[u] = minval;
        }
    }

    // compute result for each start node

    vector<int> ans;



    for (int u: start_nodes) {
        if (keep[u]) {
            ans.push_back(endindex[maxreach[u]] - endindex[minreach[u]] + 1);
        } else {
            ans.push_back(0);
        }
    }

    for (int i = (int)ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << "\n";
    }


}
