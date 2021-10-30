
struct BigInteger {
  static const int NMAX = 800;
  static const int BASE = (int)1e6;
  static const int LOGBASE = 6;
  int v[NMAX];
  BigInteger () {
    memset (v, 0, sizeof (v));
  }
  void Read();
  void Print();
  void operator = (int x);
  void operator = (BigInteger other);
  BigInteger operator + (const BigInteger &other) const;
  BigInteger operator * (int x) const;
  BigInteger operator - (BigInteger &other) const;
  BigInteger operator / (int x);
  bool operator<(const BigInteger &other) const {
    if (v[0] != other.v[0]) return v[0] < other.v[0];
    for (int i = v[0]; i > 0; --i) {
      if (v[i] != other.v[i]) {
        return v[i] < other.v[i];
      }
    }
    return false;
  }
  bool operator==(const BigInteger &other) const {
    return v == other.v;
  }
  BigInteger(int x) {
    memset(v, 0, sizeof(v));
    *this = x;
  }
};

void BigInteger::Read() {
  string s; getline(cin, s);
  int n = s.size();
  int curr = 0, p = 1;
  for (int i = n - 1; i >= 0; --i, p *= 10) {
    curr = curr + p * (s[i] - '0');
    if (p >= BASE) {
      v[++v[0]] = curr % BASE;
      curr /= BASE;
      p = 1;
    }
  }
  v[++v[0]] = curr;
}

void BigInteger::Print () {
  cout << v[v[0]];
  for (int i = v[0] - 1; i >= 1; --i) {
    cout << setw(LOGBASE) << setfill('0') << v[i];
  }
  cout << '\n';
}

void BigInteger::operator = (int x) {
  v[0] = 0;

  while (x) {
    v[++v[0]] = x % BASE;
    x /= BASE;
  }

//    return *this;
}

void BigInteger::operator = (BigInteger other) {
  for (int i = 0; i <= other.v[0]; ++i) {
    v[i] = other.v[i];
  }

//    return *this;
}

BigInteger sum; // only here
BigInteger BigInteger::operator + (const BigInteger &other) const {
  sum = 0;
  int temp = 0, i;

  for (i = 1; i <= v[0] || i <= other.v[0] || temp; ++i, temp /= BASE) {
    sum.v[i] = (temp += v[i] + other.v[i]) % BASE;
  }

  sum.v[0] = i - 1;
  return sum;
} 

BigInteger mult; // only here
BigInteger BigInteger::operator * (int x) const {
  mult = 0;
  int temp = 0, i;

  for (i = 1; i <= v[0] || temp; ++i, temp /= BASE) {
    mult.v[i] = (temp += v[i] * x) % BASE;
  }

  mult.v[0] = i - 1;
  return mult;
}

BigInteger diff;
BigInteger BigInteger::operator - (BigInteger &other) const {
  diff = *this;
  int temp = 0, i;
  for (i = 1; i <= diff.v[0]; ++i) {
    diff.v[i] -= ((i <= other.v[0]) ? other.v[i] : 0) + temp;
    diff.v[i] += (temp = diff.v[i] < 0) * BASE;
  }

  for (; diff.v[0] > 1 && !diff.v[diff.v[0]]; --diff.v[0]);
  return diff;
}

BigInteger divv;
BigInteger BigInteger::operator / (int x) {
  divv = *this;
  int temp = 0, i;
  for (i = divv.v[0]; i > 0; --i, temp %= x) {
    divv.v[i] = (temp = temp * BASE + divv.v[i]) / x;
  }
  for (; divv.v[0] > 1 && !divv.v[divv.v[0]]; --divv.v[0]);
  return divv;
}


/*
struct BigInteger {
  static const int NMAX = 10000;
  static const int BASE = 10;
  int v[NMAX];
  BigInteger () {
    memset (v, 0, sizeof (v));
  }
  void print();
  void operator = (int x);
  void operator = (BigInteger other);
  int &operator[] (int index) {
    return v[index];
  }
  BigInteger operator + (BigInteger &other);
  BigInteger operator * (int x);
  BigInteger operator - (BigInteger &other);
  BigInteger operator / (int x);
  BigInteger operator / (BigInteger &other);
  BigInteger operator % (BigInteger &other);
};

void BigInteger::print() {
  for (int i = v[0]; i >= 1; --i) {
    printf ("%d", v[i]);
  }
}

void BigInteger::operator = (int x) {
  v[0] = 0;

  while (x) {
    v[++v[0]] = x % BASE;
    x /= BASE;
  }

//    return *this;
}

void BigInteger::operator = (BigInteger other) {
  for (int i = 0; i <= other[0]; ++i) {
    v[i] = other[i];
  }

//    return *this;
}

BigInteger sum; // only here
BigInteger BigInteger::operator + (BigInteger &other) {
  sum = 0;
  int temp = 0, i;

  for (i = 1; i <= v[0] || i <= other[0] || temp; ++i, temp /= BASE) {
    sum[i] = (temp += v[i] + other[i]) % BASE;
  }

  sum[0] = i - 1;
  return sum;
}

BigInteger mult; // only here
BigInteger BigInteger::operator * (int x) {
  mult = 0;
  int temp = 0, i;

  for (i = 1; i <= v[0] || temp; ++i, temp /= BASE) {
    mult[i] = (temp += v[i] * x) % BASE;
  }

  mult[0] = i - 1;
  return mult;
}

BigInteger diff;
BigInteger BigInteger::operator - (BigInteger &other) {
  diff = *this;
  int temp = 0, i;
  for (i = 1; i <= diff[0]; ++i) {
    diff[i] -= ((i <= other[0]) ? other[i] : 0) + temp;
    diff[i] += (temp = diff[i] < 0) * BASE;
  }

  for (; diff[0] > 1 && !diff[diff.v[0]]; --diff[0]);
  return diff;
}

BigInteger divv;
BigInteger BigInteger::operator / (int x) {
  divv = *this;
  int temp = 0, i;
  for (i = divv[0]; i > 0; --i, temp %= x) {
    divv[i] = (temp = temp * BASE + divv[i]) / x;
  }
  for (; divv[0] > 1 && !divv[divv.v[0]]; --divv[0]);
  return divv;
}

BigInteger modd;
BigInteger BigInteger::operator / (BigInteger &other) {
  modd[0] = 0;
  divv[0] = v[0];

  for (int i = v[0]; i >= 1; --i) {
    modd = modd * 10;
    modd[1] = v[i];
    divv[i] = 0;
    while (other <= modd) {
      ++divv[i];
      modd = modd - other;
    }
  }
  while (!divv[divv[0]] && divv[0] > 1) --divv[0];
  return divv;
}

BigInteger BigInteger::operator % (BigInteger &other) {
  modd[0] = 0;

  for (int i = v[0]; i >= 1; --i) {
    modd = modd * 10;
    modd[1] = v[i];
    while (other <= modd) {
      modd = modd - other;
    }
  }
  return modd;
}
