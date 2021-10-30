struct AhoCorasick {
  struct Node {
    vector<Node*> son;
    vector<int> words;
    Node *fail;
    int freq;
    Node() : son(SIGMA, nullptr), fail(nullptr), freq(0) {}

    void Insert(int index, int pos, const string &s) {
      if (pos == (int)s.size()) {
        words.emplace_back(index);
        return;
      }
      int c = s[pos] - 'a';
      if (son[c] == nullptr) {
        son[c] = new Node();
      }
      son[c]->Insert(index, pos + 1, s);
    }
  };
  static const int SIGMA = 26; // Change SIGMA
  AhoCorasick() : n(0) {
    root = new Node();
  }
  int n;
  Node *root;
  vector<Node*> q;
  void Insert(int index, const string &word) {
    root->Insert(index, 0, word);
    ++n;
  }
  void GetFailLinks() {
    q = {root};
    root->fail = root;
    Node *curr, *fail;
    for (int it = 0; it < (int)q.size(); ++it) {
      curr = q[it];
      for (int i = 0; i < SIGMA; ++i) if (curr->son[i] != nullptr) {
        fail = curr->fail;
        while (fail != root && fail->son[i] == nullptr)
          fail = fail->fail;
        if (fail->son[i] != nullptr && fail->son[i] != curr->son[i])
          fail = fail->son[i];
        curr->son[i]->fail = fail;
        q.emplace_back(curr->son[i]);
      }
    }
    root->fail = nullptr;
  }
  vector<int> Count(const string &text) {
    Node *curr = root;
    for (auto &x : text) {
      int c = x - 'a';
      while (curr != root && curr->son[c] == nullptr)
        curr = curr->fail, assert(curr != nullptr);
      if (curr->son[c] != nullptr)
        curr = curr->son[c];
      ++curr->freq;
    }
    vector<int> ans(n);
    for (int it = (int)q.size() - 1; it >= 0; --it) {
      curr = q[it];
      if (curr->fail != nullptr) curr->fail->freq += curr->freq;
      for (int &x : curr->words)
        ans[x] = curr->freq;
      curr->freq = 0;
    }
    return ans;
  }
};
