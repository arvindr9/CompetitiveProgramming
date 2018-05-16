/*
    Author: Arvind Ramaswami

    O(T log(maxn) logK) solution: If the floor of log_2(height of building) + 1, then there exists
    the value of the durability of the coconuts, can be found by doing binary search on the K coconuts.

    Otherwise, it can be shown that the maximum number that can be guaranteed by d drops and e eggs
    is sum_{i = 1}^e C(d, i), and using binary search, we can find the smallest value of d such
    that the expression is greater than or equal to N.

    When finding each binomial value, it is important to round to the nearest long long at each step.
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

typedef long long ll;
typedef long double ld;

ll lg (ll num) { //floor(log_2(n)) + 1
    return (63 - __builtin_clzll(num)) + 1;
}


int T;
ll N, K;

ll binom(ll drops) { //sum C(drops, i) from i = 1 to K
    ll res = 0;
    ld add = 1;
    for (int i = 1; i <= K; i++) {
        if (drops - i + 1 <= 0) break;
        add = (ld)(add) / (ld)(i);
        add *= (ld)(drops - i + 1);
        if (add < (ld)0) {
            res = N; //accounting for overflows here (in the event of an overflow, the answer will always be greater than N).
            break;
        }
        add = llround(add);
        res += add;
        if (res < 0) {
            res = N + 1; //and here
            break;
        }
        if (res > N) {
            res = N + 1;
            break;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> N >> K;
        if (K >= lg(N)) {
            cout << lg(N) << "\n";
            continue;
        } //K will be at most 60
        ll drops = 0;
        for (int j = 59; j >= 0; j--) { 
            if (drops < N && binom(drops + (1LL << j)) < N) {
                drops += (1LL << j);
            }
        }
        drops++;
        cout << drops << "\n";
    }
}