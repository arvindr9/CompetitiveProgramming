/*
    -Author: Arvind Ramaswami

    Solution: After each step i, we must keep track of the longest decreasing suffix.
    All elements of this suffix are distinct, and there are at most k of them (and k is at most 11), so
    the suffix can be represented as a bitmask. If there is
    already a number of the form 2^k, then 2^{the number of remaining zeros} can be added to the solution.

    Otherwise, the next square can be appended to the suffix (and possibly condensed)
    if and only if it divides the bitmask (in this case,
    adding the square can be considered as adding the numerical value of the bitmask and square). If
    it doesn't divide the bitmask, the new bitmask will be the binary representation of the square.

    Hitting a zero gives two options for the next dp state: adding a 2 or a 4, while hitting a 2 or 4 gives only one option.

    Complexity: O(n * 2^k) 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2005;
const int maxk = 11;
const int mod = 1000000007;

int dp[maxn][1<<maxk + 1]; //number of ways to choose a valid sequence given that i steps have occurred and the decreasing subsequence has a bitmask j
int arr[maxn];
int numZeros[maxn];

int n, k;

inline int solve(int i, int mask) {
    if (dp[i][mask]) {
        return dp[i][mask];
    }
    if (mask == (1 << k)) {
        return (numZeros[i] % mod);
    }
    if (i == n) {
        return 0;
    }
    int res = 0;
    if (arr[i + 1] == 0) {
        res += solve(i + 1, mask + 2);
        res %= mod;
        if (mask % 4 == 0) {
            res += solve(i + 1, mask + 4);
        } else {
            res += solve(i + 1, 4);
        }
    }
    else {
        if (mask % arr[i + 1] == 0) {
            res += solve(i + 1, mask + arr[i + 1]);
        } else {
            res += solve(i + 1, arr[i + 1]);
        }
    }
    res %= mod;
    dp[i][mask] = res;
    return res;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    numZeros[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        numZeros[i] = numZeros[i+1];
        if (arr[i + 1] == 0) {
            numZeros[i] <<= 1;
        }
    }
    int ans = solve(0, 0);
    cout << ans << "\n";

}