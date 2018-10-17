/*
    Author: Arvind Ramaswami
    Solution: We use grundy numbers. Adding a triomino splits the board into two subgames (where
    some subgames could potentially have no space for remaining tiles), for which the grundy numbers can
    be found recursively with dp (the dp array is explained below). The final answer is the mex of the
    xors of the grundy values two subgames over all possible splits. 
*/

#include <bits/stdc++.h>

using namespace std;

int dp[1000][4]; //grundy values over rectangle lengths and cases

//dp[i][0]: rectangle of length i
//''[1]: rectangle of length i + one extra space
//''[2]: '' + 2 extra spaces (same side)
//''[3]: '' + 2 extra spaces (opposite)

int mex(set<int> &candidates) {
    for (int i = 0; i < 6000; i++) {
        if (!candidates.count(i)) return i;
    }
    return 1000;
}

void print(set<int> v) {
    stringstream ss;
    for (int i: v) {
        ss << i << " hi ";
    }
    cout << ss.str() << "\n";
}

int solve(int length, int cse) {
    if (~dp[length][cse]) return dp[length][cse];
    set<int> candidates;
    if (cse == 1) candidates.insert(solve(length - 1, 0)); //putting a triomino into an extra space
    if (cse == 2) candidates.insert(solve(length - 1, 1));
    if (cse == 3) candidates.insert(solve(length - 1, 1));
    for (int left = 0; left + 2 <= length; left++) {
        if (cse == 0) {
            candidates.insert(solve(left, 0) ^ solve(length - left - 2, 1));
            candidates.insert(solve(left, 1) ^ solve(length - left - 2, 0));
        }
        if (cse == 1) { //WLOG extra space is on the left side
            candidates.insert(solve(left, 2) ^ solve(length - left - 2, 0));
            candidates.insert(solve(left, 3) ^ solve(length - left - 2, 0));
            candidates.insert(solve(left, 1) ^ solve(length - left - 2, 1));
        }
        if (cse == 2) {
            candidates.insert(solve(left, 2) ^ solve(length - left - 2, 1));
            candidates.insert(solve(left, 3) ^ solve(length - left - 2, 1));
            candidates.insert(solve(left, 1) ^ solve(length - left - 2, 2));
            candidates.insert(solve(left, 1) ^ solve(length - left - 2, 3));
        }
        if (cse == 3) {
            candidates.insert(solve(left, 2) ^ solve(length - left - 2, 1));
            candidates.insert(solve(left, 3) ^ solve(length - left - 2, 1));
            candidates.insert(solve(left, 1) ^ solve(length - left - 2, 2));
            candidates.insert(solve(left, 1) ^ solve(length - left - 2, 3));
        }
    }
    return dp[length][cse] = mex(candidates);

}

int main() {
    
    // freopen("phi.in", "r", stdin);
    // freopen("phi.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    memset(dp, -1, sizeof(dp));
    dp[0][0] = dp[0][1] = dp[0][2] = dp[0][3] = dp[1][0] = 0; //losing states
    for (int i = 1; i <= T; i++) {
        int N; cin >> N;
        int g = solve(N, 0);
        if (g) cout << "X\n";
        else cout << "Y\n";
    }
}