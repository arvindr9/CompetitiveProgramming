#include <bits/stdc++.h>

/*
    O(2^{N / 2} log(N)) solution:

    Memory limit exceeded on test cases 34, 35, 37 - 42
    Wall time limit exceeded on test case 36

    Key ideas: 
    - For the subset of cards for which the red side is turned up, the summation
    of those cards over both sides must equal the total sum of all the blue sides of
    the N cards.

    - Standard knapsack to compute the possible sums of red + blue over all the subsets
    of the cards takes ~2^40 steps, so one can use meet in the middle to split it into
    two problems of size 2^20.

    Solution: 
    

    I created a knapsack type data structure that I named knap_tree.
    Each path from the root to a node represents a subset that is added,
    and for each node, attributes like the sum of , card index that creates the node,
    and depth are kept track of.
    For a knap_tree, sdn_map stores the possible depths (and its associated node) for a sum.

    Create one knap tree for the first half of the cards and another knap tree for the
    second half of the cards. For each node of the first knap_tree, check to see if sum
    + some sum from the second knap tree equals the sum of the N blue cards (using the sdn_map). If so, binary
    search (using sdn map) to find the optimal node in the second knap_tree such that the two depths' sum
    is the closest to N / 2. Repeat this for
    all the nodes in the first knap_tree to find all candidate pairs of nodes, and
    check which pair has sum closest to N / 2.

*/

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pi;
const ll maxNodes = (1 << 20) + 5;

struct knap_tree {
    ll num_nodes;
    vector<ll> adj[maxNodes];
    ll node_sum[maxNodes];
    ll depth[maxNodes];
    ll cardIndices[maxNodes];
    ll parent[maxNodes];
    map<ll, map<ll, ll> > sdn_map; //sum -> depth -> node

    knap_tree() {
        depth[0] = 0;
        cardIndices[0] = 0;
        node_sum[0] = 0;
        num_nodes = 1;
    }

    void insert(ll index, ll val) {
        for (ll i = 0; i < num_nodes; i++) {
            ll nextNode = num_nodes + i;
            adj[i].push_back(nextNode);
            depth[nextNode] = depth[i] + 1;
            node_sum[nextNode] = node_sum[i] + val;
            cardIndices[nextNode] = index;
            parent[nextNode] = i;
            sdn_map[node_sum[nextNode]][depth[nextNode]] = nextNode; //main bug: had cardIndices[nextNode] instead of node_sum[nextNode]
        }
        num_nodes *= 2;
    }

    vector<ll> getPath(ll node) {
        vector<ll> ans;
        while (node != 0) {
            ans.push_back(cardIndices[node]);
            node = parent[node];
        }
        return ans;
    }

    bool exists(ll sm) {
        if (sdn_map.count(sm)) {
            return true;
        }
        return false;
    }

    ll best_node(ll t1_depth, ll sm, ll n) {
        // returns {node}
        // assume that exists(sm) is true
        map<ll, ll> depth_node_map = sdn_map[sm];
        ll target = n / 2 - t1_depth;
        auto it = depth_node_map.lower_bound(target);
        // fix on thing: it could equal depth_node_map.end()
        ll cand1 = it->second;
        ll dc1 = it->first;
        if (it != depth_node_map.begin()) {
            it--;
            ll cand2 = it->second;
            ll dc2 = it->first;
            if (abs(2 * (t1_depth + dc1) - n) < abs(2 * (t1_depth + dc2) - n)) return cand1;
            else return cand2;
        } else {
            return cand1;
        }
        // 2 (t1_depth + t2_depth) should be as close as possible to n
    }

    void printNodes() {
        cout << "\nparent:\n";
        for (ll i = 0; i < num_nodes; i++) {
            cout << parent[i] << " ";
        }
        cout << "\ndepth:\n";
        for (ll i = 0;i < num_nodes; i++) {
            cout << depth[i] << " ";
        }
        cout << "\nsum:\n";
        for (ll i = 0;i < num_nodes; i++) {
            cout << node_sum[i] << " ";
        }
        cout << "\n";
    }

    void print_sdn_map() {
        for (pair<ll, map<ll, ll>> elt: sdn_map) {
            ll sm = elt.first;
            cout << "sum: " << sm << "\n";
            for (pair<ll, ll> p: sdn_map[sm]) {
                cout << "\tdepth: " << p.first << ", node: " << p.second << "\n";
            }
        }
    }
};

const ll maxn = 45;
ll n;
ll r[maxn], b[maxn];
ll reds[maxn];

knap_tree t1, t2;


vector<ll> solve() {
    vector<pi> candidate_pairs;
    ll sum_b = 0;
    for (ll i = 1; i <= n; i++) sum_b += b[i];
    for (ll i = 0; i < t1.num_nodes; i++) {
        ll val1 = t1.node_sum[i];
        ll wanted_sum = sum_b - val1;
        if (t2.exists(wanted_sum)) { //maybe t2.exists(2) is returning false when i = 1, i = 2? (check this tom. morning)
            ll best_node = t2.best_node(t1.depth[i], wanted_sum, n);
            candidate_pairs.push_back({i, best_node});
        }
    }
    if (candidate_pairs.empty()) return {};

    // for (pair<ll, ll> p: candidate_pairs) {
    //     cout << p.first << " " << p.second << "\n"; 
    // }

    // cout << "t1 sdn map:\n";
    // t1.print_sdn_map();

    // cout << "t2 sdn map:\n";
    // t2.print_sdn_map();

    // cout << "t2.exists:\n";
    // for (ll i = 0; i < t2.num_nodes; i++) {
    //     cout << t2.exists(i) << " ";
    // }
    // cout << "\n";

    // cout << "t1 size: " << t1.num_nodes << "\n";
    // cout << "t2 size: " << t2.num_nodes << "\n";

    // cout << "t1 nodes: "; t1.printNodes();
    // cout << "t2 nodes: "; t2.printNodes();
    // vector<ll> a = t2.getPath(0);
    // a = t2.getPath(1);
    // a = t2.getPath(2);
    // a = t2.getPath(3);

    pi bestPair = {-1, -1};
    ll closest_to_n = 2 * n;
    for (pi p: candidate_pairs) {
        ll n_dist = abs(2 * (t1.depth[p.first] + t2.depth[p.second]) - n);
        if (n_dist < closest_to_n) {
            closest_to_n = n_dist;
            bestPair = p;
        }
    }
    vector<ll> reds(n + 1);
    // cout << "best pair: " << bestPair.first << " " << bestPair.second << "\n";
    for (ll a: t1.getPath(bestPair.first)) reds[a] = 1;
    for (ll b: t2.getPath(bestPair.second)) reds[b] = 1;
    vector<ll> ans;
    for (ll i = 1;i <= n; i++) {
        if (reds[i]) ans.push_back(0);
        else ans.push_back(1);
    }


    return ans;
    
    // return {};

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("a.in", "r", stdin);
    // freopen("a.out", "w", stdout);
    cin >> n;
    for (ll i = 1; i < n / 2 + 1; i++) {
        cin >> r[i] >> b[i];
        t1.insert(i, r[i] + b[i]);
    }
    for (ll i = n / 2 + 1; i <= n; i++) {
        cin >> r[i] >> b[i];
        t2.insert(i, r[i] + b[i]);
    }
    vector<ll> ans = solve();
    if (ans.size() == 0) cout << -1;
    else {
        for (ll d: ans) {
            cout << d;
        }
        cout << "\n";
    }
}
