/*
    -Author: Arvind Ramaswami

    Solution: Let E[mask] be the maximum value that can be gained given that all the bits in mask
    (until the n^{th} bit) are contained in the bag if they are 0. Then, we can recursively find
    E[mask] to be max_i (v_i + P(item a_1 is devoured) * E[mask with a_1th and ith bit included] + P(a_2 is devoured)
    * E[mask with a_2th and ith bit included] + ... + P(no items are devoured) * E[mask with ith bit included]) )
    where the a_ith and ith bits are 0 in the original mask (since those two items are in the bag).

    Computing E[0] gives the desired result.
*/

#include <bits/stdc++.h>

using namespace std;

class BagOfDevouring {

    double E[(1<<15)];

    double solve(int mask, vector<int> values, vector<int> weights, int n) {
        if (E[mask] >= 0) return E[mask];
        if (mask == (1<<n) - 1) return E[mask] = 0;
        double mx = 0;
        double sumW = 0;
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) == 0) {
                sumW += weights[i];
            }
        }
        for (int i = 0; i < n; i++) {
            double res = 0;
            if ((mask & (1 << i)) == 0) res += values[i];
            else continue;
            for (int j = 0; j < n; j++) {
                if (j != i && (mask & (1 << j)) == 0) res += (double)weights[j]/(sumW - (double)weights[i] + 100.) * solve(mask | ((1 << i) + (1 << j)), values, weights, n);
            }
            res += 100./(sumW - (double)weights[i] + 100.) * solve(mask | (1 << i), values, weights, n); //if nothing is devoured
            mx = max(mx, res);
        }
        return E[mask] = mx;

    }

    public:
        double expectedYield(vector<int> values, vector<int> weights) {
            memset(E, -1, sizeof(E));
            int n = values.size();
            return solve(0, values, weights, n);
        }

};