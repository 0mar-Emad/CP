vector<int> in(n + 1), out(n + 1);
auto dfs = [&](auto &&dfs, int u, int p) {
  in[u] = timer++;
  for (int v : adj[u]) {
    if (v == p)
      continue;
    dfs(dfs, v, u);
  }
  out[u] = timer - 1;
}