template<int char_size>
struct TrieNode {
  std::array<int, char_size> nxt;
  int cnt;
  std::vector<int> accept;
  TrieNode() :cnt(0) { std::fill(nxt.begin(), nxt.end(), -1); }
};

template<int char_size>
struct Trie {
  using Node = TrieNode<char_size>;
  std::vector<Node> nodes;
  int root;

  Trie() :root(0) { nodes.emplace_back(Node()); }
  void add(const std::vector<int>& str, int id) {
    int node_index = 0;
    for (auto& c : str) {
      if (nodes[node_index].nxt[c] == -1) {
        nodes[node_index].nxt[c] = (int)nodes.size();
        nodes.emplace_back(Node());
      }
      nodes[node_index].cnt += 1;
      node_index = nodes[node_index].nxt[c];
    }
    nodes[node_index].cnt += 1;
    nodes[node_index].accept.emplace_back(id);
  }
  void add(const std::vector<int>& str) { add(str, nodes[0].cnt); }

  int find(const std::vector<int>& str) {
    int node_index = 0;
    for (auto& c : str) {
      if (nodes[node_index].nxt[c] == -1) return -1;
      node_index = nodes[node_index].nxt[c];
    }
    return node_index;
  }
  int count() const { return nodes[0].cnt; }
  int size() const { return nodes.size(); }
};