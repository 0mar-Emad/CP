struct DSU {
  int comp;
  vector<int> par, sz;
  DSU() {}
  DSU(int n) { init(n); }
  void init(int n) {
    par.resize(n + 1);
    iota(par.begin(), par.end(), 0);
    sz.assign(n + 1, 1);
    comp = n;
  }
  int find(int v) {
    if (v == par[v]) return v;
    return par[v] = find(par[v]);
  }
  bool unite(int u, int v) {
    int x = find(u), y = find(v);
    if (x == y) return false;
    if (sz[y] > sz[x]) swap(x, y);
    par[y] = x;
    sz[x] += sz[y];
    comp--;
    return true;
  }
  bool same(int u, int v) {
    return find(u) == find(v);
  }
  int size(int v) {
    return sz[find(v)];
  }
};