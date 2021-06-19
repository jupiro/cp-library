std::vector<int> Z_Algorighm(const std::string &S) {
	std::vector<int> Z_Array(S.size());
	Z_Array[0] = (int)S.size();
	int i = 1, j = 0;
	while (i < (int)S.size()) {
		while (i + j < (int)S.size() && S[j] == S[i + j]) ++j;
		Z_Array[i] = j;
		if (j == 0) { ++i; continue; }
		int k = 1;
		while (i + k < (int)S.size() && k + Z_Array[k] < j) Z_Array[i + k] = Z_Array[k], ++k;
		i += k; j -= k;
	}
	return Z_Array;
}