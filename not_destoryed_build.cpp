#include <string>
#include <vector>

using namespace std;

int cusum[1010][1010];
int N, M;

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
  N = board.size(), M = board[0].size();

  for (auto sk : skill) {
    int degree = sk[5];
    if (sk[0] == 1)
      degree = -degree;

    cusum[sk[1]][sk[2]] += degree;
    cusum[sk[3] + 1][sk[4] + 1] += degree;
    cusum[sk[1]][sk[4] + 1] -= degree;
    cusum[sk[3] + 1][sk[2]] -= degree;
  }

  for (int i = 0; i < N + 1; ++i) {
    for (int j = 0; j < M; ++j) {
      cusum[i][j + 1] += cusum[i][j];
    }
  }

  for (int j = 0; j < M + 1; ++j) {
    for (int i = 0; i < N; ++i) {
      cusum[i + 1][j] += cusum[i][j];
    }
  }

  int answer = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (board[i][j] + cusum[i][j] > 0)
        answer++;
    }
  }

  return answer;
}