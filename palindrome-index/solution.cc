#include <iostream>
#include <algorithm>

using namespace std;

bool is_palindrome(const string& s, int ignored_index) {
  for (int i = 0, j = s.length() - 1; i <= j; i++, j--) {
    if (i == ignored_index) {
      i++;
    }
    if (j == ignored_index) {
      j--;
    }
    if (s[i] != s[j]) {
      return false;
    }
  }

  return true;
}

int palindrome_index(const string& s) {
  for (int i = 0, j = s.length() - 1; i <= j; i++, j--) {
    if (s[i] != s[j]) {
      if (is_palindrome(s, i)) {
        return i;
      }
      else if (is_palindrome(s, j)) {
        return j;
      } else {
        return -1;
      }
    }
  }

  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int q;
  cin >> q;

  while (q--) {
    string s;
    cin >> s;

    cout << palindrome_index(s) << '\n';
  }

  return 0;
}
