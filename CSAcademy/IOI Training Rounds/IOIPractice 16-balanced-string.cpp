#include <bits/stdc++.h>

/*
    Author: Arvind Ramaswami

    Solution (based on https://csacademy.com/contest/ioi-2016-training-round-5/task/balanced-string/solution/):
    
    For the original string, it is invalid for there to exist two contiguous A's and
    two contiguous B's (here, the first and last character are also defined to be contiguous).

    Without loss of generality, suppose there are no two contiguous B's. Then, we can
    create an encoding based on the sizes of the maximal contiguous sequences of A's (example:
    ABBABAAA would become (1, 4)). The minimum and maximum elements of the encoding must have difference
    at most 1. Convert the encoding such that the minimum elements are replaced with A's
    and the maximum elements will be replaced with B's. This returns a string of at most
    half the size, which we can recursively perform the algorithm on.
*/

using namespace std;

typedef pair<int, int> pi;

int T;

int valid(string s) {
    vector<pair<char, int>> compress;
    int l = s.size();
    int i = 0;
    char cur_char = s[0];
    int cnt = 0;
    while (i < l) {
        if (s[i] != cur_char) {
            compress.push_back(make_pair(cur_char, cnt));
            cur_char = s[i];
            cnt = 1;
        } else {
            cnt++;
        }
        i++;
    }
    compress.push_back(make_pair(cur_char, cnt));
    int num_compress = compress.size();

    if (num_compress == 1) {
        return true;
    }

    // num_compress > 1

    if (compress[0].first == compress[num_compress - 1].first) {
        compress[0].second += compress[num_compress - 1].second;
        compress.pop_back();
    }


    if ((int)compress.size() == 1) {
        return true;
    }

    num_compress = compress.size();

    // 2 \mid num_compress

    vector<int> enc1;
    vector<int> enc2;

    bool sparse1 = true; //denotes whether the A's have all ones
    bool sparse2 = true;

    for (int i = 0; i < num_compress; i++) {
        int qty = compress[i].second;
        if (i % 2 == 0) {
            enc1.push_back(qty);
            if (qty > 1) {
                sparse1 = false;
            }
        } else {
            enc2.push_back(qty);
            if (qty > 1) {
                sparse2 = false;
            }
        }
    }

    if (!sparse1 && !sparse2) {
        return false;
    }

    vector<int> encoding;
    if (!sparse1) {
        encoding = enc1;
    } else {
        encoding = enc2;
    }

    int mn = 1e7;
    int mx = -1;


    for (int i: encoding) {
        mn = min(mn, i);
        mx = max(mx, i);
    }

    if (abs(mn - mx) > 1) {
        return false;
    } else if (mn == mx) {
        return true;
    }

    string s2;

    for (int i: encoding) {
        if (i == mn) {
            s2 += 'A';
        } else {
            s2 += 'B';
        }
    }

    return valid(s2);


}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        string s;
        cin >> s;
        cout << valid(s) << "\n";
    }
}
