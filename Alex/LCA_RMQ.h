namespace LCA_ {
  int n, maxlog;
  vector<int> in, euler, level;
  vector<vector<int>> st;
  void Init(int n_) {
    n = n_;
    maxlog = 32 - __builtin_clz(2 * n);
    in.resize(n);
    euler.resize(2 * n);
    level.resize(n);
    st.resize(maxlog);
  }
  void Precompute() {
    st[0] = euler;
    for (int bit = 1; bit < maxlog; ++bit) {
      st[bit].resize(2 * n - (1 << bit) + 1);
      for (int i = 0; i + (1 << bit) - 1 < 2 * n; ++i) {
        int a = st[bit - 1][i], b = st[bit - 1][i + (1 << bit - 1)];
        if (level[a] > level[b]) a = b;
        st[bit][i] = a;
      }
    }
  }
  int LCA(int x, int y) {
    if (in[x] > in[y]) swap(x, y);
    int lg = 31 - __builtin_clz(in[y] - in[x] + 1);
    int a = st[lg][in[x]], b = st[lg][in[y] - (1 << lg) + 1];
    if (level[a] > level[b]) a = b;
    return a;
  }
};
using namespace LCA_;

void DFS(int node, const vector<vector<int>> &adj) {
  static int timer = 0;
  euler[timer] = node;
  in[node] = timer++;
  for (auto &x : adj[node]) {
    level[x] = level[node] + 1;
    DFS(x, adj);
    euler[timer++] = node;
  }
}
