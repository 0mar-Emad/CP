struct DSU {
  int comp;
  vector<int> par, sz, snap;
  vector<pair<int, int>> hist;
  DSU() {}
  DSU(int n) { init(n); }
  void init(int n) {
    par.resize(n + 1);
    iota(par.begin(), par.end(), 0);
    sz.assign(n + 1, 1);
    hist.clear();
    snap.clear(); 
    comp = n;
  }
  int find(int v) {
    while (v != par[v]) {
      v = par[v];
    }
    return v;
  }
  bool unite(int u, int v) {
    int x = find(u), y = find(v);
    if (x == y) return false;
    if (sz[y] > sz[x]) swap(x, y);
    hist.emplace_back(y, sz[x]);
    par[y] = x;
    sz[x] += sz[y];
    comp--;
    return true;
  }
  void rollback() {
    if (snap.empty()) return;
    int check = snap.back();
    snap.pop_back();
    while (hist.size() > check) {
      auto [y, old_sz] = hist.back();
      hist.pop_back();
      int x = par[y];
      par[y] = y;
      sz[x] = old_sz;
      comp++;
    }
  }
  void persist() {
    snap.push_back(hist.size());
  }
  bool same(int u, int v) {
    return find(u) == find(v);
  }
  int size(int v) {
    return sz[find(v)];
  }
};