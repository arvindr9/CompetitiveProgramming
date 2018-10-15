/*
    Author: Arvind Ramaswmi

    Solution: First, the candidates for the prime factors of n are generated (A prime p
    is a candidate if p - 1 divides phi(n)). Then, dfs is used to consider all possible
    prime factorizations of n such that phi(n) is equal to the input, and for each valid prime factorization,
    the answer is updated by taking min(answer, n).

    In the function dfs(out, in, i_factor), "out" is an accumulator for the value of
    n, and "in" is the original value for phi(n) that is input, which ideally should
    reach 1 or a prime number minus one. If in equals 1, the answer is out, and if in
    is p - 1 for a prime p, the answer equals in * p as long as p was not used for the
    accumulation of out.

*/

#include <bits/stdc++.h>

using namespace std;

const int maxp = 10e4;
int primes[maxp]; //list of primes
int composite[maxp + 1]; //composite[i] = 1 if i is composite
int fac[maxp]; //candidate prime divisors of n
int facdiv[maxp]; //tells if the i'th candidate factor divides n
int ans = INT_MAX;
int np = 0;
int nf = 0;


void processPrimes() {
    for (int i = 2; i <= maxp; i++) {
        if (composite[i]) continue;
        primes[np++] = i;
        for (int j = 2 * i; j <= maxp; j += i) composite[j] = 1;
    }
}

void processFac(int n) {
    for (int i = 0; i < np; i++) {
        if (n % (primes[i] - 1) == 0) {
            fac[nf++] = primes[i];
        }
    }
}

bool prime(int n) {
    for (int i = 2; i * i <= n; i++) if (n % i == 0) return false;
    return true;
}

void dfs(int out, int in, int i_factor) {
    if (i_factor == nf) {
        if (in == 1) {ans = min(ans, out); return;}
        if (!prime(in + 1)) return;
        for (int i = 0; i < nf; i++) {
            if (facdiv[i] && (in + 1) % fac[i] == 0) return;
        }
        ans = min(ans, out * (in + 1)); //in + 1 is a prime larger than maxp
        return;
    }
    int factor = fac[i_factor];
    dfs(out, in, i_factor + 1);
    if (in % (factor - 1) == 0) {
        facdiv[i_factor] = 1;
        in /= (factor - 1);
        out *= factor;
        while (true) {
            dfs(out, in, i_factor + 1);
            if (in % factor != 0) return; 
            in /= factor;
            out *= factor;
        }
    }
    facdiv[i_factor] = 0;


}

int solve(int n) {
    processFac(n);
    dfs(1, n, 0);
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    processPrimes();
    int i = 0;
    while (cin >> n) {
        i++;
        if (n == 0) return 0;
        cout << "Case " << i << ": " << n << " " << solve(n) << "\n";
        memset(fac, 0, sizeof fac);
        memset(facdiv, 0, sizeof facdiv);
        ans = INT_MAX;
        nf = 0;
    }
}