#include <bits/stdc++.h>

/*
    Author: Arvind Ramaswami

    Solution based off https://github.com/thecodingwizard/competitive-programming/blob/master/POI/POI04-Passage.cpp

    dp[mask]: The minimum remaining time required such that the current
    processed groups are represented by the bits in mask.

    For the transition state, we determine a subset of the
    unprocessed people to add as the next group. Details are in the comments.
*/

using namespace std;

const int maxn = 17;
int dp[(1 << maxn)];
int w, n, tim[maxn], wt[maxn];
const int INF = INT_MAX;

int solve(int mask) {
    if (~dp[mask]) return dp[mask];
    int ans = INF;
    vector<int> opt; // unprocessed people
    for (int i = 0; i < n; i++) {
        if (!(mask & (1 << i))) {
            opt.push_back(i);
        }
    }

    if (opt.size() == 0) ans = 0;

    // The last person in opt will always be placed in the next group (for speedup purposes)

    for(int i = 0; i < (1 << (opt.size() - 1)); i++) {
        int new_mask = mask;
        int total_time = 0;
        int total_weight = 0;
        for (int j = 0; j < opt.size() - 1; j++) {
            if ((1 << j) & i) {
                total_time = max(tim[opt[j]], total_time);
                total_weight += wt[opt[j]];
                new_mask |= (1 << opt[j]);
            }
        }

        int last_opt = opt[opt.size() - 1];
        total_time = max(total_time, tim[last_opt]);
        total_weight += wt[last_opt];
        new_mask |= (1 << last_opt);

        if (total_weight > w) continue;
        ans = min(ans, total_time + solve(new_mask));
    }

    return dp[mask] = ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> w >> n;
    for (int i = 0; i < (1 << maxn); i++) {
        dp[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        cin >> tim[i] >> wt[i];
    }

    cout << solve(0) << "\n";


}
