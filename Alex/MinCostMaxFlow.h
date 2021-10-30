class MinCostMaxFlow {
  struct Edge {
    int to, cap, flow, cost, nxt;
  };
 
  int n, src, dst;
  pair<int, int> ans;
  vector<Edge> edges;
  vector<int> adj, dist, new_dist, aux, par;
 
  void addEdge(int from, int to, int cap, int cost) {
    edges.emplace_back(Edge{to, cap, 0, cost, adj[from]});
    adj[from] = edges.size() - 1;
  }
 
  void BellmanFord() {
    fill(dist.begin(), dist.end(), INF);
    dist[src] = 0;
    vector<bool> in_queue(n);
    vector<int> q = {src};
 
    for (int it = 0; it < (int)q.size(); ++it) {
      int node = q[it];
      in_queue[node] = false;
 
      for (int eid = adj[node]; eid != -1; eid = edges[eid].nxt) {
        auto &e = edges[eid];
        if (e.flow == e.cap) continue;
        if (dist[e.to] > dist[node] + e.cost) {
          dist[e.to] = dist[node] + e.cost;
          if (!in_queue[e.to]) {
            in_queue[e.to] = true;
            q.emplace_back(e.to);
          }
        }
      }
    }
  }
 
  bool Dijkstra() {
    fill(par.begin(), par.end(), -1);
    fill(aux.begin(), aux.end(), INF);
    fill(new_dist.begin(), new_dist.end(), INF);
 
    static priority_queue<pair<int, int>,
      vector<pair<int, int>>,
        greater<pair<int, int>>> pq;
 
    pq.emplace(0, src);
    aux[src] = new_dist[src] = 0;
    
    while (!pq.empty()) {
      int cost, node; tie(cost, node) = pq.top(); pq.pop();
      if (cost != aux[node]) continue;
 
      for (int eid = adj[node]; eid != -1; eid = edges[eid].nxt) {
        auto &e = edges[eid];
        if (e.flow == e.cap) continue;
        int new_cost = e.cost + dist[node] - dist[e.to];
 
        if (aux[e.to] > aux[node] + new_cost) {
          aux[e.to] = aux[node] + new_cost;
          new_dist[e.to] = new_dist[node] + e.cost;
          pq.emplace(aux[e.to], e.to);
          par[e.to] = eid ^ 1;
        }
      }
    }
 
    swap(dist, new_dist);
    return par[dst] != -1;
  }
 
  void IncreaseFlow() {
    int node = dst, flow = INF;
    while (node != src) {
      int e = par[node] ^ 1;
      flow = min(flow, edges[e].cap - edges[e].flow);
      node = edges[par[node]].to;
    }
 
    ans.first += flow;
    ans.second += flow * dist[dst];
 
    node = dst;
    while (node != src) {
      int e = par[node] ^ 1;
      edges[e].flow += flow;
      edges[e ^ 1].flow -= flow;
      node = edges[par[node]].to;
    }
  }
 
public:
  MinCostMaxFlow(int n_) :
    n(n_), adj(n, -1), dist(n), new_dist(n), aux(n), par(n, -1) {}
 
  void AddEdge(int from, int to, int cap, int cost) {
    addEdge(from, to, cap, cost);
    addEdge(to, from, 0, -cost);
  }
 
  pair<int, int> Compute(int src, int dst) {
    this->src = src; this->dst = dst;
    BellmanFord();
 
    ans = {0, 0};
    while (Dijkstra()) {
      IncreaseFlow(); 
    }
 
    return ans;
  }
};