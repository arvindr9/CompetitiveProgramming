/*
    -Author: Arvind Ramaswami

    Solution: We want to find a^a^...^a mod 10^n.
    If gcd(a, 10^n) = 1, and then we would have that a^(a^...^a) mod 10^n = a^(a^...^a mod phi(10^n)) mod 10^n,
    where phi is the Euler totient function, and the mod can be found recursively.
    However, a and 10^n are not necessarily coprime, so we must modify our mod function.

    We have a function newmod such that newmod(a, b) is a if a < b or otherwise b + a % b.
    
    Applying the above formula but replacing mod with newmod is sufficient. Here is why:
    
    We want to find a^x mod m.
    Consider a maximal power of an arbitrary prime factor p that divides m (p ^ n).
    We have a^x = a^newmod(x, phi(m)) mod p^n
    since if x < phi(m), the right side will equal a^x,
    and otherwise there are two cases:
    1) gcd(a, m) == 1: phi(p^n) | phi(m), so a^x = a^ (x mod phi(m)) mod p^n = a^(newmod(x, phi(m))) mod p^n
    2) gcd(a, m) > 1: both sides will be zero
    
    The prime p was chosen arbitrarily, so by the Chinese Remainder Theorem, we have the unique solution to the modular
    congruence a^x = a^newmod(x, phi(m)) mod m.

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll newmod(ll a, ll b) {
    return a <= b ? a : b + a % b;
}

ll poww(ll a, ll b, ll cap) {
    if (b == 0) return 1;
    if (b&1) return newmod(poww(a, b - 1, cap) * a, cap);
    return newmod(poww(a, b / 2, cap) * poww(a, b / 2, cap), cap);
}

ll len(ll curr, ll n) {
    ll l = 0;
    for (ll i = 1; i <= 100000000; i *= 10) {
        if (curr >= i - (i % 10)) l++;
        else break;
    }
    return n - l;
}

ll phi(ll num) {
    ll n2 = num;
    for (ll i = 2; i * i <= n2; i++) {
        bool prime = false;
        while (n2 % i == 0) {
            prime = true;
            n2 /= i;
        }
        if (prime) {
            num *= (i - 1);
            num /= i;
        }
    }
    return num;
}

ll solve2(ll base, ll iter, ll mod) {
    if (iter == 0) return 1;
    ll a2 = solve2(base, iter - 1, phi(mod));
    return poww(base, a2, mod);
}

ll solve(ll base, ll iter, ll n) {
    ll cap = 1;
    for (int i = 1; i <= n; i++) {
        cap *= 10;
    }
    return solve2(base, iter, 10000000LL) % cap;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("ic.in", "r", stdin);
    // freopen("ic.out", "w", stdout);
    ll b, i, n;
    while (cin >> b) {
        if (b == 0) break;
        cin >> i >> n;
        ll curr = solve(b, i, n);
        int l = len(curr, n);
        for (int i = 1; i <= l; i++) {
            cout << 0;
        }
        cout << curr << "\n";
    }
}
