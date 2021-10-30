struct Dinic {
  struct Edge {
    int to, cap, flow, nxt;
    Edge(int to_ = 0, int cap_ = 0, int flow_ = 0, int nxt_ = 0) :
      to(to_), cap(cap_), flow(flow_), nxt(nxt_) {}
  };
  int n, src, dest;
  vector<int> adj, idx, dist;
  vector<Edge> edges;
  Dinic(int n_) : n(n_), adj(n, -1), dist(n) {} 
  void AddEdge(int from, int to, int cap) {
    edges.emplace_back(to, cap, 0, adj[from]);
    adj[from] = edges.size() - 1;
    edges.emplace_back(from, 0, 0, adj[to]);
    adj[to] = edges.size() - 1;
  }
  bool BFS() {
    static vector<int> q;
    fill(dist.begin(), dist.end(), -1);
    q = {src};
    dist[src] = 0;
    for (int it = 0; it < (int)q.size(); ++it) {
      int node = q[it];
      for (int id = adj[node]; id != -1; id = edges[id].nxt) {
        auto &e = edges[id];
        if (dist[e.to] == -1 && e.flow < e.cap) {
          dist[e.to] = dist[node] + 1;
          q.emplace_back(e.to);
        }
      }
    }
    return dist[dest] != -1;
  }
  int DFS(int node, int flow) {
    if (flow == 0) return 0;
    if (node == dest) return flow;
 
    for (int &id = idx[node]; id != -1; id = edges[id].nxt) {
      auto &e = edges[id];
      if (dist[e.to] == dist[node] + 1) {
        if (int ret = DFS(e.to, min(flow, e.cap - e.flow))) {
          edges[id].flow += ret;
          edges[id ^ 1].flow -= ret;
          return ret;
        }
      }
    }
    return 0;
  }
  int GetFlow(int source, int sink) {
    src = source, dest = sink; int flow = 0;
    while (BFS()) {
      idx = adj;
      while (int add = DFS(src, (int)1e9 + 5)) {
        flow += add;
      }
    }
    return flow;
  }
};