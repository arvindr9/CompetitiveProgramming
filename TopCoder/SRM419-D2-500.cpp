/*
    -Author: Arvind Ramaswami

    Solution: Create a dp array of the possible winners for each configuration of stones and player number.
    At each state win[stone][turn], the current entry of the dp array is created by considering
    win[stone - removed][turn + 1]. If any of them are equal to {turn}, then the current player
    has a winning strategy, so win[stone][turn] = turn. Otherwise, 
    if any of the entries in the possible stated containes turn, win[stone][turn] is the union
    of all such entries. Otherwise, win[stone][turn] is the union of all the possible states of the next step.

    We also take care to include 0 in each entry either if either no future states can be reached or if
    it is possible that a future state with 0 will be reached (if playing optimally). This allows for a future
    state to possibly be {0, turn}, preventing the algorithm from perceiving that state as {turn} and considering
    it as that move as a winning strategy.
*/

#include <bits/stdc++.h>

using namespace std;

class NimForK {

    set<int> win[52][22]; //win[s][t] = set of possible winners when person t is playing and s stones are remaining

    void prepareWin(int n, int k, vector<vector<int>> & moves) {
        for (int stones = 1; stones <= n; stones++) { // 0 stones = no winners
            for (int turn = 1; turn <= k; turn++) {
                vector<int> possibleMoves = moves[stones - 1];
                set<int> res;
                int nextPerson = (turn + 1) % k;
                if (nextPerson == 0) nextPerson = k;
                for (int move : possibleMoves) {
                    if (move == stones) {
                        res = {turn};
                        break;
                    }
                    set<int> next = win[stones - move][nextPerson];
                    if (next.size() == 1 && *(next.begin()) == turn) {
                        res = {turn};
                        break;
                    }
                    if (next.count(turn)) for (int winner: next) res.insert(winner);
                }
                if (res.empty()) {
                    for (int move: possibleMoves) {
                        set<int> next = win[stones - move][nextPerson];
                        for (int winner: next) res.insert(winner);
                    }
                }
                if (res.empty()) res = {0};
                win[stones][turn] = res;
            }
        }
    }

    vector<vector<int>> processMoves(vector<string> &moves) {
        vector<vector<int>> res;
        for (string s: moves) {
            vector<int> v;
            stringstream ss;
            ss << s;
            int n;
            while (ss >> n) v.push_back(n);
            res.push_back(v);
        }
        return res;
    }

    public:
        vector<int> winners(int n, int k, vector<string> moves) { //winners(stones, players, moves)
            vector<vector<int>> moves2 = processMoves(moves);
            prepareWin(n, k, moves2);
            set<int> res = win[n][1];
            vector<int> ans;
            for (int i: res) if (i) ans.push_back(i);
            return ans;
        }

};
