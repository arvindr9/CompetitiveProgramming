/*
        Author: Arvind Ramaswami

        I noticed that the number of couples in odd chairs is equal to the number
        of couples in even chairs, so I tried to find a construction for
        the food in each chair (starting from food 1 for odd chairs and food 2 for even chairs),
        but wasn't able to find one.

        Instead, I used the solution in the editorial, which involved drawing an edge from
        2 * i to 2 * i + 1 for each i and from each bf to gf, creating a graph without
        any odd cycles, allowing it to be transformed into a bipartite graph.

        If each side of the bipartite graph is given a food item, the conditions are
        satisfied. Each boy has a girlfriend in the other side of the bipartite graph, and
        for every person, there is an adjacent person in the other side of the bipartite graph.

        Wrong answer on test case 13
*/
#include <bits/stdc++.h>

using namespace std;

const int maxn = 100010;
int arr[2 * maxn];
int food[2 * maxn];
int gf[maxn];
set<int> adj[2 * maxn];
set<int> unprocessed;
vector<int> boys;
int n;

void dfs(int currPerson, int f) {
    food[currPerson] = f;
    unprocessed.erase(currPerson);
    for (int person: adj[currPerson]) {
        if(!food[person]) {
            dfs(person, f ^ 3);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= 2 * n; i++) {
        unprocessed.insert(i);
    }
    for (int i = 1; i <= n; i++) {
        adj[2 * i].insert((2 * i + 1) % (2 * n));
        adj[(2 * i + 1) % (2 * n)].insert(2 * i);
        int b, g;
        cin >> b >> g;
        adj[b].insert(g);
        adj[g].insert(b);
        gf[b] = g;
        boys.push_back(b);
    }
    while (unprocessed.size()) {
        int currPerson = (*unprocessed.begin());
        dfs(currPerson, 1);
    }
    for (int boy: boys) {
        cout << food[boy] << " " << food[gf[boy]] << "\n";
    }
}