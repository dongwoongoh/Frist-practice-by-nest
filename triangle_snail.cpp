#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n) {
  vector<int> answer;
  vector<vector<int>> tri_snail;
  vector<int> tmp;
  int number = 1;

  for (int i = 1; i <= n; i++) {
    tmp.resize(i, 0);
    tri_snail.push_back(tmp);
  }

  for (int h = 0; h < n; h++) {
    for (int i = 2 * h; i < n - h; i++) {
      tri_snail[i][h] = number;
      number++;
      if (i == n - h - 1) {
        for (int j = 1 * h + 1; j < i - h; j++) {
          tri_snail[i][j] = number;
          number++;
        }
      }
    }

    for (int i = n - h - 1; i > 2 * h; i--) {
      tri_snail[i][i - h] = number;
      number++;
    }
  }

  for (const auto &an : tri_snail) {
    for (const auto &b : an) {
      answer.push_back(b);
    }
  }

  return answer;
}