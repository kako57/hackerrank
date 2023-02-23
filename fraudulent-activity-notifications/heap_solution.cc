#include <iostream>
#include <iterator>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

class PriorTransactionData {
private:

public:
  // heaps are slow due to the deletes having linear time complexity :(
  // time for basic binary search attempt
  vector<uint> window;
  queue<uint> data_in_window;
  size_t max_num_items;

  PriorTransactionData(int max_num_items) : max_num_items(max_num_items) {
  }

  void delete_value(uint value) {
    auto it = std::lower_bound(this->window.begin(), this->window.end(), value);
    if (it != this->window.end())
      this->window.erase(it);
  }

  void push(uint value) { // insert value while keeping sorted property of window
    this->window.insert(
      std::upper_bound(this->window.begin(), this->window.end(), value),
      value
    );
  }

  uint median() {
    uint n = this->window.size();
    uint idx = n / 2;
    uint result = this->window[idx];
    if (n % 2 == 0) {
      idx--;
    }
    result += this->window[idx];
    return result;
  }
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  uint n, d, i, x, ans = 0;
  cin >> n >> d;

  PriorTransactionData ptd = PriorTransactionData(d);

  for (i = 0; i < d; i++) {
    cin >> x;
    ptd.push(x);
  }

  for (; i < n; i++) {
    cin >> x;

    if (x >= ptd.median()) {
      ans++;
    }
    ptd.push(x);
  }

  cout << ans << endl;

  return 0;
}
