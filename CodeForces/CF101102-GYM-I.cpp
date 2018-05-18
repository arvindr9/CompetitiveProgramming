/*
    -Author: Arvind Ramaswami

    -Solution: The number of bad moves is independent of when left/right moves are made compared to up/down moves,
    so we can consider the left/right and up/down moves separately. This solution uses dynamic programming to
    memoize the number of future skipped steps will occur given that the robot is currently at a certain border and i steps
    have already been processed.
    
    Then, the algorithm iterates through all the possible start locations (R + C total since we are considering the horizontal
    and vertical moves separately) to find the minimal number of skipped steps that will occur.

    Compexity: O(T(R log R + C log C))
*/

#include <bits/stdc++.h>

using namespace std;

void print_map(map<int, set<int>> & m) {
    for (auto entry: m) {
        cout << entry.first << ":\n\t";
        for (int j: m[entry.first]) {
            cout << j << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void print(vector<int> &v) {
    for (int i: v) {
        cout << i << " ";
    }
    cout << "\n";
    cout << "\n";
}

void print2d(vector<vector<int>> &v) {
    for (vector<int> v2: v) {
        for (int i: v2) {
            cout << i << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int findOpt(vector<int> &instructions, int height) {
    // cout << "instructions:\n";
    // print(instructions);
    int num_ins = instructions.size(); //number of instructions
    if (num_ins == 0) {
        return 0;
    }
    height--; //the maximum allowed delta
    vector<int> num_up(num_ins + 1); //number of contiguous upward steps after completing i steps
    vector<int> num_down(num_ins + 1); //vice versa
    for (int i = num_ins - 1; i >= 0; i--) { //values are zero at index num_ins
        if (instructions[i] == 1) {
            num_up[i] = num_up[i + 1] + 1;
        } else {
            num_down[i] = num_down[i + 1] + 1;
        }
    }
    // cout << "num_up:\n";
    // print(num_up);
    // cout << "num_down:\n";
    // print(num_down);
    vector<int> delta(num_ins + 1); //delta from beginning after completing i steps
    unordered_map<int, set<int>> delta2indices; //set of indices for each delta
    delta2indices[0].insert(0);
    delta[1] = instructions[0];
    delta2indices[delta[1]].insert(1);
    for (int i = 2; i <= num_ins; i++) {
        delta[i] = delta[i - 1] + instructions[i - 1];
        delta2indices[delta[i]].insert(i);
    }
    // cout << "delta:\n";
    // print(delta);
    // cout << "delta2indices:\n";
    // print_map(delta2indices);
    vector<vector<int>> dp(2, vector<int>(num_ins + 1)); //number of remaining misses after completing j steps



    for (int i = num_ins - 1; i >= 0; i--) {
        int j_up;
        int j_straight;
        int j_down;
        auto it_up = delta2indices[height + delta[i]].upper_bound(i);
        auto it_straight = delta2indices[0 + delta[i]].upper_bound(i);
        auto it_down = delta2indices[-height + delta[i]].upper_bound(i);
        if (it_up == delta2indices[height + delta[i]].end()) {
            j_up = num_ins;
        } else {
            j_up = *(it_up);
        }
        if (it_straight == delta2indices[0 + delta[i]].end()) {
            j_straight = num_ins;
        } else {
            j_straight = *(it_straight);
        }
        if (it_down == delta2indices[-height + delta[i]].end()) {
            j_down = num_ins;
        } else {
            j_down = *(it_down);
        }


        if (num_down[i] > 0) {
            dp[0][i] = num_down[i] + dp[0][i + num_down[i]];
        } else {
            if (j_up > j_straight) { //they will never be equal since the robot can't be at the top and bottom at once.
                dp[0][i] = dp[0][j_straight];
            } else {
                dp[0][i] = dp[1][j_up];
            }
        }
        if (num_up[i] > 0) {
            dp[1][i] = num_up[i] + dp[1][i + num_up[i]];
        } else {
            if (j_down > j_straight) {
                dp[1][i] = dp[1][j_straight];
            } else {
                dp[1][i] = dp[0][j_down];
            }
        }

    }


    // cout << "dp:\n";
    // print2d(dp);

    int ans = 1000000;
    for (int i = 0; i <= height; i++) {
        if (!delta2indices.count(height - i + 1) || delta2indices[height - i + 1].empty()) {
            if (!delta2indices.count(-i - 1) || delta2indices[-i - 1].empty()) {
                ans = 0;
                break;
            }
        } else {
            int j_up;
            int j_down;
            auto it_up = delta2indices[height - i].begin();
            auto it_down = delta2indices[i].begin();
            if (it_up == delta2indices[height - i].end()) {
                j_up = num_ins;
            } else {
                j_up = *it_up;
            }
            if (it_down == delta2indices[i].end()) {
                j_down = num_ins;
            } else {
                j_down = *it_down;
            }
            if (j_up > j_down) { //the bottom will be hit
                ans = min(ans, num_down[j_down] + dp[0][j_down + num_down[j_down]]);
            } else { //they won't be equal
                ans = min(ans, num_down[j_up] + dp[1][j_up + num_up[j_up]]);
            }
        }
        
    }
    return ans;
}

int main()  {
    // freopen("I.in", "r", stdin);
    // freopen("I.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int R, C;
        cin >> R >> C;
        string s;
        cin >> s;
        vector<int> vertical;
        vector<int> horizontal;
        for (char c: s) {
            if (c == '<') {
                horizontal.push_back(-1);
            } else if (c == '>') {
                horizontal.push_back(1);
            } else if (c == '^') {
                vertical.push_back(1);
            } else if (c == 'v') {
                vertical.push_back(-1);
            }
        }
        int optHoriz = findOpt(horizontal, C);
        int optVert = findOpt(vertical, R);
        cout << (optHoriz + optVert) << "\n";
    }
}