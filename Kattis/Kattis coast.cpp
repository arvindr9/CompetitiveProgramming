/*
    Author: Arvind Ramaswami

    There are two things that contribute to the length of the coast: The number of land blocks in the
    edge (easily computed), and the number of land blocks next to each sea block (can be found
    using a floodfill dfs starting at each sea block that is in the edge of the grid).
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1050;

int grid[maxn][maxn];
int sea[maxn][maxn];
int visited[maxn][maxn];
int ans = 0;

int n, m;

void dfs(int i, int j) {
    if (i < 1 || j < 1 || i > n || j > m || visited[i][j] || grid[i][j]) {
        return;
    }
    visited[i][j] = 1;
    if (grid[i + 1][j]) {
        ans++;
    }
    if (grid[i][j + 1]) {
        ans++;
    }
    if (grid[i - 1][j]) {
        ans++;
    }
    if (grid[i][j - 1]) {
        ans++;
    }
    dfs(i + 1, j);
    dfs(i, j + 1);
    dfs(i - 1, j);
    dfs(i, j - 1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        for (int j = 1; j <= m; j++) {
            grid[i][j] = (s[j - 1] == '1' ? 1 : 0);
        }
    }
    for (int i = 1; i <= m; i++) {
        dfs(1, i);
        dfs(n, i);
    }
    for (int i = 1; i <= n; i++) {
        dfs(i, 1);
        dfs(i, m);
    }

    for (int i = 1; i <= m; i++) {
        if (grid[1][i]) ans++;
        if (grid[n][i]) ans++;
    }
    
    for (int i = 1; i <= n; i++) {
        if (grid[i][1]) ans++;
        if (grid[i][m]) ans++;
    }
    cout << ans << "\n";
}