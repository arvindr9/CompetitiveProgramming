/*
    Author: Arvind Ramaswami

    Solution: For each test case, use 0/infinity knapsack to find the minimum price
    that is needed to buy exactly k items for each k <= around 200 (200
    is an upper bound since each order of items has at most 100 items, and
    the queries will require up to 100 items). Then, for each query k in the test case,
    find the minimum price to get >= k items from the knapsack array.


    Complexity: O(T(M * MAXK + L * MAXK)) where T is the number of test cases,
    M is the number of ways to buy one order of items, L is the the size of the
    list of positive integers, and MAXK is the maximum number of items possible.

*/

#include <bits/stdc++.h>

using namespace std;

const int maxm = 25;
const int maxk = 210;

double unit_p;
int m;

int qty[maxm];
double prices[maxm];
double knapsack[maxk]; //minimum price of getting k items
vector<int> ans;

inline void createKnapsack() { //O(KM)
    memset(knapsack, 0, sizeof(knapsack));
    for (int i = 1; i <= m + 1; i++) {
        if (knapsack[qty[i]] && (prices[i] < knapsack[qty[i]])) {
            knapsack[qty[i]] = prices[i];
        } else if (knapsack[qty[i]] == 0) {
            knapsack[qty[i]] = prices[i];
        }
    } //uncommenting ln 25-33 and commenting ln 34 - 43 gives a valid solution
    // for (int i = 1; i <= m + 1; i++) {
    //     for (int j = 1; j < maxk; j++) {
    //         if (knapsack[j] && j + qty[i] < maxk) {
    //             if (knapsack[j + qty[i]] > knapsack[j] + prices[i] || knapsack[j + qty[i]] == 0) {
    //                 knapsack[j + qty[i]] = knapsack[j] + prices[i];
    //             }
    //         }
    //     }
    // }
    for (int i = 1; i < maxk; i++) {
        for (int j = 1; j <= m + 1; j++) {
            if (knapsack[i] && i + qty[j] < maxk) {
                if (knapsack[i + qty[j]] > knapsack[i] + prices[j] || knapsack[i + qty[j]] == 0) {
                    knapsack[i + qty[j]] = knapsack[i] + prices[j];
                }
            }
        }
    }
}

void solveKnapsack(vector<int> & K) {
    for (int k: K) {
        double cheapest = 200000;
        for (int i = k; i < maxk; i++) {
            if (knapsack[i]) {
                if (knapsack[i] < cheapest) {
                    cheapest = knapsack[i];
                }
            }
        }
        printf("Buy %d for $%.2f\n", k, cheapest);
    }
    
}


int main() {
    //freopen("uva.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int q = 1;
    while (cin >> unit_p >> m) {
        qty[1] = 1;
        prices[1] = unit_p;
        for (int i = 2; i <= m + 1; i++) {
            cin >> qty[i] >> prices[i];
        }
        string s;
        cin.ignore();
        getline(cin, s);
        stringstream ss;
        ss << s;
        int i;
        vector<int> K;
        while (ss >> i) {
            K.push_back(i);
        }
        createKnapsack();
        printf("Case %d:\n", q++);
        solveKnapsack(K);
        for (int i = 1; i <= m + 1; i++) {
            qty[i] = 0;
            prices[i] = 0;
        }
    }
}