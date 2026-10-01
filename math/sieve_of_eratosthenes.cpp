bitset<1000000> comp;
void sieve(int n) {
  comp[0] = comp[1] = 1;
  for (int i = 2; i * i <= n; i++) {
    if (comp[i]) {
      continue;
    }
    for (int j = i * i; j <= n; j += i) {
      comp[j] = 1;
    }
  }
}