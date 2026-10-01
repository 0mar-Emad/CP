struct VirtualTree {
  int n, lg, t;
  vector<int> dep, sz, in, out, used;
  vector<vector<int>> anc, vadj;
  const vector<vector<int>> &adj;
  VirtualTree(const auto &g, int root = 1) : adj(g) {
    n = adj.size();
    lg = __lg(n) + 2;
    dep.assign(n + 1, {});
    sz.assign(n + 1, {});
    in.assign(n + 1, {});
    out.assign(n + 1, {});
    vadj.assign(n + 1, {});
    anc.assign(n + 1, vector<int>(lg));
    init(root);
  }
  void init(int root) {
    t = 0;
    vector<pair<int, int>> stk;
    stk.emplace_back(root, 0);
    vector<bool> vis(n + 1);
    vis[root] = true;
    anc[root][0] = root;
    out[0] = 2e9;
    while (!stk.empty()) {
      auto &[u, idx] = stk.back();
      if (idx == 0) {
        in[u] = ++t;
        sz[u] = 1;
      };
      if (idx < adj[u].size()) {
        int v = adj[u][idx++];
        if (!vis[v]) {
          vis[v] = true;
          anc[v][0] = u;
          dep[v] = dep[u] + 1;
          stk.emplace_back(v, 0);
        }
      } else {
        out[u] = ++t;
        if (anc[u][0] != u) {
          sz[anc[u][0]] += sz[u];
        }
        stk.pop_back();
      }
    }
    for (int i = 1; i < lg; i++) {
      for (int v = 1; v <= n; v++) {
        anc[v][i] = anc[anc[v][i - 1]][i - 1];
      }
    }
  }
  bool isAnc(int u, int v) {
    return in[u] <= in[v] && out[v] <= out[u];
  }
  int lca(int u, int v) {
    if (isAnc(u, v)) return u;
    if (isAnc(v, u)) return v;
    for (int i = lg - 1; ~i; i--) {
      if (!isAnc(anc[u][i], v)) { 
        u = anc[u][i];
      }
    }
    return anc[u][0];
  }
  int build(vector<int> vt) {
    for (int u : used) vadj[u].clear();
    used.clear();
    sort(vt.begin(), vt.end(), [&](int a, int b) { return in[a] < in[b]; });
    int k = vt.size();
    for (int i = 0; i + 1 < k; i++) {
      vt.push_back(lca(vt[i], vt[i + 1]));
    }
    sort(vt.begin(), vt.end(), [&](int a, int b) { return in[a] < in[b]; });
    vt.erase(unique(vt.begin(), vt.end()), vt.end());
    vector<int> stk;
    stk.push_back(vt[0]);
    used.push_back(vt[0]);
    for (int i = 1; i < vt.size(); i++) {
      int u = vt[i];
      used.push_back(u);
      while (!isAnc(stk.back(), u)) {
        stk.pop_back();
      }
      vadj[stk.back()].push_back(u);
      stk.push_back(u);
    }
    return vt[0];
  }
};