struct Edge {
  int v;
  Edge() : v(0) {}
  Edge(int w) : v(w) {}
  operator int() const { return v; }  
};
template<typename T, auto merge>
struct LCA {
  int n, lg;
  vector<int> dep;
  vector<vector<int>> anc; 
  vector<vector<T>> tbl;
  const vector<vector<pair<int, int>>> &adj;
  LCA(const auto &g, int root = 1) : adj(g) {
    n = adj.size();
    lg = __lg(n) + 1;
    dep.assign(n + 1, {});
    anc.assign(n + 1, vector<int>(lg));
    tbl.assign(n + 1, vector<T>(lg, T()));
    dfs(root);
  }
  void dfs(int u, int p = -1) {
    for (auto &[v, w] : adj[u]) {
      if (v == p) continue;
      dep[v] = dep[u] + 1;
      anc[v][0] = u;
      tbl[v][0] = w;
      for (int i = 1; i < lg; i++) {
        anc[v][i] = anc[anc[v][i - 1]][i - 1];
        tbl[v][i] = merge(tbl[v][i - 1], tbl[anc[v][i - 1]][i - 1]);
      }
      dfs(v, u);
    }
  }
  int kth(int u, int k) {
    if (k > dep[u]) return -1;
    for (int i = lg - 1; ~i; i--) {
      if (k >> i & 1) {
        u = anc[u][i];
      }
    }
    return u;
  }
  int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    v = kth(v, dep[v] - dep[u]);
    if (u == v) return u;
    for (int i = lg - 1; ~i; i--) {
      if (anc[u][i] != anc[v][i]) {
        u = anc[u][i];
        v = anc[v][i];
      }
    }
    return anc[u][0];
  }
  T get(int u, int k) {
    if (k > dep[u]) return T();
    T ans {};
    for (int i = lg - 1; ~i; i--) {
      if (k >> i & 1) {
        ans = merge(ans, tbl[u][i]);
        u = anc[u][i];
      }
    }
    return ans;
  }
  T query(int u, int v) {
    int l = lca(u, v);
    return merge(get(u, dep[u] - dep[l]), get(v, dep[v] - dep[l]));
  }
};
inline Edge merge(const Edge &a, const Edge &b) {
  // merge logic
}