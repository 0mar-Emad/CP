map<int, int> primeFact(int n) {
  map<int, int> mp;
  for (int i = 2; i * i <= n; i++) {
    while (n % i == 0) {
      n /= i;
      mp[i]++;
    }
  }
  if (n > 1) {
    mp[n]++;
  }
  return mp;
}