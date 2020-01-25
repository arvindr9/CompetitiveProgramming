#include <bits/stdc++.h>


/*
Author: Arvind Ramaswami

Solution: It is straightforward to determine the winning and losing positions for
a game with one knight (computed below by the function win(int x, int y){}).

Define val(x, y) to as:
If (x, y) is a winning position, val(x, y) is the maximum number of moves
that the next player can guarantee for a knight at (x, y).
If (x, y) is a losing position, val(x, y) is the minimum number of moves
that the next player can guarantee for a knight at (x, y).


The position of the knights is a winning position if at least one
knight is in a winning position and
max_{knights(x, y) in a losing position} val(x, y) < max_{knights(x, y) in a winning position} val(x, y).

val(x, y) can be computed naively with dp, but considering patterns
based on N mod 4 gives closed forms for val(x, y).

*/

using namespace std;

int K, N;

bool win_infinite(int x, int y) {
    // returns whether the position is winning if the board is infinite
    int big_x = (x - 1) / 2;
    int big_y = (y - 1) / 2;
    if (big_y % 2 == 0 && big_x % 2 == 0) {
        return false;
    }
    return true;
}

bool win(int x, int y) {
    if (N % 4 == 0) {
        if (min(x, y) == N) {
            return false;
        }
        if (max(x, y) >= N - 1) {
            return true;
        }
        return win_infinite(x, y);
    }
    if (N % 4 == 1) {
        if (min(x, y) == N - 1) {
            return true;
        }
        if (max(x, y) == N) {
            return false;
        }
        return win_infinite(x, y);
    }
    // N % 4 == 2 || N % 4 == 3
    return win_infinite(x, y);
}

int val_infinite(int x, int y) {
    int big_x = (x - 1) / 2;
    int big_y = (y - 1) / 2;
    if (big_x % 1 == 1 && big_y % 1 == 1) {
        return big_x + big_y;
    }
    if (big_x % 2 == 0 && big_y % 2 == 0) {
        return big_x + big_y;
    }
    if (x % 4 == 3 && y % 4 == 3) {
        return big_x + big_y - 1;
    }
    return big_x + big_y + 1;
}

int compute_val(int x, int y) {
    if (N % 4 == 0) {
        if (min(x, y) == N) {
            return N - 2;
        }
        if (max(x, y) >= N - 1) {
            int huge_block = min(x, y) / 4;
            return 2 * huge_block + (N - 1) / 2;
        }
        return val_infinite(x, y);
    }
    if (N % 4 == 1) {
        if (min(x, y) == N) {
            return N - 1;
        }
        if (min(x, y) == N - 1) {
            return N - 2;
        }
        if (max(x, y) == N) {
            int huge_block = (min(x, y) - 1) / 4;
            return 2 * huge_block + (N / 2);
        }
        return val_infinite(x, y);
    }
    if (N % 4 == 2) {
        return val_infinite(x, y);
    }
    // N % 4 == 3
    if (max(x, y) == N) {
        int huge_block = min(x, y) / 4;
        return 2 * huge_block + N / 2;
    }
    return val_infinite(x, y);
}

bool valid(int x, int y) {
    return min(x, y) >= 1 && max(x, y) <= N;
}


const int MN = -1e6;
const int MX = 1e6;
const int maxk = 2e5 + 6;
int max_win = MN;
int max_lose = MN;


int xs[maxk], ys[maxk];



int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> K >> N;

    for (int i = 1; i <= K; i++) {
        cin >> xs[i] >> ys[i];
    }
    for (int i = 1; i <= K; i++) {
        int iswin = win(xs[i], ys[i]);
        if (iswin) {
            max_win = max(max_win, compute_val(xs[i], ys[i]));
        } else {
            max_lose = max(max_lose, compute_val(xs[i], ys[i]));
        }
    }


    if (max_win <= max_lose) {
        cout << "NO\n";
    } else {

        cout << "YES\n";

        for (int i = 1; i <= K; i++) {
            pair<int, int> best_move;
            if (win(xs[i], ys[i])) {
                int latest_lose = MN;
                for (pair<int, int> move: (vector<pair<int, int>>){make_pair(-2, 1), make_pair(-2, -1), make_pair(-1, -2), make_pair(1, -2)}) {
                    int next_x = xs[i] + move.first;
                    int next_y = ys[i] + move.second;
                    if (valid(next_x, next_y)) {
                        if (!win(next_x, next_y)) {
                            int val = compute_val(next_x, next_y);
                            if (val > latest_lose) {
                                latest_lose = val;
                                best_move = make_pair(next_x, next_y);
                            }
                        }
                    }
                }
                if (latest_lose == MN) {
                    best_move = make_pair(xs[i], ys[i]);
                }
            } else {
                int earliest_win = MX;
                for (pair<int, int> move: (vector<pair<int, int>>){make_pair(-2, 1), make_pair(-2, -1), make_pair(-1, -2), make_pair(1, -2)}) {
                    int next_x = xs[i] + move.first;
                    int next_y = ys[i] + move.second;
                    if (valid(next_x, next_y)) {
                        if (win(next_x, next_y)) {
                            int val = compute_val(next_x, next_y);
                            if (val < earliest_win) {
                                earliest_win = val;
                                best_move = make_pair(next_x, next_y);
                            }
                        }
                    }
                }
                if (earliest_win == MX) {
                    best_move = make_pair(xs[i], ys[i]);
                }
            }
            cout << best_move.first << " " << best_move.second << "\n";
        }
    }

}
