/*
    -Author: Arvind Ramaswami

    For each divisor d of n (in increasing order since we want to minimize the number of piles in the first step), check if:

    1. The pile can be split into d piles.
    2. If (1) applies, add the grundy number of the d piles to a set.
    3. If the grundy number of the d piles is zero, set the number of piles to be the answer.
    4. Find the grundy number of the pile over all possible splits.

    If the grundy number of the original configuration is positive, then return the number of piles that was stored in step 3.
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 100050;
int n;

int grundy[maxn];
int piles[maxn]; //stores the answer for each n.
vector<int> fac[2 * maxn];

void prepareFac() {
    for (int i = 2; i <= 2 * n; i++) {
        for (int j = i; j <= 2 * n; j+=i) {
            fac[j].push_back(i);
        }
    }
}

inline int mex(set<int> s) {
    for (int i = 0; i <= 100000; i++) {
        if (!s.count(i)) return i;
    }
    return 100001;
}

int grund(int state) {
    if (~grundy[state]) return grundy[state];
    set<int> s;
    for (int factor: fac[2 * state]) {
        if (factor >= state) break;
        int g = 0;
        if (factor % 2 == 0) {
            if (state % factor != 0) {
                int two_mid = state * 2 / factor;
                int stretch = factor / 2;
                if (two_mid / 2 - stretch + 1 >= 1) {
                    for (int i = two_mid / 2 - stretch + 1; i <= two_mid / 2 + stretch; i++) {
                        g ^= grund(i);
                    }
                } else break;
            } else continue;
        } else {
            if (state % factor == 0) {
                int mid = state / factor;
                int stretch = factor / 2;
                if (mid - stretch >= 1) {
                    for (int i = mid - stretch; i <= mid + stretch; i++) {
                        g ^= grund(i);
                    }
                } else break;
            }
        }
        s.insert(g);
        if (g == 0 && piles[state] == -1) {
            piles[state] = factor;
        }
    }
    int m = mex(s);
    return grundy[state] = m;
}

int main() {
    cin >> n;
    prepareFac();
    memset(grundy, -1, sizeof(grundy));
    memset(piles, -1, sizeof(piles));
    if (grund(n)) cout << piles[n] << "\n";
    else cout << "-1\n";
}