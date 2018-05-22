/*
    -Arvind Ramaswami

    -Solution: For each correct answer on a leaked question of a difficulty d, keep track
    of the number of incorrect answers on unleaked question of difficulty less than d,
    which will be contributed to the final sum.

    This can be done by having an array to keep track of the number of unleaked of difficulty d
    that are answered incorrectly and converting it to a prefix sum which
    gives the number of unleaked questions of difficulty at most d that are incorrect.
*/

#include <bits/stdc++.h>

using namespace std;


int incorrect[11]; //incorrect and not leaked
int sm[11];
int T;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int i = 1; i <= T; i++) {
        memset(incorrect, 0, sizeof(incorrect));
        memset(sm, 0, sizeof(sm));
        int Q;
        cin >> Q;
        queue<int> correct;
        for (int i = 1; i <= Q; i++) {
            int d, s;
            char r;
            cin >> d >> s >> r;
            if (s == 1 && r == 'c') {
                correct.push(d);
            }
            if (s == 0 && r == 'i') {
                incorrect[d]++;
            }
        }
        for (int i = 1; i < 11; i++) {
            sm[i] = sm[i-1] + incorrect[i];
        }
        ll ans = 0;
        while (!correct.empty()) {
            int curr = correct.front(); correct.pop();
            ans += sm[curr - 1];
        }
        cout << ans << "\n";
    }
}