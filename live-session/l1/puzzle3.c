long long mystery(long long a) {
  long long final = 0;
  for(long long  i = 0; i < 42; i+=a) {
      final += i;
  }
  return final;
}
