struct AhoCorasick {
  struct Node {
    int link = -1, exit = -1;
    int p; char pc;
    vector<int> words, next, go;
    Node(int p_ = -1, char pc_ = '#') : p(p_), pc(pc_), next(SIGMA, -1), go(SIGMA, -1) {}
  };
  static const char fst_ch = 'a';
  static const int SIGMA = 26;
 
  int n = 0;
  vector<Node> t = vector<Node>(1);
 
  int Exit(int node) {
    if (t[node].exit == -1) {
      if (!t[node].words.empty()) t[node].exit = node;
      else t[node].exit = node == 0 ? 0 : Exit(Link(node));
    }
    return t[node].exit;
  }
 
  int Link(int node) {
    if (t[node].link == -1) {
      if (node == 0 || t[node].p == 0) t[node].link = 0;
      else t[node].link = Go(Link(t[node].p), t[node].pc);
    }
    return t[node].link;
  }
 
  int Go(int node, char ch) {
    int c = ch - fst_ch;
    if (t[node].go[c] == -1) {
      if (t[node].next[c] != -1) t[node].go[c] = t[node].next[c];
      else t[node].go[c] = node == 0 ? 0 : Go(Link(node), ch);
    }
    return t[node].go[c];
  }
 
  void Add(const string &s, int id) {
    ++n;
    int node = 0;
    for (auto &ch : s) {
      int c = ch - fst_ch;
      if (t[node].next[c] == -1) {
        t[node].next[c] = t.size();
        t.emplace_back(node, ch);
      }
      node = t[node].next[c];
    }
    t[node].words.emplace_back(id);
  }
 
  vector<int> Count(const string &s) {
    vector<int> ans(n);
    int node = 0;
    for (auto &c : s) {
      node = Go(node, c);
      for (int aux = node; aux; aux = Exit(Link(aux))) {
        for (int &id : t[aux].words) {
          ++ans[id];
        }
      }
    }
    return ans;
  }
};
