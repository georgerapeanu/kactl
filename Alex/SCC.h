struct SCC {
  int n;
  vector<bool> in_stk;
  vector<int> in, stk, comp;
  vector<vector<int>> adj;
  SCC(int n_) : n(n_), in_stk(n), in(n, -1), adj(n) {}

  void AddEdge(int a, int b) {
    adj[a].emplace_back(b);
  }

  void Callback() {
    // comp contains each SCC in reverse topological sort order
  }

  int timer = 0;
  int DFS(int node) {
    int low = in[node] = ++timer;
    stk.emplace_back(node);
    in_stk[node] = true;

    for (int &x : adj[node]) {
      if (in[x] == -1) {
        low = min(low, DFS(x));
      } else if (in_stk[x]) {
        low = min(low, in[x]);
      }
    }

    if (in[node] == low) {
      int x;
      comp.clear();
      do {
        x = stk.back(); stk.pop_back();
        comp.emplace_back(x);
        in_stk[x] = false;
      } while (x != node);
      Callback();
    }
    return low;
  }

  void Solve() {
    for (int i = 0; i < n; ++i) if (in[i] == -1) DFS(i);
  }
};