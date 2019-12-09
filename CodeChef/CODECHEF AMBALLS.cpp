/*

    Author: Arvind Ramaswami

    Given a sequence of balls, define a space between two balls to be "bad" if the twp balls are of the
    same color. Let dp[i][j] be the number of ways to construct such a sequence using the first
    i colors. 

    We want to find dp[N][0]
    
    From dp[i - 1][b], we can add k disjoint blocks of the
    i^{th} color (binom(c[i] - 1, k - 1) to construct these blocks)
    place m of these blocks in bad spaces (binom(b, m)), and
    place (k - m) of these blocks in good spaces (binom(total good spaces, k - m)).
    This gives a contribution to dp[i][(b - m) + (c[i] - k)], and we can look over
    the number of blocks and the number of placements in bad spaces to compute the other dp values.
*/


#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


const ll mod = 1e9 + 7;

const int maxn = 205;
int c[maxn];
int sm[maxn];
ll dp[maxn][maxn]; // dp[considered][num bad]
int T, N;

ll prod(ll a, ll b) {
    return (((a * b) % mod) + mod) % mod;
}

// ll modpow(ll a, ll pw) {
//     if (pw == 0) return 1;
//     if (pw % 2 == 1) {
//         return prod(modpow(a, pw - 1), a);
//     }
//     return prod(modpow(a, pw / 2), modpow(a, pw / 2));
// }

ll add(ll a, ll b) {
    return (((a + b) % mod) + mod) % mod;
}

ll binom_memo[maxn][maxn];

ll binom(ll a, ll b) {
    if (b > a || b < 0) return 0;
    if (~binom_memo[a][b]) return binom_memo[a][b];
    if (b == 0 || b == a) return binom_memo[a][b] = 1;
    return binom_memo[a][b] = add(binom(a - 1, b - 1), binom(a - 1, b));

}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) {
            binom_memo[i][j] = -1;
        }
    }
    for (int t = 1; t <= T; t++) {
        cin >> N;
        for (int i = 1; i <= N; i++) {
            cin >> c[i];
            sm[i] = sm[i - 1] + c[i];
        }
        dp[1][c[1] - 1] = 1;
        for (int i = 2; i <= N; i++) {
            int num_gaps = sm[i - 1] + 1;
            for (int b = 0; b <= num_gaps; b++) {
                if (dp[i - 1][b] > 0) {
                    int g = num_gaps - b;
                    for (int blocks = 0; blocks <= c[i]; blocks++) {
                        for (int bad = 0; bad <= min(blocks, b); bad++) {
                            int good = blocks - bad;
                            if (bad + good <= num_gaps) {
                                int new_bad = (b - bad) + (c[i] - blocks);
                                ll plus = prod(prod(dp[i - 1][b], binom(b, bad)), prod(binom(g, good), binom(c[i] - 1, blocks - 1)));
                                dp[i][new_bad]  = add(dp[i][new_bad], plus);
                            }
                        }
                    }
                }
            }
        }

        cout << dp[N][0] << "\n";
        for (int i = 0; i < maxn; i++) {
            for (int j = 0; j < maxn; j++) {
                dp[i][j] = 0;
            }
        }
    }

}
