/*
    Author: Arvind Ramaswami

    Note that once the first 2k + 1 integers are written, there is a cycle (k - 1 -- 2k - 1 -- 2k + 1).
    Thus, the answer is upper bounded by 2k + 1, and we only need to consider the cycles formed
    by the first 2k + 1 numbers.

    For every pair (a, b) such that there is an edge from a to b, we either have a = -b^2 mod k or
    b = -a^2 mod k. Let's consider the pairs (a, b) where a and b are between 1 and 2k + 1 inclusive.
    These can all be formed by considering each number a from 1 to 2k + 1 and finding -a^2 mod k to use for
    b. We now want to find the minimum possible value of the largest node in a cycle
    
    The edge set needs to be modified such that a > b for all (a, b) and then sorted in increasing order
    according to a. Then, add each edge in sequential to a dsu structure until there exists a pair (a, b)
    that cannot be added. Then, return that value for a as the answer.
*/

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