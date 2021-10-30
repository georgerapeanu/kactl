struct Fenwick {
  int n;
  vector<int> t;
  Fenwick(int n_) : n(n_), t(n + 1) {}
  inline int lsb(int x) { return x & -x; }
  void Update(int pos, int val) {
    for (++pos; pos <= n; pos += lsb(pos)) t[pos] += val;
  }
  int Query(int pos) {
    int ans = 0;
    for (++pos; pos; pos -= lsb(pos)) ans += t[pos];
    return ans;
  }
  int Query(int l, int r) {
    return Query(r) - Query(l - 1);
  }
  int Search(int sum) {
    int pow = 1, i;
    while (pow < n) pow <<= 1;
    for (i = 0; pow >= 1; pow >>= 1) {
      if (i + pow <= n) {
        if (sum > bit[i + pow]) {
          sum -= bit[i + pow];
          i += pow;
        }
      }
    }
    return i + 1;
  }
};