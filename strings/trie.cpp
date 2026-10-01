struct Node {
  int nxt[26] {}, cnt{};
  int& operator[](int c) { return nxt[c]; }
};
struct Trie {
  vector<Node> trie;
  Trie() { trie.emplace_back(); }
  void insert(const string &s) {
    int u = 0;
    for (char ch : s) {
      int c = ch - 'a';
      if (!trie[u][c]) {
        trie[u][c] = trie.size();
        trie.emplace_back();
      }
      u = trie[u][c];
      trie[u].cnt++;
    }
  }
  int query(const string &s) {
    int u = 0;
    for (char ch : s) {
      int c = ch - 'a';
      if (!trie[u][c]) {
        return 0;
      }
      u = trie[u][c];
    }
    return trie[u].cnt;
  }
};