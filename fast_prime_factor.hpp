const int MAX = (int)3e5;
bool IsPrime[MAX];
int MinFactor[MAX]; 
void preprocess(int n = MAX) {
  for (int i = 0; i < n; ++i) IsPrime[i] = true, MinFactor[i] = -1;
  IsPrime[0] = false; IsPrime[1] = false;
  MinFactor[0] = 0; MinFactor[1] = 1;
  for (int i = 2; i < n; ++i) {
    if (IsPrime[i]) {
      MinFactor[i] = i;
      for (int j = i * 2; j < n; j += i) {
        IsPrime[j] = false;
        if (MinFactor[j] == -1) MinFactor[j] = i;
      }
    }
  }
}

std::vector<std::pair<int, int>> fast_prime_factor(int n) {
  std::vector<std::pair<int, int>> res;
  while (n != 1) {
    int prime = MinFactor[n];
    int exp = 0;
    while (MinFactor[n] == prime) {
      ++exp;
      n /= prime;
    }
    res.emplace_back(prime, exp);
  }
  return res;
}