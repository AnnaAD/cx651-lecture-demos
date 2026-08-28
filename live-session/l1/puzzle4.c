long long mystery(long long a, long long b) {
  long long i = 0;
  while(a < b) {
    a += 3000000;
    b += 1000000;
    i += 1;
  }
  return i;
}
