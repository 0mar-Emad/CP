auto bfs = [&](int start) {
  queue<int> q;
  vector<int> dist(n + 1, -1);
  q.push(start);
  dist[start] = 0;
  int far = start;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : adj[u]) {
      if (~dist[v]) continue;
      dist[v] = dist[u] + 1;
      q.push(v);
      if (dist[v] > dist[far]) {
        far = v;
      }
    }
  }
  return make_pair(far, dist[far]);
};
auto [far, _] = bfs(1);
auto [end, diameter] = bfs(far);