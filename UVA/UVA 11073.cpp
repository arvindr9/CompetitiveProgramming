/*
    Author: Arvind Ramaswami

    Solution: Generate a list of primes, and see which ones are possible candidates for
    n such that phi(n) is equal to the input(primes p such that p - 1 is divisible by the input).
    
    Then, check all powers of primes through a dfs, and see if they satisfy that phi(n) = input.
    This can be done by having an accumulator "out" to construct a value of n given an input "in".

    For each prime p, "out" will be multiplied by p and "in" would be divided by p - 1 when considering
    the first power to include in n. Then, for the remaining powers, "out" will be multiplied by
    p and "in" will be divided by p.

    Our desired cases at the end state are: either "in" is 1, in which the result for n will be "out", or "in" will be p - 1
    for some prime that does not divide n, where the result will be (in + 1) * out. Append all such results
    to the answer.

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll maxp = 1e5;
ll composite[maxp];
ll primes[maxp];
ll fac[maxp]; //potential prime factors
ll consider[maxp]; //whether the ith factor is considered to create out.
ll np = 0;
ll nf = 0;

set<ll> ans;

void processPrimes() {
    for (ll i = 2; i < maxp; i++) {
        if (composite[i]) continue;
        primes[np++] = i; 
        for (ll j = 2 * i; j < maxp; j += i) {
            composite[j] = 1;}
    }
}

void processFac(ll n) {
    for (ll i_p = 0; i_p < np; i_p++) {
        if (n % (primes[i_p] - 1) == 0) fac[nf++] = primes[i_p];
    }
}

bool isPrime(ll n) {
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void printAns() {
    if (ans.empty()) cout << "No solution.\n";
    else {
        stringstream ss;
        ll l = ans.size();
        ll i = 0;
        for (ll num: ans) {
            ss << num;
            if (i < (l - 1)) {
                ss << " ";
            }
            i += 1;
        }
        cout << ss.str() << "\n";
    }
}

void dfs(ll out, ll in, ll i_fac) {
    if (i_fac == nf) {
        if (in == 1) {
            ans.insert(out);
            return;
        }
        if (!isPrime(in + 1)) return;
        for (ll i_f = 0; i_f < nf; i_f++) {
            if (consider[i_f] && fac[i_f] == in + 1) return;
        }
        ans.insert((in + 1) * out);
        return;
    }
    dfs(out, in, i_fac + 1);
    ll factor = fac[i_fac];
    if (in % (factor - 1) == 0) {
        consider[i_fac] = 1;
        in /= (factor - 1);
        out *= factor;
        while (true) {
            dfs(out, in, i_fac + 1);
            if (in % factor != 0) break;
            out *= factor;
            in /= factor;
        }
    }
    consider[i_fac] = 0;

}

void solve(ll n) {
    nf = 0;
    ans.clear();
    memset(fac, 0, sizeof fac);
    processFac(n);
    dfs(1, n, 0); //(out, in, i_fac)
    printAns();
}

int main() {
    // freopen("phi.in", "r", stdin);
    // freopen("phi.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    processPrimes();
    ll n;
    while (cin >> n) solve(n);
}