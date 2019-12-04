/*

Author: Arvind Ramaswami

Solution: It suffices to create a data structure that finds the maximum cost from
column c1 to column c2, where where a path starts at row r1 and ends at row r2.

This can be done by a segment tree, where each node represents an starting & ending column
and has 25 values (each value represents the maximum cost for a starting & ending row).

With careful building / summation / updates, the result will be the max from column 0 to M - 1
over the starting and ending rows.

*/

#include <bits/stdc++.h>

using namespace std;


const int maxm = (1 << 15);
int N, M, Q;
int arr[6][maxm + 5];

struct node {
    int dp_vals[6][6];
    node() {
        reset();
    }

    void reset() {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                dp_vals[i][j] = -1;
            }
        }
    }

    void initialize(int index) {
        for (int i = 1; i <= N; i++) {
            dp_vals[i][i] = arr[i][index];
        }
    }

};

node * sum(node * n1, node * n2) {
    node * result = new node();
    for (int l = 1; l <= N; l++) {
        for (int r = 1; r <= N; r++) {
            for (int mid_l = 1; mid_l <= N; mid_l++) {
                for (int mid_r = mid_l - 1; mid_r <= mid_l + 1; mid_r++) {
                    int dp1 = n1->dp_vals[l][mid_l];
                    int dp2 = n2->dp_vals[mid_r][r];
                    if (mid_r >= 1 && mid_r <= N && ~dp1 && ~dp2) {
                        result->dp_vals[l][r] = max(result->dp_vals[l][r], dp1 + dp2);
                    }
                }
            }
        }
    }
    return result;
}

node * tree[2 * maxm];

void build(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = new node();
        if (tl < M) tree[v]->initialize(tl);
    } else {
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm + 1, tr);
        tree[v] = sum(tree[2 * v], tree[2 * v + 1]);  
    }
}

node * sum(int v, int tl, int tr, int l, int r) {
    if (l > r) {
        return nullptr;
    }
    if (l == tl && r == tr) {
        return tree[v];
    }
    int tm = (tl + tr) / 2;
    node * result = nullptr;
    node * result1 = sum(v*2, tl, tm, l, min(r, tm));
    node * result2 = sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    if (result1 == nullptr) {
        result = result2;
    } else if (result2 == nullptr) {
        result = result1;
    } else {
        result = sum(result1, result2);
    }
    return result;
}

void update(int v, int tl, int tr, int pos, node * new_node) {
    if (tl == tr) {
        tree[v] = new_node;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            update(v*2, tl, tm, pos, new_node);
        } else {
            update(v * 2 + 1, tm + 1, tr, pos, new_node);
        }
        tree[v] = sum(tree[2 * v], tree[2 * v + 1]);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> Q;

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
        }
    }

    build(1, 0, maxm - 1);

    for (int query = 1; query <= Q; query++) {
        int R, C, T;
        cin >> R >> C >> T;
        arr[R][C - 1] = T;
        node * new_node = new node();
        new_node->initialize(C - 1);
        update(1, 0, maxm - 1, C - 1, new_node);

        node * sm = sum(1, 0, maxm - 1, 0, M - 1);
        int max_sum = -1;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                max_sum = max(sm->dp_vals[i][j], max_sum);
            }
        }
        cout << max_sum << "\n";
    }
}