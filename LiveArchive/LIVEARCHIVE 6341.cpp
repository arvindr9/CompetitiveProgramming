#include <bits/stdc++.h>

/*
    Author: Arvind Ramaswami
    This solution is based on the implementation here: https://github.com/renzov/Red_Crown/blob/master/Live%20Archive/6341.cpp

    Solution: Let f(x, y) equal the time it takes if the point is placed at (x, y).
    Since f(x, y) is the max of several convex functions (the time it takes for all
    the ents to reach that point), f(x, y) is a convex function. Thus, we can use ternary search
    to find the optimal x (and while processing each x, we can use ternary search to find
    the corresponding y).
*/

using namespace std;

int t, n;

const int maxn = 55;
const int INF = 2e6;
double x_max, x_min, y_max, y_min;

int x[maxn], y[maxn], s[maxn];

double f(double _x, double _y) {
    double res = 0; //max value of time
    for (int i = 1; i <= n; i++) {
        double dx = abs(_x - x[i]);
        double dy = abs(_y - y[i]);
        double dist = sqrt(dx * dx + dy * dy);
        double time = dist / (s[i]);
        res = max(res, time);
    }
    return res;
}

double g(double _x, bool print = 0) {
    double ymin = y_min;
    double ymax = y_max;
    int count = 70;
    while (count--) {
        double a = (2. * ymin + ymax) / 3.;
        double b = (ymin + 2. * ymax) / 3.;
        if (f(_x, a) < f(_x, b)) {
            ymax = b;
        } else {
            ymin = a;
        }
    }
    if (print) {
        cout << "ymin: " << ymin << ", ymax: " << ymax << "\n";
    }
    return f(_x, ymin);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("circles.in", "r", stdin);
    // freopen("circles.out", "w", stdout);
    cin >> t;
    cout << setprecision(6) << fixed;
    for (int cs = 1; cs <= t; cs++) {
        cin >> n;
        x_max = y_max = INF;
        x_min = y_min = -INF;
        
        for (int i = 1; i <= n; i++) {
            cin >> x[i] >> y[i] >> s[i];
        }

        int ct = 70;
        while (ct--) {
            double a = (2. * x_min + x_max) / 3.;
            double b = (x_min + 2. * x_max) / 3.;
            if (g(a) < g(b)) {
                x_max = b;
            } else {
                x_min = a;
            }
        }
        cout << g(x_min, 0) << "\n";
        // cout << "x_min: " << x_min << ", y_min: " << y_min << "\n";

    } 
}