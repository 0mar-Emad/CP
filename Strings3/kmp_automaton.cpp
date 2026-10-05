vector<int> kmp(const string &s) {
  int n = s.size();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j && s[i] != s[j]) {
      j = pi[j - 1];
    }
    j += (s[i] == s[j]);
    pi[i] = j;
  }
  return pi;
}
vector<vector<int>> automaton(string s) {
  s += "#";
  int n = s.size();
  auto pi = kmp(s);
  vector aut(n, vector<int>(26));
  aut[0][s[0] - 'a'] = 1;
  for (int i = 1; i < n; i++) {
    for (int c = 0; c < 26; c++) {
      if (c == s[i] - 'a') {
        aut[i][c] = i + 1;
      } else {
        aut[i][c] = aut[pi[i - 1]][c];
      }
    }
  }
  return aut;
}