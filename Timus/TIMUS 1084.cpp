/*
    Author: Arvind Ramaswami

    Solution: If the radius is smaller than half the side length of the square, find the area of the circle.
    If the radius is larger than half the diagonal of a square, find the area of the square.
    Otherwise, we want to find the intersection of a circle and square. This can be done by finding
    the area of a triangle with hypotenuse r and one leg equal to half the side length and
    the area of a sector with radius r and angle (pi / 4 - arccos(half the side length / radius))
    and multiplying their sum by 8 (since the desired region can be partitioned into 8 such
    triangles and sectors).
*/

#include <iostream>
#include <iomanip>

using namespace std;

typedef long double ld;

const ld PI = 3.14159265;
const ld eps = 1e-8;

ld s, r;

ld ans = 0;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s >> r;
    s /= 2;
    if (r < s + eps) {
        ans = PI * r * r;
    }
    else if (r > s * sqrt(2) - eps) ans = 4 * s * s;
    else {
        ld base_sq = r * r - s * s;
        ld angle = acos(s / r);
        ld sector_angle = PI / 4 - angle;
        ld sector_area = sector_angle * r * r / 2;
        ld triangle_area = sqrt(base_sq) * s / 2;
        ans = 8 * (triangle_area + sector_area);
    }
    cout << fixed;
    cout << setprecision(3)  << ans << "\n";
}