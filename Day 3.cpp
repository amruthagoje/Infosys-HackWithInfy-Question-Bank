/*1. You are given a tree with n nodes and a color[i] for each node.

For each of q queries, given node v, find the number of unique colors in the subtree
rooted at v.*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

const int N = 200005;

vector<int> tree[N];
int color[N], subtreeSize[N];
bool bigChild[N];
unordered_map<int, int> freq;
int distinct = 0;
int result[N];

void calculateSize(int node, int parent) {
    subtreeSize[node] = 1;
    for (int child : tree[node]) {
        if (child != parent) {
            calculateSize(child, node);
            subtreeSize[node] += subtreeSize[child];
        }
    }
}

void addSubtree(int node, int parent, int val) {
    freq[color[node]] += val;

    if (freq[color[node]] == 1 && val == 1) distinct++;
    if (freq[color[node]] == 0 && val == -1) distinct--;

    for (int child : tree[node]) {
        if (child != parent && !bigChild[child]) {
            addSubtree(child, node, val);
        }
    }
}

void dfs(int node, int parent, bool keep) {
    int maxSize = -1, heavyChild = -1;

    for (int child : tree[node]) {
        if (child != parent && subtreeSize[child] > maxSize) {
            maxSize = subtreeSize[child];
            heavyChild = child;
        }
    }

    for (int child : tree[node]) {
        if (child != parent && child != heavyChild) {
            dfs(child, node, false);
        }
    }

    if (heavyChild != -1) {
        dfs(heavyChild, node, true);
        bigChild[heavyChild] = true;
    }

    addSubtree(node, parent, 1);
    result[node] = distinct;

    if (heavyChild != -1) bigChild[heavyChild] = false;

    if (!keep) addSubtree(node, parent, -1);
}

/*2. You are given a tree and a value[i] for each node.
Each query provides a node v and a number k.
Return how many nodes in the subtree of v have value equal to k.*/
#include <iostream>
#include <vector>
using namespace std;

const int N = 200005;

vector<int> tree[N];
int value[N], in[N], out[N], euler[N];
int timer = 0;

void dfs(int node, int parent) {
    in[node] = ++timer;
    euler[timer] = value[node];

    for (int child : tree[node]) {
        if (child != parent) {
            dfs(child, node);
        }
    }

    out[node] = timer;
}

int query(int node, int k) {
    int count = 0;
    for (int i = in[node]; i <= out[node]; i++) {
        if (euler[i] == k) count++;
    }
    return count;
}

/*3. Each node in the tree has a value val[i].
Given q queries of nodes v, return the sum of values in the subtree rooted at v.*/
#include <iostream>
#include <vector>
using namespace std;

const int N = 200005;

vector<int> tree[N];
int value[N];
long long subtreeSum[N];

void dfs(int node, int parent) {
    subtreeSum[node] = value[node];

    for (int child : tree[node]) {
        if (child != parent) {
            dfs(child, node);
            subtreeSum[node] += subtreeSum[child];
        }
    }
}

/*4. Given a tree and multiple queries of the form (u, v), return the distance between
nodes u and v.*/
#include <iostream>
#include <vector>
using namespace std;

const int N = 200005;
const int LOG = 20;

vector<int> tree[N];
int parent[N][LOG], depth[N];

void dfs(int node, int par) {
    parent[node][0] = par;

    for (int i = 1; i < LOG; i++) {
        parent[node][i] = parent[parent[node][i - 1]][i - 1];
    }

    for (int child : tree[node]) {
        if (child != par) {
            depth[child] = depth[node] + 1;
            dfs(child, node);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    int diff = depth[u] - depth[v];

    for (int i = 0; i < LOG; i++) {
        if (diff & (1 << i)) {
            u = parent[u][i];
        }
    }

    if (u == v) return u;

    for (int i = LOG - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

int distance(int u, int v) {
    int L = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[L];
}

/*5. You are given a rooted tree. For q queries (v, k), return the k-th ancestor of
node v.
If it doesn’t exist, return -1.
Hint: Use binary lifting (precompute ancestors in log steps)*/
#include <iostream>
#include <vector>
using namespace std;

const int N = 200005;
const int LOG = 20;

vector<int> tree[N];
int parent[N][LOG];
int depth[N];

void dfs(int node, int par) {
    parent[node][0] = par;

    for (int i = 1; i < LOG; i++) {
        if (parent[node][i - 1] != -1)
            parent[node][i] = parent[parent[node][i - 1]][i - 1];
        else
            parent[node][i] = -1;
    }

    for (int child : tree[node]) {
        if (child != par) {
            depth[child] = depth[node] + 1;
            dfs(child, node);
        }
    }
}

int kthAncestor(int node, int k) {
    for (int i = 0; i < LOG; i++) {
        if (k & (1 << i)) {
            node = parent[node][i];
            if (node == -1) return -1;
        }
    }
    return node;
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < LOG; j++) {
            parent[i][j] = -1;
        }
    }


    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    depth[1] = 0;
    dfs(1, -1);

    int q;
    cin >> q;

    while (q--) {
        int node, k;
        cin >> node >> k;
        cout << kthAncestor(node, k) << endl;
    }

    return 0;
}

/*6. Each node has a weight.
For each query (u, v), find the maximum weight along the path from u to v.
Hint: Use Heavy-Light Decomposition or Euler Tour + Segment Tree.*/
#include <iostream>
#include <vector>
using namespace std;

const int N = 200005;
const int LOG = 20;

vector<pair<int,int>> tree[N];
int parent[N][LOG], maxWeight[N][LOG], depth[N];

void dfs(int node, int par, int weight) {
    parent[node][0] = par;
    maxWeight[node][0] = weight;

    for (int i = 1; i < LOG; i++) {
        parent[node][i] = parent[parent[node][i - 1]][i - 1];
        maxWeight[node][i] = max(maxWeight[node][i - 1],
                                 maxWeight[parent[node][i - 1]][i - 1]);
    }

    for (auto edge : tree[node]) {
        int child = edge.first;
        int wt = edge.second;

        if (child != par) {
            depth[child] = depth[node] + 1;
            dfs(child, node, wt);
        }
    }
}

int getMax(int u, int v) {
    int result = 0;

    if (depth[u] < depth[v]) swap(u, v);

    int diff = depth[u] - depth[v];

    for (int i = 0; i < LOG; i++) {
        if (diff & (1 << i)) {
            result = max(result, maxWeight[u][i]);
            u = parent[u][i];
        }
    }

    if (u == v) return result;

    for (int i = LOG - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            result = max(result, max(maxWeight[u][i], maxWeight[v][i]));
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    result = max(result, max(maxWeight[u][0], maxWeight[v][0]));

    return result;
}

/*7. Given a tree and a node u, return the list of all nodes at distance K from u.
Hint: BFS from u, track levels.*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> getNodesAtDistanceK(int start, int K, int n, vector<int> tree[]) {
    vector<int> distance(n + 1, -1);
    queue<int> q;

    q.push(start);
    distance[start] = 0;

    vector<int> result;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (distance[node] == K) {
            result.push_back(node);
        }

        for (int child : tree[node]) {
            if (distance[child] == -1) {
                distance[child] = distance[node] + 1;
                q.push(child);
            }
        }
    }

    return result;
}

/*8. Initially, you're given a tree. You get:
Update (u, v): Add edge between u and v
Query (): Return diameter of the tree*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

pair<int, int> bfs(int start, vector<int> tree[], int n) {
    vector<int> dist(n + 1, -1);
    queue<int> q;

    q.push(start);
    dist[start] = 0;

    int farthest = start;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int child : tree[node]) {
            if (dist[child] == -1) {
                dist[child] = dist[node] + 1;
                q.push(child);

                if (dist[child] > dist[farthest]) {
                    farthest = child;
                }
            }
        }
    }

    return {farthest, dist[farthest]};
}

/*9. You are given a tree and values for each node.

A path is good if the maximum value on the path is equal to both ends.
Return the number of good paths.
Hint: Union-Find with DSU on tree*/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class DSU {
public:
    vector<int> parent;

    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) parent[b] = a;
    }
};

/*10. You are given a tree and a color for each node.
Given a node v and integer k, find the longest path from v down such that the number of distinct
colors is at most k. */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<int, int> freq;
int maxLen = 0;

void dfs(int node, int parent, int k, vector<int> tree[], vector<int>& color) {
    freq[color[node]]++;

    if (freq.size() <= k) {
        maxLen = max(maxLen, (int)freq.size());
    }

    for (int child : tree[node]) {
        if (child != parent) {
            dfs(child, node, k, tree, color);
        }
    }

    freq[color[node]]--;
    if (freq[color[node]] == 0) {
        freq.erase(color[node]);
    }
}
