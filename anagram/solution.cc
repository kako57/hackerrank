#include <iostream>

using namespace std;

int anagram(const string& s) {
  if (s.length() % 2 == 1) {
    return -1;
  }

  int char_count[26] = {0};

  uint i;
  for (i = 0; i * 2 < s.length(); i++) {
    char_count[s[i] - 'a']++;
  }
  for (; i < s.length(); i++) {
    char_count[s[i] - 'a']--;
  }

  int ans = 0;
  for (i = 0; i < 26; i++) {
    if (char_count[i] < 0) {
      ans -= char_count[i];
    } else {
      ans += char_count[i];
    }
  }

  return ans / 2;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int q;
  cin >> q;

  while (q--) {
    string s;
    cin >> s;

    cout << anagram(s) << '\n';
  }

  return 0;
}
