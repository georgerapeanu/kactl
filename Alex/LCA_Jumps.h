/* Structure for computing the Lowest Common Ancestor
 * of 2 nodes in a rooted tree
 * Implementation based on linear memory binary jumps
 * Usage:
 * LCA lca(n); // declares the structure for a tree of size n
 * lca.AddEdge(a, b); // adds an edge in the tree
 * lca.DFS(); // performs a DFS for precomputing the links
 * lca(a, b); // returns the LCA of a and b in O(logN) time
 * Complexity: O(N) precomputation + O(logN) / query
*/

struct LCA {
  int n;
  vector<vector<int>> adj;
  vector<int> in, par, link, depth;

  LCA(int n_) : n(n_), adj(n), in(n), par(n, -1), link(n), depth(n) {}

  void AddEdge(int a, int b) {
    adj[a].emplace_back(b);
    adj[b].emplace_back(a);
  }

  int timer = 0;
  void DFS(int node = 0) {
    in[node] = timer++;
    if (par[node] == -1) {
      par[node] = link[node] = 0;
    } else {
      int p = par[node], l = link[p];
      int d0 = depth[p] - depth[l];
      int d1 = depth[l] - depth[link[l]];
      if (d0 == d1) link[node] = link[l];
      else link[node] = par[node];
    }

    for (auto &x : adj[node]) {
      if (x == par[node]) continue;
      depth[x] = 1 + depth[node];
      par[x] = node;
      DFS(x);
    }
  }

  int operator()(int a, int b) const {
    while (depth[a] != depth[b]) {
      if (depth[a] < depth[b]) swap(a, b); 
      if (depth[link[a]] >= depth[b]) a = link[a];
      else a = par[a];
    }
    if (a == b) return a;
    while (a != b) {
      if (link[a] != link[b]) a = link[a], b = link[b];
      else a = par[a], b = par[b];
    }
    return a;
  }
};