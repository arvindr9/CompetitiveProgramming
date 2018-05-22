/*
    -Author: Arvind Ramaswami

    Solution: Note that if the LCM of a set of numbers is equal to k, then each member of the set is divisible by k.
    The sum of the set is maximized if the set has all the divisors of k. Thus, we wish to find the sum of the divisors
    of each integer from 2 to N.

    First, we find all pairs (a, b) with a < b such that a * b <= N. Each pair contributes (a + b) to the total
    sum. Then, to account for the square numbers from 2 to N, we add all integers from max(2, floor(sqrt(n))) to floor(sqrt(n)) to the total
    value, resulting in the sum of divisors of all numbers from 2 to N.
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N;

ll sqrt(ll num) { // O(log(sqrt(n))) implementation to find floor of sqrt
    int LN = 25;
    ll res = 0;
    for (int i = LN; i >= 0; i--) {
        ll base = res + (1 << i);
        if (base * base <= num){
            res += (1 << i);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> N) {
        if (N == 0) break;
        ll res = 0;
        ll largest = sqrt(N);
        for (int i = 1; i <= largest; i++) { //find pairs (a, b), a < b s.t. a * b = k for some k <= n
            ll j_lo = i + 1;
            ll j_hi = N / i;
            if (j_hi >= j_lo) {
                ll num_terms = j_hi - j_lo + 1;
                res += num_terms * (2 * i + (j_lo + j_hi)) / 2;
            }
        }
        for (int i = 2; i <= largest; i++) { //accounts for cases with a * a = k for some k <= n
            res += i;
        }
        cout << res << "\n";
    }
}