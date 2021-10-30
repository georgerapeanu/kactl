struct MaxFlow {
  int n, source, sink, flow;
  vector<int> parent;
  vector<vector<int>> adj, capacity;
  MaxFlow(int n_, int source_, int sink_) : 
    n(n_), source(source_), sink(sink_), flow(0), parent(n), adj(n), 
      capacity(n, vector<int>(n)) {}
  void AddEdge(int u, int v, int cap) {
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
    capacity[u][v] += cap;
  }
  bool CanIncreaseFlow() {
    fill(parent.begin(), parent.end(), -1);
    parent[source] = -2;
    vector<int> q = {source};
    for (int i = 0; i < (int)q.size(); ++i) {
      int node = q[i];
      for (int &x : adj[node]) {
        if (parent[x] == -1 && capacity[node][x]) {
          parent[x] = node;
          q.emplace_back(x);
        }
      }
    }
    return parent[sink] != -1;
  }
  int GetMaxFlow() {
    while (CanIncreaseFlow()) {
      int node = sink;
      int add_flow = (int)1e9;
      while (node != source) {
        add_flow = min(add_flow, capacity[parent[node]][node]);
        node = parent[node];
      }
      node = sink;
      while (node != source) {
        capacity[parent[node]][node] -= add_flow;
        capacity[node][parent[node]] += add_flow;
        node = parent[node];
      }
      flow += add_flow;
    }
    return flow;
  }
};
