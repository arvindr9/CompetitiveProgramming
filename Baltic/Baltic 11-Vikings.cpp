#include <bits/stdc++.h>


/*
Link to problems from the contest: https://cses.fi/100/list/

Author: Arvind Ramaswami

Solution: Let dist_v[i][j] be the minimum amount of time it can take for the
viking to reach (i, j) (can be computed by a bfs).

Let realdist_v[i][j] be the minimum amount of time it can take for the viking
to be on the same row / column as (i, j) and not blocked by an island
(can be found in O(n^3) time using the information from dist_v)

Now, do a bfs from 'Y' to create dist_y, where each spot (i, j) on the grid is visited
if dist_y[i][j] > realdist_v[i][j].

The result will be YES if (i, j) is reachable by the final bfs.

*/

using namespace std;

int n, m;
const int maxn = 702;
typedef pair<int, int> pi;

char arr[maxn][maxn];
int visited_v[maxn][maxn];
int visited_y[maxn][maxn];
int dist_v[maxn][maxn];
int realdist_v[maxn][maxn];
int dist_y[maxn][maxn];
const int INF = 5000;
pi viking;
pi you;
pi treasure;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // freopen("a.in", "r", stdin);
    // freopen("a.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dist_v[i][j] = dist_y[i][j] = realdist_v[i][j] = INF;
            cin >> arr[i][j];
            if (arr[i][j] == 'Y') {
                you = make_pair(i, j);
            } else if (arr[i][j] == 'V') {
                viking = make_pair(i, j);
            } else if (arr[i][j] == 'T') {
                treasure = make_pair(i, j);
            }
        }
    }

    queue<pair<int, pi>> q;
    q.push(make_pair(0, viking));

    while(!q.empty()) {
        pair<int, pi> spot = q.front();
        q.pop();
        pi ij = spot.second;
        int i = ij.first; int j = ij.second;
        int d = spot.first;
        if (!visited_v[i][j]) {
            visited_v[i][j] = 1;
            if (arr[i][j] == 'I') {
                continue;
            }
            dist_v[i][j] = d;
            for (pi p: {make_pair(i - 1, j), make_pair(i + 1, j), make_pair(i, j - 1), make_pair(i, j + 1)}) {
                int x = p.first;
                int y = p.second;
                if (x > 0 && x <= n && y > 0 && y <= m) {
                    if (!visited_v[x][y]) {
                        q.push(make_pair(d + 1, make_pair(x, y)));
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (dist_v[i][j] < INF) {
                realdist_v[i][j] = dist_v[i][j];
                for (int k = i - 1; k > 0 && arr[k][j] != 'I'; k--) {
                    realdist_v[i][j] = min(realdist_v[i][j], dist_v[k][j]);
                }
                for (int k = i + 1; k <= n && arr[k][j] != 'I'; k++) {
                    realdist_v[i][j] = min(realdist_v[i][j], dist_v[k][j]);
                }
                for (int k = j - 1; k > 0 && arr[i][k] != 'I'; k--) {
                    realdist_v[i][j] = min(realdist_v[i][j], dist_v[i][k]);
                }
                for (int k = j + 1; k <= m && arr[i][k] != 'I'; k++) {
                    realdist_v[i][j] = min(realdist_v[i][j], dist_v[i][k]);
                }
                realdist_v[i][j] = max(1, realdist_v[i][j]);
            }
        }
    }

    q.push({0, you});
    while (!q.empty()) {
        pair<int, pi> spot = q.front();
        q.pop();
        pi ij = spot.second;
        int i = ij.first; int j = ij.second;
        int d = spot.first;
        if (arr[i][j] == 'I') {
            continue;
        }
        // cout << "i, j: " << i << ", " << j << "\n";
        // cout << "d: " << d << "\n";
        // cout << "realdist: " << realdist_v[i][j] << "\n";
        if (d > 0) {
            if (visited_y[i][j] || realdist_v[i][j] <= d) {
                continue;
            }
        }
        visited_y[i][j] = 1;
        dist_y[i][j] = d;
        for (pi p: {make_pair(i - 1, j), make_pair(i + 1, j), make_pair(i, j - 1), make_pair(i, j + 1)}) {
            int x = p.first;
            int y = p.second;
            if (x > 0 && x <= n && y > 0 && y <= m) {
                if (!visited_y[x][y] && realdist_v[x][y] > d + 1) {
                    q.push(make_pair(d + 1, make_pair(x, y)));
                }
            }
        }
    }

    // cout << "realdist: \n";

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         cout << realdist_v[i][j] << " ";
    //     }
    //     cout << "\n";
    // }


    // cout << "you: \n";

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         cout << dist_y[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    int i = treasure.first; int j = treasure.second;
    // cout << "viking dist: " << dist_v[i][j] << "\n";
    // cout << "viking realdist: " << realdist_v[i][j] << "\n";
    // cout << "you dist: " << dist_y[i][j] << "\n";


    if (visited_y[i][j] && dist_y[i][j] < realdist_v[i][j]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    

}
