struct AhoCorasick {
  const static int A = 26;
  vector<array<int, A>> next;
  vector<int> fail, out, id;
  AhoCorasick() { node(); }
  int node() {
    next.emplace_back();
    fail.emplace_back();
    out.emplace_back();
    id.emplace_back(-1);
    return next.size() - 1;
  }
  int insert(const string &p, int idx) {
    int u = 0;
    for (char ch : p) {
      int c = ch - 'a';
      if (!next[u][c]) {
        next[u][c] = node();
      }
      u = next[u][c];
    }
    int &pid = id[u];
    return ~pid ? pid : (pid = idx);
  }
  void build() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int c = 0; c < A; c++) {
        int v = next[u][c];
        if (!v) {
          next[u][c] = next[fail[u]][c];
        } else {
          fail[v] = u ? next[fail[u]][c] : 0;
          out[v] = ~id[fail[v]] ? fail[v] : out[fail[v]];
          q.push(v);
        }
      }
    }
  }
  vector<vector<int>> match(const string &s, int m) {
    vector<vector<int>> ret(m);
    int n = s.size(), u = 0;
    for (int i = 0; i < n; i++) {
      u = next[u][s[i] - 'a'];
      for (int p = u; p; p = out[p]) {
        if (~id[p]) {
          ret[id[p]].push_back(i);
        }
      }
    }
    return ret;
  }
};