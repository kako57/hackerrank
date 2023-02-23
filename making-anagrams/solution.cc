#include <iostream>

using namespace std;

int making_anagrams(const string& s1, const string& s2) {
  int char_count[26] = {0};

  uint i;
  for (i = 0; s1[i]; i++) {
    char_count[s1[i] - 'a']++;
  }
  for (i = 0; s2[i]; i++) {
    char_count[s2[i] - 'a']--;
  }

  int ans = 0;
  for (i = 0; i < 26; i++) {
    if (char_count[i] < 0) {
      ans -= char_count[i];
    } else {
      ans += char_count[i];
    }
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  string s, t;
  cin >> s >> t;

  cout << making_anagrams(s, t) << '\n';

  return 0;
}
