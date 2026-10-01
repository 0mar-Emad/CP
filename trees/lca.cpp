struct LCA {
  int n, lg;
  vector<int> dep;
  vector<vector<int>> anc;
  const vector<vector<int>> &adj;
  LCA(const auto &g, int root = 1) : adj(g) {
    n = adj.size();
    lg = __lg(n) + 1;
    dep.assign(n + 1, {});
    anc.assign(n + 1, vector<int>(lg));
    dfs(root);
  }
  void dfs(int u, int p = -1) {
    for (int v : adj[u]) {
      if (v == p) continue;
      dep[v] = dep[u] + 1;
      anc[v][0] = u;
      for (int i = 1; i < lg; i++) {
        anc[v][i] = anc[anc[v][i - 1]][i - 1];
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
};