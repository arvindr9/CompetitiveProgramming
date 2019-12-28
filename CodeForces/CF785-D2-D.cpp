/*
    Author: Arvind Ramaswami

    Solution: For each index i of the sequence with an opening bracket
    '(', we want to compute the number of ways such to construct an
    RSBS such that its final opening bracket is at index i. The desired
    answer will be the sum of these values over all candidate final
    opening brackets.

    Consider all the opening brackets up to index i, and all the closing
    brackets after index i. Let there be p open brackets and q closed
    brackets.
    We want to include the last opening bracket
    and choose a subset of the remaining such that the total number of
    opening brackets is equal to the total number of closing brackets.
    This is equivalent to labeling the brackets with p 0's and q 1's
    such that the opening brackets labeled with 1 are included,
    and the closing brackets with 0's are included, with the extra
    condition that the final opening bracket must be labeled
    with a 1 (since it must be included). The desired value is thus
    C(p + q - 1, p). Summing over all the open brackets gives the answer.


    */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int maxn = 2e5 + 5;
const int mod = 1e9 + 7;

ll prod(ll a, ll b) {
    return (((a * b) % mod) + mod) % mod; 
}

ll modpow(ll a, ll pw) {
    if (pw == 0) return 1;
    if (pw == 1) return (a % mod);
    if (pw % 2 == 0) return prod(modpow(a, pw / 2), modpow(a, pw / 2));
    return prod(modpow(a, pw - 1), a);
}

ll inv(ll a) {
    return modpow(a, mod - 2);
}



string seq;

ll fac[maxn];
int num_l[maxn];
int num_r[maxn];


ll binom(ll a, ll b) {
    ll den = inv(fac[b]);
    den = prod(den, inv(fac[a - b]));
    ll num = fac[a];
    return prod(num, den);
}

ll add(ll a, ll b) {
    return (((a + b) % mod) + mod) % mod;
}

void computeFac(ll n) {
    fac[0] = 1;
    for (ll i = 1; i < n; i++) {
        fac[i] = prod(fac[i - 1], i);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> seq;
    computeFac(maxn);
    int l = seq.size();
    if (seq[0] == '(') num_l[0] = 1;

    for (int i = 1; i < l; i++) {
        num_l[i] = num_l[i - 1];
        if (seq[i] == '(') {
            num_l[i]++;
        }
    }

    if (seq[l - 1] == ')') num_r[l - 1] = 1;
    for (int i = l - 2; i >= 0; i--) {
        num_r[i] = num_r[i + 1];
        if (seq[i] == ')') {
            num_r[i]++;
        }
    }
    ll ans = 0;

    for (int i = 0; i <= l; i++) {
        if (seq[i] == '(') {
            int lef = num_l[i];
            int rig = num_r[i];
            if (rig == 1) {
                ans++;
            } else if (rig > 1) {
                ans = add(ans, binom(lef + rig - 1, lef));
                // add some binomial coefficient to the answer
            }
        }
    }

    cout << ans << "\n";
}