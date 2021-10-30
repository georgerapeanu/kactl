#include <bits/stdc++.h>
using namespace std;

const int SIGMA = 26;

struct PalTree {
  struct Node {
    int len = 0, fail = 1;
    long long cnt = 0;
    vector<int> son = vector<int>(SIGMA, -1);
  };
  int node = 1;
  vector<Node> t;
  string s;
  PalTree() : t(2) {
    t[1].len = -1;
  }
  
  int Alloc() {
    t.emplace_back();
    return t.size() - 1;
  }

  void AddChar(char c) {
    c -= 'a';
    s += c;
    while (node != 1 && (t[node].len == (int)s.size() - 1 || s.end()[-2 - t[node].len] != c))
      node = t[node].fail;

    if (t[node].son[c] != -1) {
      node = t[node].son[c];
      t[node].cnt += 1;
      return;
    }

    int son = Alloc();
    t[node].son[c] = son;

    t[son].len = t[node].len + 2;
    t[son].fail = t[node].fail;
    t[son].cnt = 1;
    int &fail = t[son].fail;
    node = son;

    if (t[node].len == 1) {
      fail = 0;
      return;
    }

    while (fail != 1) {
      if (s.end()[-2 - t[fail].len] == c) {
        break;
      }
      fail = t[fail].fail;
    }
    fail = t[fail].son[c];
  }

  long long Get() {
    long long res = 0;
    for (int i = t.size() - 1; i > 1; --i) {
      res += t[i].cnt;
      t[t[i].fail].cnt += t[i].cnt;
    }
    return res;
  }
};

int main() {
  ifstream cin("pscpld.in");
  ofstream cout("pscpld.out");

  string s; getline(cin, s);

  PalTree pt;
  for (auto &c : s) {
    pt.AddChar(c);
  }

  cout << pt.Get() << endl;
}
