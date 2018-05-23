/*
    -Author: Arvind Ramaswami

    Solution: We want to find the grundy number of the initial state of the board (and see if it's greater than zero).
    Given a board or sub-board, the grundy number is either

    0: if all tiles are primes
    the mex of the xors of the possible splits: if there exists a tile that is not a prime

    Thus, we preprocess whether every tile of each subarray is a prime and use this information to find the grundy number of
    every subarray. When calculating the grundy number by considering all possible splits, using a set to keep track of
    the grundy numbers of the next possible states will
    profuce a TLE on test 3 in C++, so either an array or vector must be used to avoid this.

*/

#include <bits/stdc++.h>

using namespace std;

int grid[31][31];

int grundy[31][31][31][31]; //grundy[i1][i2][j1][j2]
int prime[31][31][31][31];

int T, N;
int v[50];

vector<int> primes = {0, 0, 1, 1, 0, 1, 0, 1, 0, 0};


inline int mex() {
    for (int i = 0; i < 50; i++) {
        if (!v[i]) return i;
    }
    return 50;
}

inline void preparePrimes() {
    for (int di = 0; di <= N - 1; di++) {
        for (int dj = 0; dj <= N - 1; dj++) {
            for (int i = 1; i <= N - di; i++) {
                for (int j = 1; j <= N - dj; j++) {
                    if (di == 0 && dj == 0) {
                        if (primes[grid[i][j]]) {
                            prime[i][i][j][j] = 1;
                        } else {
                            prime[i][i][j][j] = 0;
                        }
                    } else if (di == 0) {
                        prime[i][i][j][j + dj] = prime[i][i][j][j + dj - 1] && prime[i][i][j + dj][j + dj];
                    } else if (dj == 0) {
                        prime[i][i + di][j][j] = prime[i][i + di - 1][j][j] && prime[i + di][i + di][j][j];
                    } else {
                        prime[i][i + di][j][j + dj] = prime[i][i + di - 1][j][j + dj - 1] && prime[i][i + di - 1][j + dj][j + dj]
                            && prime[i + di][i + di][j][j + dj - 1] && prime[i + di][i + di][j + dj][j + dj];
                    }
                }
            }
        }
    }
}

inline void prepareGrundy() {
    for (int di = 0; di <= N - 1; di++) {
        for (int dj = 0; dj <= N - 1; dj++) {
            for (int i = 1; i <= N - di; i++) {
                for (int j = 1; j <= N - dj; j++) {
                    int ans;
                    if (di == 0 && dj == 0) {
                        if (prime[i][i][j][j]) {
                            ans = 0;
                        } else {
                            ans = 1;
                        }
                    }
                    if (prime[i][i + di][j][j + dj]) {
                        ans = 0;
                    }
                    else {
                            for (int k = j; k < j + dj; k++) {
                                v[grundy[i][i + di][j][k] ^ grundy[i][i + di][k + 1][j + dj]]++;
                            }
                            for (int k = i; k < i + di; k++) {
                                v[grundy[i][k][j][j + dj] ^ grundy[k + 1][i + di][j][j + dj]]++;
                            }
                            ans = mex();
                            memset(v, 0, sizeof(v));
                        }
                    grundy[i][i + di][j][j + dj] = ans;
                }
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> N;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                cin >> grid[i][j];
            }
        }
        preparePrimes();
        prepareGrundy();
        cout << (grundy[1][N][1][N] ? "First" : "Second") << "\n";
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                grid[i][j] = 0;
            }
        }
        for (int i = 1; i <= N; i++) {
            for (int i2 = i; i2 <= N; i2++) {
                for (int j = 1; j <= N; j++) {
                    for (int j2 = 1; j2 <= N; j2++) {
                        grundy[i][i2][j][j2] = 0;
                        prime[i][i2][j][j2] = 0;
                    }
                }
            }
        }
    }

}