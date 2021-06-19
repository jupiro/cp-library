template<typename T>
std::vector<std::pair<T, int>> prime_factor(T a) {
	std::vector<std::pair<T, int>> ret;
	for (int i = 2; i * i <= a; i++) {
		int cnt = 0;
		while (a % i == 0 && a != 0) {
			cnt++;
			a /= i;
		}
		if (cnt > 0) ret.emplace_back(i, cnt);
	}
	if (a != 1) {
		ret.emplace_back(a, 1);
	}
	return ret;
}