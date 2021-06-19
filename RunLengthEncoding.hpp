namespace KKT89
{
  template<typename T>
  std::vector<std::pair<T, int>> RunLengthEncoding(std::vector<T>& v) {
    std::vector<std::pair<T, int>> ret;
    for (int i = 0; i < (int)v.size(); i++) {
      if (ret.empty() or ret.back().first != v[i]) {
        ret.emplace_back(v[i], 1);
      }
      else {
        ret.back().second += 1;
      }
    }
    return ret;
  }

  std::vector<std::pair<char, int>> RunLengthEncoding(std::string& v) {
    std::vector<std::pair<char, int>> ret;
    for (int i = 0; i < (int)v.size(); i++) {
      if (ret.empty() or ret.back().first != v[i]) {
        ret.emplace_back(v[i], 1);
      }
      else {
        ret.back().second += 1;
      }
    }
    return ret;
  }
}