/*
        Author: Arvind Ramaswami

        I noticed that the number of couples in odd chairs is equal to the number
        of couples in even chairs, so I tried to find a construction for
        the food in each chair (starting from food 1 for odd chairs and food 2 for even chairs),
        but wasn't able to find one.

        Instead, I used the solution in the editorial, which involved drawing an edge from
        2 * i to 2 * i - 1 for each i and from each bf to gf, creating a graph without
        any odd cycles, allowing it to be transformed into a bipartite graph.

        If each side of the bipartite graph is given a food item, the conditions are
        satisfied. Each boy has a girlfriend in the other side of the bipartite graph, and
        for every person, there is an adjacent person in the other side of the bipartite graph.

        I kept getting wrong answer on test case 13 since I had accidentally set the size of the gf array to maxn instead
        of 2 * maxn.
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 100010;
int arr[2 * maxn];
int food[2 * maxn];
int gf[2 * maxn];
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
        int currFood = 1;
        int currPerson = (*unprocessed.begin());
        queue<int> q;
        q.push(currPerson);
        food[currPerson] = currFood;
        while (!q.empty()) {
            currPerson = q.front(); q.pop();
            unprocessed.erase(currPerson);
            currFood = (food[currPerson] == 1) ? 2 : 1;
            for (int person: adj[currPerson]) {
                if (food[person] == 0) {
                    q.push(person);
                    food[person] = currFood;
                }
            }
        }
    }
    for (int boy: boys) {
        cout << food[boy] << " " << food[gf[boy]] << "\n";
    }
}