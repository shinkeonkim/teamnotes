int chToIdx(char ch) { return ch - 'a'; }
struct Trie {
  int terminal = -1;
  Trie *fail; // fail, output은 아호 코라식에 사용
  vector<int> output;
  Trie *chil[ALPHABETS];
  Trie() {
    for (int i = 0; i < ALPHABETS; i++)
      chil[i] = NULL;
  }
  // number -> 문자열 번호(ith string)
  void insert(string &s, int number, int idx) {
    if (idx == s.size()) {
      terminal = number;
      return;
    }
    int next = chToIdx(s[idx]);
    if (chil[next] == NULL)
      chil[next] = new Trie();
    chil[next]->insert(s, number, idx + 1);
  }
  int find(string &s, int idx = 0) {
    if (idx == s.size())
      return terminal;
    int next = chToIdx(s[idx]);
    if (chil[next] == NULL)
      return false;
    return chil[next]->find(s, idx + 1);
  }
};