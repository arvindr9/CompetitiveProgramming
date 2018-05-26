/*
    -Author: Arvind Ramaswami

    Solution: It can be shown that for a point P, if it's distance from A is d_1 and its distance from B is a * d_1 where a > 1, then the locus
    of possible regions is two circles. Thus, the problem reduces to finding the intersection of two circles.

    There are different cases to consider; the number of intersections could either be zero, one, two or infinite (one circle is inside another).
    All the cases are trivial except for two intersections; in this case, we find (mathematically) the length of the perpendicular from one
    of the intersections to the segment connecting the centers of the circles, as well as the distance from one of the centers to
    the foot of that perpendicular, and adding vectors with the corresponding magnitudes and appropriate directions gives the desired
    points of intersection.
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX / 2;
const long double eps = 1e-4;

struct pt {
    long double x, y;
    pt() {}
    pt(long double _x, long double _y) : x(_x), y(_y) {}
    pt(const pt &p) : x(p.x), y(p.y) {}
    pt operator+(const pt &p) const {return pt(x + p.x, y + p.y);}
    pt operator*(long double c) const {return pt(c * x, c * y);}
    pt operator-(const pt &p) const {return pt(x - p.x, y - p.y);}
    pt operator/(long double c) const {return pt(x/c, y/c);}

    bool operator <(const pt &other) const {
        if(abs(x - other.x) > eps) {
            return x < other.x;
        }
        if (abs(y - other.y) > eps) {
            return y < other.y;
        }
        return false;
    }
};

struct circle {
    long double x, y, r;
    circle(long double _x, long double _y, long double _r) {
        x = _x;
        y = _y;
        r = _r;
    }
    circle(pt p, long double _r) {
        x = p.x;
        y = p.y;
        r = _r;
    }
};

long double quadratic(long double a, long double b, long double c, char op) {
    long double ans = -b;
    if (op == '+') ans += sqrt(b*b - 4. * a * c);
    else ans -= sqrt(b*b - 4. * a * c);
    ans /= (2. * a);
    return ans;
}

long double dist_sq(circle c1, circle c2) {
    return (c2.x - c1.x) * (c2.x - c1.x) + (c2.y - c1.y) * (c2.y - c1.y);
}

int satisfy(pt p) {
    return p.x > -1000 - eps && p.x < 1000 + eps && p.y > -1000 - eps && p.y < 1000 + eps;
}

pt rot90(pt p) {
    return pt(-p.y, p.x);
}

set<pt> intersect(circle c1, circle c2) {
    set<pt> res;
    double x1 = c1.x;
    double x2 = c2.x;
    double y1 = c1.y;
    double y2 = c2.y;
    double r = c1.r;
    double R = c2.r;
    pt p1 = pt(x1, y1);
    pt p2 = pt(x2, y2);
    pt diff = p2 - p1;
    if (abs(x1 - x2) < eps && abs(y1 - y2) < eps) { //infinite intersections
        if (abs(r - R) < eps) {
            pt p = pt(x1 - r, y1);
            if (satisfy(p)) res.insert(p);
        }
    } else if (abs(dist_sq(c1, c2) - (r + R)*(r + R)) < eps) { // 1 intersection
        pt p = p1 + (p2 - p1) * (r/(r+R));
        if (satisfy(p)) res.insert(p);
    } else if (dist_sq(c1, c2) - (r + R)*(r + R) < -eps) { //2 intersections
        double d = sqrt(diff.x * diff.x + diff.y * diff.y);
        double a = (r * r - R * R + d * d) / (2 * d);
        double h = sqrt(r*r - a*a);
        pt ans1 = p1 + diff * (a / d) + rot90(diff * h / d);
        pt ans2 = p1 + diff * (a / d) - rot90(diff * h / d);
        if (satisfy(ans1)) res.insert(ans1);
        if (satisfy(ans2)) res.insert(ans2);
    }
    return res;
}

circle circ(pt p1, pt p2, long double a) {
    pt diff = p2 - p1;
    pt left = p1 + diff * a/(a+1);
    pt right = p1 + diff * a/(a - 1);
    pt diameter = right - left;
    pt center = (left + right) / 2;
    long double r = sqrt(diameter.x * diameter.x + diameter.y * diameter.y) * .5;
    circle c = circle(center, r);
    return c;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long double a, b;
    cin >> a >> b;
    int kx, ky, bx, by, jkx, jky, jnx, jny;
    cin >> kx >> ky>> bx>> by>> jkx>> jky>> jnx>> jny;
    pt K = pt(kx, ky);
    pt B = pt(bx, by);
    pt JK = pt(jkx, jky);
    pt JN = pt(jnx, jny);
    circle c1 = circ(K, B, a);
    circle c2 = circ(JK, JN, b);
    set<pt> inter = intersect(c1, c2);
    if (inter.empty()) {
        puts("Impossible!");
    } else {
        pt ans = *(inter.begin());
        double x = ans.x;
        double y = ans.y;
        printf("%.2f %.2f\n", x, y);
    }
}