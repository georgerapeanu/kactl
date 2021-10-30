using Int = ModInt<int64_t>;

namespace Math {
  Int Pow(Int b, int64_t e) {
    if (e < 0) e += MOD - 1;
    Int ret = 1;
    while (e) {
      if (e & 1) ret *= b;
      b *= b;
      e >>= 1;
    }
    return ret;
  }
  
  vector<Int> fact, tcaf;
  void Precalc(int n) {
    fact.resize(n);
    tcaf.resize(n);
    fact[0] = 1;
    for (int i = 1; i < n; ++i) fact[i] = fact[i - 1] * i;
    tcaf[n - 1] = Pow(fact[n - 1], -1);
    for (int i = n - 2; i >= 0; --i) tcaf[i] = tcaf[i + 1] * (i + 1);
  }
  
  Int Inv(int x) {
    return tcaf[x] * fact[x - 1];
  }
  
  Int Choose(Int n, Int k) {
    if ((n - k)() < k()) k = n - k;
    Int ans = 1;
    for (int i = n(), j = 0; j < k(); ++j, --i) {
      ans *= i;
    }
    for (int i = 1; i <= k(); ++i) {
      ans *= Inv(i);
    }
    return ans;
  }
}
