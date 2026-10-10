const int N = 1e5 + 5;
vector<vector<int>> adj;
int sz[N], big[N], a[N], ans[N];
// what ever DS i'm using
void pre(int u, int p) {
  sz[u] = 1;
  for (int v : adj[u]) {
    if (v == p) continue;
    pre(v, u);
    sz[u] += sz[v];
    if (!big[u] || sz[v] > sz[big[u]]) {
      big[u] = v;
    }
  }
}
void update(int x, int d) {
  // update logic
}
void add(int u, int p, int d) {
  update(a[u], d);
  for (int v : adj[u]) {
    if (v == p) continue;
    add(v, u, d);
  }
}
void dfs(int u, int p, bool keep) {
  for (int v : adj[u]) {
    if (v == p || v == big[u]) continue;
    dfs(v, u, 0);
  }
  if (big[u]) {
    dfs(big[u], u, 1);
  }
  update(a[u], 1);
  for (int v : adj[u]) {
    if (v == p || v == big[u]) continue;
    add(v, u, 1);
  }
  // ans[u] = ??, update ans
  if (!keep) {
    add(u, p, -1);
  }
}