template<class T, class F = function<T(const T&, const T&)>>
struct Sparse2D {
  int n, m;
  F func;
  vector<vector<vector<T>>> st;
  Sparse2D(const vector<vector<T>> &a, const F &f) : 
    n(a.size()), m(a[0].size()), func(f) {
    
    int logn = 32 - __builtin_clz(min(n, m));
    st.resize(logn);
    st[0] = a;
    for (int bit = 1; bit < logn; ++bit) {
      st[bit].resize(n - (1 << bit) + 1);
      for (int i = 0; i + (1 << bit) - 1 < n; ++i) {
        st[bit][i].resize(m - (1 << bit) + 1);
        for (int j = 0; j + (1 << bit) - 1 < m; ++j) {
          int l = 1 << (bit - 1);
          st[bit][i][j] = st[bit - 1][i][j];
          st[bit][i][j] = func(st[bit][i][j], st[bit - 1][i][j + l]);
          st[bit][i][j] = func(st[bit][i][j], st[bit - 1][i + l][j]);
          st[bit][i][j] = func(st[bit][i][j], st[bit - 1][i + l][j + l]);
        }
      }
    }
  }
  T Get(int r, int c, int l) const {
    assert(0 <= r && r + l - 1 < n && 0 <= c && c + l - 1 < m);
    int lg = 31 - __builtin_clz(l);
    T ans = st[lg][r][c];
    ans = func(ans, st[lg][r][c + l - (1 << lg)]);
    ans = func(ans, st[lg][r + l - (1 << lg)][c]);
    ans = func(ans, st[lg][r + l - (1 << lg)][c + l - (1 << lg)]);
    return ans;
  }
};

