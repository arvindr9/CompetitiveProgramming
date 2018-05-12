#include <iostream>
#include <set>

using namespace std;

typedef long long ll;

const int maxn = 200010;

int link[maxn];
int siz[maxn];
set<pair<int, int>> edges; // higher-numbered node is first
int k;

inline int n_square(long long u) {
    return (-(u * u) % k + k) % k;
}

int find(int u) {
    while (link[u] != u) {
        u = link[u];
    }
    return u;
}

bool same(int u, int v) {
    return find(u) == find(v);
}

void unite(int u, int v) {
    u = find(u);
    v = find(v);
    if (siz[u] > siz[v]) {
        swap(u, v);
    } //size[u] <= size[v]
    link[u] = v;
}

void addEdges(int u) {
    int v = n_square(u);
    for (int i = 0; u + i * k <= 2 * k + 1; i++) {
        for (int j = 0; v + j * k <= 2 * k + 1; j++) {
            int u2 = u + i * k;
            int v2 = v + j * k;
            if (u2 > v2) {
                swap(u2, v2);
            }
            if (u2 == v2 || u2 == 0 || v2 == 0) {
                continue;
            } // u2 < v2
            edges.insert({v2, u2});
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> k;
    for (int i = 1; i <= 2 * k + 1; i++) {
        link[i] = i;
        siz[i] = 1;

    }
    for (int i = 1; i <= k; i++) {
        addEdges(i);
    }
    int ans = 0;
    for (pair<int, int> edge: edges) {
        int n1 = edge.first; int n2 = edge.second;
        if (!same(n1, n2)) {
            unite(n1, n2);
        } else {
            ans = n1;
            break;
        }
    }
    cout << ans << "\n";

}