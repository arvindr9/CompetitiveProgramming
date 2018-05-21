/*
    -Author: Arvind Ramaswami

    Solution: Let the grundy number of a state be 0 if it is a losing state and the mex of all the possible
    immediately subsequent states (the smallest nonnegative integer such that
    none of the subsequent states have that number) otherwise. If there are multiple chains, the grundy
    number will be the xor of the grundy number of each chain.

    If the grundy number of the original configuration is 0, then Saruman wins.
    Otherwise, if the grundy number is some positive k,
    Gandalf wins. If Gandalf wins, we must test the deletion of each number from
    each chain. Let the original grundy number of the chain be n. If there exists a number m
    from the chain such that n ^ m = k, then Gandalf must remove m from that chain (since this will
    result in a grundy number of zero).
*/

#include <iostream>
#include <set>
#include <vector>

using namespace std;

int k;

vector<vector<int>> chains;

inline int mex(set<int> &grundys) {
    for (int i = 0; i <= 10000; i++) {
        if (!grundys.count(i)) return i;
    }
}

int grundy(vector<int> &v) {
    if (v.size() == 0) return 0;
    if (v.size() == 1) return 1;
    set<int> elements;
    for (int i: v) {
        elements.insert(i);
    }
    set<int> grundys;
    for (int del: elements) {
        int g = 0;
        vector<int> v2;
        for (int elt: v) {
            if (elt > del) {
                v2.push_back(elt);
            } else {
                g ^= grundy(v2);
                v2.clear();
            }
        }
        g ^= grundy(v2);
        grundys.insert(g);
    }
    return mex(grundys);
}

int satisfy(vector<int> & v, int k) {
    set<int> elements;
    for (int i: v) {
        elements.insert(i);
    }
    int grund = grundy(v);
    int wanted = grund ^ k;
    for (int del: elements) {
        int g = 0;
        vector<int> v2;
        for (int elt: v) {
            if (elt > del) {
                v2.push_back(elt);
            } else {
                g ^= grundy(v2);
                v2.clear();
            }
        }
        g ^= grundy(v2);
        if (g == wanted) {
            return del;
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> k;
    int g = 0; //g = the grundy number of the original setup (to be calculated in the following lines)
    for (int i = 1; i <= k; i++) {
        int n;
        cin >> n;
        vector<int> v;
        for (int i = 1; i <= n; i++) {
            int ring;
            cin >> ring;
            v.push_back(ring);
        }
        chains.push_back(v);
        g ^= grundy(v);
    }
    if (g == 0) {
        cout << "S\n";

    } else {
        cout << "G\n";
        for (int i = 0; i < (int) chains.size(); i++) { //try to convert the grundy number to 0
            int ans = satisfy(chains[i], g);
            if (~ans) {
                cout << (i + 1) << " " << ans << "\n";
                break;
            }
        }
    }
}