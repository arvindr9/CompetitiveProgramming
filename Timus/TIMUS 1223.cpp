/*
    Author: Arvind Ramaswami

    Solution: O(N log N) Let f(d, n) be the maximum height such that
    at most d drops and n eggs will always work. It can be shown
    that f(d, n) = sum_{i=1}^{n} C(d, i).
    
    We want to find the minimum
    d such that f(d, n) is greater than or equal to the height
    of the building, which can be done through binary search.
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 1002;

typedef long long ll;

int eggs, height;

ll maxH(int drops, int eggs) {
    long double ans = 0;
    long double add = 1;
    for (int i = 1; i <= eggs; i++) {
        add *= (long double)(drops - i + 1);
        add /= (long double)(i);
        if (add < 0.) {
            add = 0;
        }
        ans += add;
        if (ans > height) break;
    }
    return (ll)ans;
}

int solve() {
    int drops = 0;
    for (int i = 10; i >= 0; i--) {
        if (maxH(drops + (1 << i), eggs) < height) {
            drops += (1 << i);
        }
    }
    drops++;
    return drops;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(cin >> eggs >> height) {
        if (eggs == 0 && height == 0) {
            break;
        }
        cout << solve() << "\n";
    }
}