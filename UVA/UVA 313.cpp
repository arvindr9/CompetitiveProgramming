/*
    -Author: Arvind Ramaswami

    Solution: Using elementary trigonometry, we can find the range of x-values that each circle blocks.
    Now, we can sort the ranges by the first value then by the second value. Processing each range one
    by one in this sorted order allows us to find the union of the ranges.
*/

#include <bits/stdc++.h>

using namespace std;

int N, bx, by;
const long double eps = 1e-4;
set<pair<long double, long double>> regions;
vector<pair<long double, long double>> unions;


pair<long double, long double> intersect (long double x, long double y, long double r) {
    if (bx > x + eps) {
        long double alpha = atan((bx - x) / (by - y));
        long double theta = asin(r / sqrt( (bx - x) * (bx - x) + (by - y) * (by - y) ));
        return {bx - by * tan(alpha + theta), bx - by * tan(alpha - theta)};
    } else if (bx < x - eps) {
        long double alpha = atan((x - bx) / (by - y));
        long double theta = asin(r / sqrt( (x - bx) * (x - bx) + (by - y) * (by - y) ));
        return {bx + by * tan(alpha - theta), bx + by * tan(alpha + theta)};
    } else {
        long double dy = by - y;
        long double c = (by * r) / sqrt(dy * dy - r * r);
        return {bx - c, bx + c};
    }
}

int main() {
    // freopen("sq.in", "r", stdin);
    // freopen("sq.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int i = 0;
    while (cin >> N) {
        if (N == 0) break;
        //if (i) printf("\n");
        if (i == 0) i++;
        cin >> bx >> by; //change to while cin >> N;
        for (int i = 1; i <= N; i++) {
            int x, y, r;
            cin >> x >> y >> r;
            regions.insert(intersect(x, y, r));
        }
        long double l = regions.begin()->first;
        long double r = regions.begin()->first;
        for (pair<long double, long double> reg: regions) {
            if (reg.first > r + eps) {
                unions.push_back({l, r});
                l = reg.first;
                r = reg.second;
            } else {
                r = max(r, reg.second);
            }
        }
        int sz = unions.size();
        if (unions.empty() || abs(unions[sz - 1].first - regions.rbegin()->first) > eps) {
            unions.push_back({l, r});
        }
        for (pair<long double, long double> p: unions) {
                double f = p.first;
                double s = p.second;
                printf("%.2f %.2f\n", f, s);
        }
        printf("\n");
        regions.clear();
        unions.clear();
    }
}