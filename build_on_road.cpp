#include <climits>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board) {
  int answer = INT_MAX;
  int N = board.size();
  int directX[4] = {-1, 1, 0, 0};
  int directY[4] = {0, 0, -1, 1};
  queue<pair<pair<int, int>, pair<int, int>>> q;

  q.push({{0, 0}, {4, 0}});
  board[0][0] = 1;

  while (!q.empty()) {
    int x = q.front().first.first;
    int y = q.front().first.second;
    int dir = q.front().second.first;
    int currentCost = q.front().second.second;

    q.pop();

    if (x == N - 1 && y == N - 1) {
      answer = answer < currentCost ? answer : currentCost;
      continue;
    }

    for (int j = 0; j < 4; j++) {
      int nx = x + directX[j];
      int ny = y + directY[j];
      int add = 100;

      if (nx >= 0 && nx < N && ny >= 0 && ny < N && board[nx][ny] != 1) {
        if (dir == 0 || dir == 1) {
          if (!(j == 0 || j == 1)) {
            add += 500;
          }
        } else if (dir == 2 || dir == 3) {
          if (!(j == 2 || j == 3)) {
            add += 500;
          }
        }

        if (board[nx][ny] == 0 || board[nx][ny] >= currentCost + add) {
          board[nx][ny] = currentCost + add;
          q.push({{nx, ny}, {j, currentCost + add}});
        }
      }
    }
  }

  return answer;
}