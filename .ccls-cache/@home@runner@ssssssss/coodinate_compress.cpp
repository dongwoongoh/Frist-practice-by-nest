#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int N;
  std::cin >> N;
  std::vector<int> v(N);

  for (int i = 0; i < N; ++i) {
    std::cin >> v[i];
  }

  std::vector<int> ans(v);
  std::sort(ans.begin(), ans.end());
  ans.erase(std::unique(ans.begin(), ans.end()), ans.end());

  for (const auto &val : v) {
    auto it = std::find(ans.begin(), ans.end(), val);
    std::cout << std::distance(ans.begin(), it) << ' ';
  }
}