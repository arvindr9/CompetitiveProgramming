#include <bits/stdc++.h>

using namespace std;

int dp[1003][256][130];
int nxt[1003][9][130]; //next[index][elt][k] = index of k_th occurrence of elt after index
int arr[1003];
map<int, vector<int>> indices;

int n;

void constructNext() {
    for (int i = 0; i <= n; i++) {
        map<int, int> num_to_freq;
        for (int j = i + 1; j <= n; j++) {
            num_to_freq[arr[j]]++;
            if (num_to_freq[j] < 130) nxt[i][arr[j]][num_to_freq[arr[j]]] = j;
        }
        for (int j = 1; j <= 8; j++) {
            nxt[i][j][0] = i;
        }
    }
    
}



int solve(int index, int mask, int length) {
    if (index == -1) {
        return -1;
    }
    if (mask == ((1 << 8) - 1)) {
        dp[index][mask][length] = 0;
        return 0;
    }
    if (~dp[index][mask][length]) return dp[index][mask][length];
    int res = -1;
    for (int i = 1; i <= 8; i++) {
        if (!(mask & (1 << (i - 1)))) {
            if (~solve(nxt[index][i][length], mask + (1 << (i - 1)), length))
                res = max(res, length + solve(nxt[index][i][length], mask | (1 << (i - 1)), length));
            if (~solve(nxt[index][i][length + 1], mask + (1 << (i - 1)), length)) 
                res = max(res, length + 1 + solve(nxt[index][i][length + 1], mask | (1 << (i - 1)), length));
        }
    }
    dp[index][mask][length] = res;
    return res;
}

int main() {
    // freopen("E.in", "r", stdin);
    // freopen("E.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    memset(dp, -1, sizeof(dp));
    memset(nxt, -1, sizeof(nxt));
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    constructNext();
    int ans = 0;
    int maxLen = n / 8;
    for (int i = 0; i <= maxLen; i++) {
        ans = max(ans, solve(0, 0, i));
    }

    cout << ans << "\n";
}