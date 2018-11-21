#include <bits/stdc++.h>

using namespace std;


class PerfectMemory {

    const long double eps = 1e-8;

    long double dp[3000][3000]; //dp[total][discovered] = expected number of moves from a certain number of discovered pieces from a total

    long double solve(int i, int j) {
        if (i == 0) return dp[i][j] = 0;
        if (dp[i][j] > -eps) return dp[i][j];
        long double ans = 0;
        if (i - 2 * j > 0) ans += (long double)(i - 2 * j) / (long double)((i - j) * (i - j - 1)) * (1 + solve(i - 2, j)); //match within undiscovered
        if (i - 2 * j > 2) ans += (long double)((i - 2 * j) * (i - 2 * j - 1) - (i - 2 * j)) / (long double)((i - j) * (i - j - 1)) * (1. + solve(i, j + 2)); //0 matches with discovered (and no match within undiscovered)
        if (i >= 2 * j && j >= 1) ans += (long double)j / (long double)(i - j) * (1 + solve(i - 2, j - 1)); //discovered reached 1st
        if (i > 2 * j && j >= 1) ans += (long double)((i - 2 * j) * j) / (long double)((i - j) * (i - j - 1)) * (2. + solve(i - 2, j)); //discovered reached 2nd
        return dp[i][j] = ans;
    }
    public:
        double getExpectation(int N, int M) {
            for (int i = 0; i < 3000; i++) {
                for (int j = 0; j < 3000; j++) {
                    dp[i][j] = -1;
                }
            }
            return solve(N * M, 0);
        }

    // int main() {
    //     ios::sync_with_stdio(0);
    //     cin.tie(0);
    //     // cout << solve(4, 2) << "\n";
    //     int N, M; cin >> N >> M;
    //     cout.precision(11);
    //     cout << fixed << getExpectation(N, M) << "\n";
    // }
};
