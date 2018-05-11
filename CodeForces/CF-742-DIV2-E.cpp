#include <bits/stdc++.h>

using namespace std;

const int maxn = 100010;
int arr[2 * maxn];
int food[2 * maxn];
int gf[maxn];
vector<int> adj[2 * maxn];
set<int> unprocessed;
vector<int> boys;
int n;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= 2 * n; i++) {
        unprocessed.insert(i);
    }
    for (int i = 1; i <= n; i++) {
        adj[2 * i].push_back((2 * i + 1) % (2 * n));
        adj[(2 * i + 1) % (2 * n)].push_back(2 * i);
        int b, g;
        cin >> b >> g;
        adj[b].push_back(g);
        adj[g].push_back(b);
        gf[b] = g;
        boys.push_back(b);
    }
    while (unprocessed.size()) {
        int currPerson = (*unprocessed.begin());
        queue<int> q;
        q.push(currPerson);
        food[currPerson] = 1;
        while (!q.empty()) {
            currPerson = q.front(); q.pop();
            unprocessed.erase(currPerson);
            for (int person: adj[currPerson]) {
                if (!food[person]) {
                    q.push(person);
                    food[person] = (food[currPerson] ^ 3);
                }
            }
        }
    }
    for (int boy: boys) {
        cout << food[boy] << " " << food[gf[boy]] << "\n";
    }
}