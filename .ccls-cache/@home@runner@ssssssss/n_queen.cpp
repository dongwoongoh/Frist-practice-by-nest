#include <cmath>
#include <string>
#include <vector>
using namespace std;

void dfs(vector<int> &chess, int &answer, int col) {
  if (chess.size() == col) {
    answer++;
  } else {
    for (int i = 0; i < chess.size(); i++) {
      bool flag = true;
      chess[col] = i;

      for (int u = 0; u < col; u++) {
        if (chess[col] == chess[u] ||
            abs(chess[col] - chess[u]) == abs(col - u)) {
          flag = false;
          break;
        }
      }
      if (flag)
        dfs(chess, answer, col + 1);
    }
  }
}

int solution(int n) {
  int answer = 0;
  vector<int> chess(n, 0);
  dfs(chess, answer, 0);
  return answer;
}