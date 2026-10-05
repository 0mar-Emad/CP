auto valid = [&](int x, int y) {
  return x >= 0 && y >= 0 && x < n && y < m 
    && grid[x][y] == '.' && !vis[x][y];
};