/**
 *  Author: Arvind Ramaswami
 * 
 * When drawing ST to split a triangle ABC, one of the regions will be a triangle. Thus, consider
 * each vertex one at a time to consider the possibility that this triangle to contain that vertex.
 * Let's say the vertex is A and S lies
 * on AB and T lies on AC. Then, AS * AT = 1/2 (AB * BC). Also, AS + AT = BS + BC + CS = 1/2(perimeter).
 * Thus, we have two equations in terms of AS and AT and we can solve for both using the quadratic formula and then check
 * if they are valid. Then, S would equal A + (B - A) * (AS / AB) and T would equal A + (C - A) * (AT / AC). 
 * 
 **/


#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

typedef long double ld;
const ld eps = 1e-8;

ld perimeter = 0;

ld x[3];
ld y[3];
ld sides[3];

ld eq(ld a, ld b) {
    return a + eps > b && a - eps < b;
}

ld leq(ld a, ld b) {
    return b + eps > a;
}

ld geq(ld a, ld b) {
    return a + eps > b;
}

void process() {
    for (int i = 0; i < 3; i++) {
        int a1 = (i + 1) % 3;
        int a2 = (i + 2) % 3;
        sides[i] = sqrt((x[a1] - x[a2]) * (x[a1] - x[a2]) + (y[a1] - y[a2]) * (y[a1] - y[a2]));
        perimeter += sides[i];
    }
}

vector<vector<ld>> convert(int i, ld s1, ld s2) {
    int a1 = (i + 1) % 3;
    int a2 = (i + 2) % 3;
    ld r1 = s1 / sides[a1];
    ld r2 = s2 / sides[a2];
    vector<ld> p1 = {x[i] + (x[a2] - x[i]) * r1, y[i] + (y[a2] - y[i]) * r1};
    vector<ld> p2 = {x[i] + (x[a1] - x[i]) * r2, y[i] + (y[a1] - y[i]) * r2};
    return {p1, p2};
}

vector<vector<ld>> solve(int i) { //one island is a triangle that contains the ith vertex of the original triangle
    int a1 = (i + 1) % 3;
    int a2 = (i + 2) % 3;
    ld prod = sides[a1] * sides[a2] / 2;
    ld sum = perimeter / 2;
    ld discr = sum * sum - 2 * sides[a1] * sides[a2];
    if (eq(discr, 0)) {
        ld sl = sum / 2;
        if (leq(sl, sides[a1]) && leq(sl, sides[a2])) return convert(i, sl, sl);
        else return {};
    }
    if (discr < -eps) {
        return {};
    }
    ld s1 = (sum - sqrt(discr)) / 2;
    ld s2 = (sum + sqrt(discr)) / 2;
    if (leq(s1, sides[a1]) && leq(s2, sides[a2])) return convert(i, s1, s2);
    else if (leq(s2, sides[a1]) && leq(s1, sides[a2])) return convert(i, s2, s1);
    else return {};
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < 3; i++) {
        cin >> x[i] >> y[i];
    }
    process();
    vector<vector<ld>> ans = {};
    for (int i = 0; i < 3; i++) {
        vector<vector<ld>> candidate = solve(i);
        if (!candidate.empty()) {ans = candidate; break;}
    }
    cout.precision(10);
    if (!ans.empty()) {
        cout << "YES\n" <<fixed<< ans[0][0] << " "<< ans[0][1] <<"\n"<< ans[1][0] <<" "<< ans[1][1]; 
    } else {
        cout << "NO\n";
    }


}