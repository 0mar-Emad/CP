vector<short> spf(N + 5);
for (int i = 2; i * i <= N; i++) {
  if (spf[i]) {
    continue;
  }
  for (int j = i * i; j <= N; j += i) {
    if (!spf[j]) {
      spf[j] = i;
    }
  }
}