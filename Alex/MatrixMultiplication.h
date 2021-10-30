// Use with ModInt
template<class T>
struct Matrix {
  int n, m;
  vector<vector<T>> a;
  Matrix(int n_ = 0, int m_ = 0) : n(n_), m(m_), a(n, vector<T>(m)) {}

  vector<T>& operator[](int row) { return a[row]; }

  Matrix<T> operator*(const Matrix<T> &b) const {
    Matrix<T> ret(n, b.m);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        T aux = a[i][j];
        for (int k = 0; k < b.m; ++k) {
          ret[i][k] = ret[i][k] + aux * b.a[j][k];
        }
      }
    }
    return ret;
  }

  Matrix<T>& operator=(const Matrix<T> &other) {
    n = other.n;
    m = other.m;
    a = other.a;
    return *this;
  }

  /// check exponent max value
  Matrix<T> Pow(int64_t e) const {
    auto ret = *this;
    auto curr = *this;
    --e;
    
    while (e) {
      if (e & 1) ret = ret * curr;
      curr = curr * curr;
      e /= 2;
    }
    return ret;
  }
};
