/*
    -Author: Arvind Ramaswami

    -Solution: The number of bad moves is independent of when left/right moves are made compared to up/down moves,
    so we can consider the left/right and up/down moves separately. 

    The solution uses ternary search to find the minimal misses due to left/right moves and to find the minimal misses
    due to up/down moves.

    Compexity: O(T(N log R + N log C)) (N is the number of characters in each test case).
*/

#include <bits/stdc++.h>

using namespace std;


inline int misses(vector<int> instructions, int y, int h) {
    int ans = 0;
    for (int i: instructions) {
        if (i == 1) {
            if (y == h) ans++;
            else y++;
        } else if (i == -1) {
            if (y == 0) ans++;
            else y--;
        }
    }
    return ans;
}

inline int findOpt(vector<int> &instructions, int height) {
    int h = height - 1;
    int ans = 300000;
    int l = 0;
    int r = h;

    while (l <= r) {
        int m1 = (2 * l + r) / 3;
        int m2 = (l + 2 * r) / 3;
        int ans1 = misses(instructions, m1, h);
        int ans2 = misses(instructions, m2, h);
        if (ans1 >= ans2) {
            l = m1 + 1;
        } else { //ans1 < ans2
            r = m2 - 1;
        }
        ans = min(ans, min(ans1, ans2));
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