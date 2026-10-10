struct Node {
  int nxt[2]{}, cnt{};
  int& operator[](int c) { return nxt[c]; }
};
struct BinaryTrie {
  vector<Node> trie;
  static const int B = 29;
  BinaryTrie() { trie.emplace_back(); }
  void insert(int x) {
    int node = 0;
    for (int i = B; i >= 0; i--) {
      int bit = x >> i & 1;
      if (!trie[node][bit]) {
        trie[node][bit] = trie.size();
        trie.emplace_back();
      }
      node = trie[node][bit];
      trie[node].cnt++;
    }
  }
  void erase(int x) {
    int node = 0;
    for (int i = B; i >= 0; i--) {
      int bit = x >> i & 1;
      node = trie[node][bit];
      trie[node].cnt--;
    }
  }
  int max_xor(int x) {
    int node = 0;
    int64_t ans = 0;
    for (int i = B; i >= 0; i--) {
      int bit = x >> i & 1;
      if (trie[node][bit ^ 1] && trie[trie[node][bit ^ 1]].cnt) {
        node = trie[node][bit ^ 1];
        ans |= 1ll << i;
      } else {
        node = trie[node][bit];
      }
    }
    return ans;
  }
};