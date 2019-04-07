/*
    Author: Arvind Ramaswami

    The input size is small, so this can be solved with bitmask dp.

    Let dp[mask][k] be the probability that the fish represented by
    mask are still alive after k timesteps.
    
    We have that if a set S of fish is
    alive after k timesteps, then one of those fish had eaten some other fish f_i
    during the kth timestep. Given a group of fish S U f_i, the probability that
    another fish eats f_i can be computed. Thus, dp[mask][k] is the sum over
    all dp[mask union another fish f_i][k - 1] * (the probability that f_i is eaten).
    
    Our desired probabilities are dp[0][n - 1], dp[1 << 1][n - 1],
    ... dp[1 << (n - 1)][n - 1].
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int maxn = 18;
const ld eps = 1e-4;

ld arr[maxn][maxn];
ld dp[(1 << maxn)][maxn]; //probability of mask after j steps
ld sm[(1 << maxn)][maxn];

int n;


ld solve(int mask, int steps) {
    if (abs(-1 - dp[mask][steps]) > eps) return dp[mask][steps];
    ld ans = 0;
    for (int i = 0; i < n; i++) {
        if (!(mask & (1 << i))) { //ith element is a zero
            ld num_terms = __builtin_popcount(mask);
            ld factor = sm[mask][i] / ((num_terms + 1.)*(num_terms)/2.);
            ans += solve(mask | (1 << i), steps - 1) * factor;
        }
    }
    return dp[mask][steps] = ans;
}



double computeSum(int mask, int j) {
    double ans = 0;
    for (int i = 0; i < maxn; i++) {
        if ((1 << i) & mask) {
            ans += arr[i][j];
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("E.in", "r", stdin);
    // freopen("E.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    for (int mask = 0; mask < (1 << maxn); mask++) {
        for (int j = 0; j < maxn; j++) {
            sm[mask][j] = computeSum(mask, j);
            dp[mask][j] = -1.;
        }
    }
    dp[(1 << n) - 1][0] = 1;
    cout << fixed << setprecision(6);
    for (int i = 0; i < n - 1; i++) {
        cout << solve((1<<i), n - 1) << " ";
    }
    cout << solve(1<<(n - 1), n - 1) << "\n";
    

}