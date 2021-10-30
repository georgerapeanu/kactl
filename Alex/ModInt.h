template<class T>
struct ModInt {
  T n;
  ModInt(T n_ = 0) : n(n_ % MOD) {
    while (n < 0) n += MOD;
  }
  ModInt operator+(const ModInt &other) { return n + other.n; }
  ModInt operator-(const ModInt &other) { return n - other.n; }
  ModInt operator*(const ModInt &other) { return n * other.n; }
  ModInt& operator+=(const ModInt &other) { return *this = *this + other; }
  ModInt& operator-=(const ModInt &other) { return *this = *this - other; }
  ModInt& operator*=(const ModInt &other) { return *this = *this * other; }
  T operator()() { return n; }
};
