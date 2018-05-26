#include <bits/stdc++.h>

using namespace std;

class LittleSquares {

    int grundy[1030][1030];
    int n;

    inline int mex(vector<int> &grundys) {
        for (int i = 0; i < 22; i++) {
            if (!grundys[i]) return i;
        }
        return 22;
    }

    int solve(int top, int bottom, int n) {
        if (~grundy[top][bottom]) return grundy[top][bottom];
        vector<int> grundys(22);
        for (int i = 0; i < n; i++) {
            if (!(top & (1 << i) ) ) { //i'th square not filled
                grundys[ solve(top | (1 << i), bottom, n ) ] = 1;
                if (i < n - 1) {
                    if (!(bottom & (1 << i) ) && !(top & (1 << (i + 1)) ) && !(bottom & (1 << (1 + i)) ) ) {
                        grundys[ solve(top | ((1 << i) + (1 << (i + 1))), bottom | ((1 << i) + (1 << (i + 1))), n ) ] = 1;
                    }
                }
            }
        }
        grundy[top][bottom] = mex(grundys);
        return grundy[top][bottom];
    }

    int number(string s, int n) {
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '#') res |= (1<<i);
        }
        return res;
    }
    public: 
        string winner(vector<string> state) {
            memset(grundy, -1, sizeof(grundy));
            int n = state[0].size();
            int h = state.size();
            int g = 0;
            for (int i = 0; i + 2 <= h; i += 2) {
                int n1 = number(state[i], n);
                int n2 = number(state[i + 1], n);
                g ^= solve(n1, n2, n);
            }
            if (g == 0) return "second";
            else return "first";
        }

};