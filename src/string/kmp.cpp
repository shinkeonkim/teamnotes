struct KMP {
  /*
    s 문자열에서 o문자열을 찾습니다.
    매칭이 시작되는 인덱스 목록을 반환합니다.
    Time: O(n + m)
  */
  vector<int> result;
  int MX;
  string s, o;
  int n, m; // n : s.length(), m :o.length();
  vector<int> fail;

  KMP(string s, string o) : s(s), o(o) {
    n = s.length();
    m = o.length();
    MX = max(n, m) + 1;
    fail.resize(MX, 0);

    run();
  }

  void run() {
    for(int i = 1, j = 0; i < m; i++){
      while(j > 0 && o[i] != o[j]) j = fail[j-1];
      if(o[i] == o[j]) fail[i] = ++j;
    }
    for(int i = 0, j = 0; i < n; i++) {
      while(j > 0 && s[i] != o[j]) {
        j = fail[j - 1];
      }
      if(s[i] == o[j]) {
        if(j == m - 1) {
          // matching OK;
          result.push_back(i - m + 1);
          j = fail[j];
        }
        else {
          j++;
        }
      }
    }
  }
};
