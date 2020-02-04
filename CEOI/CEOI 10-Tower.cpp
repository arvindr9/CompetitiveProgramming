#include <bits/stdc++.h>

/*
Author: Arvind Ramaswami

Solution: To construct the tower, we can insert the blocks
in order from the largest block. Given a solution with the largest
k blocks, the (k + 1)th largest block can be inserted anywhere except for
the places where the block above it exceeds its size by > D.

Thus, this reduces to the following problem: given an element k in
a sorted array, find the number of elements j: j <= k + D
and index(j) > index(k). We want
to find the product over all k of (result(k) + 1).
The minimum {j: index(j) > index(k), j <= k + D} is monotonically
non-increasing, so one can keep track of it over all the inserts
in O(N) time.

*/

using namespace std;

typedef long long ll;

const ll mod = 1e9 + 9;

ll prod(ll a, ll b) {
    return (((a * b) % mod) + mod) % mod;
}

ll modpow(ll a, ll b) {
    if (b == 0) return 1;
    if (a % 2 == 1) {
        return prod(modpow(a, b - 1), a);
    }
    return prod(modpow(a, b / 2), modpow(a, b / 2));
}


ll ans = 1;

int N, D;
vector<int> blocks;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> D;

    for (int i = 1; i <= N; i++) {
        int u; cin >> u;
        blocks.push_back(u);
    }

    sort(blocks.begin(), blocks.end(), greater<>());

    int i = 1;
    int first_valid = 0;

    while (i < N) {
        while (first_valid < min(N - 1, i) && blocks[first_valid] > blocks[i] + D) {
            first_valid++;
        } 
        ans = prod(ans, (i - first_valid + 1));
        i++;
    }

    cout << ans << "\n";

    
}
