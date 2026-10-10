struct Node {
  int nxt[26]{}, cnt{}, end{};
  int& operator[](int c) { return nxt[c]; }
};
struct Trie {
  vector<Node> trie;
  Trie() { trie.emplace_back(); }
  void insert(const string &s) { update(s, 1); }
  bool erase(const string &s) {
    int u = find(s);
    if (!u || !trie[u].end) return false;
    update(s, -1);
    return true;
  }
  int count_pfx(const string &s) {
    return trie[find(s)].cnt;
  } 
  int count_word(const string &s) {
    return trie[find(s)].end;
  }
  void update(const string &s, int d) {
    int u = 0;
    for (char ch : s) {
      int c = ch - 'a';
      if (!trie[u][c]) {
        trie[u][c] = trie.size();
        trie.emplace_back();
      }
      u = trie[u][c];
      trie[u].cnt += d;
    }
    trie[u].end += d;
  }
  int find(const string &s) {
    int u = 0;
    for (char ch : s) {
      int c = ch - 'a';
      if (!trie[u][c]) return 0;
      u = trie[u][c];
    }
    return u;
  }
};