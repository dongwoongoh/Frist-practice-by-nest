#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int visit[25][25];
int n;

void gostraight(int b, int sti, int stj, queue<pair<int, int>> &q,
                queue<char> &bang) {
  int cost = visit[sti][stj] + 500;

  if (b > 0) {
    int cnt = 1;
    for (int i = sti - 1; i >= 0; i--) {
      if (visit[i][stj] == 1)
        break;

      if (visit[i][stj] > cost + cnt * 100) {
        q.push(pair<int, int>(i, stj));
        bang.push(-1);
        visit[i][stj] = cost + cnt * 100;
      }
      cnt++;
    }

    cnt = 1;
    for (int i = sti + 1; i < n; i++) {
      if (visit[i][stj] == 1)
        break;

      if (visit[i][stj] > cost + cnt * 100) {
        q.push(pair<int, int>(i, stj));
        bang.push(-2);
        visit[i][stj] = cost + cnt * 100;
      }
      cnt++;
    }
  } else {
    int cnt = 1;
    for (int i = stj - 1; i >= 0; i--) {
      if (visit[sti][i] == 1)
        break;

      if (visit[sti][i] > cost + cnt * 100) {
        q.push(pair<int, int>(sti, i));
        bang.push(1);
        visit[sti][i] = cost + cnt * 100;
      }

      cnt++;
    }

    cnt = 1;
    for (int i = stj + 1; i < n; i++) {
      if (visit[sti][i] == 1)
        break;

      if (visit[sti][i] > cost + cnt * 100) {
        q.push(pair<int, int>(sti, i));
        bang.push(2);
        visit[sti][i] = cost + cnt * 100;
      }

      cnt++;
    }
  }

  return;
}

int bfs() {
  queue<pair<int, int>> q;
  queue<char> bang;

  int sti = 0;
  int stj = 0;
  int b;
  visit[0][0] = 1;

  int cost = 0;
  for (int i = 1; i < n; i++) {
    if (visit[0][i] == 1) {
      break;
    }
    visit[0][i] = i * 100;
    q.push(pair<int, int>(0, i));
    bang.push(2);
  }

  for (int i = 1; i < n; i++) {
    if (visit[i][0] == 1) {
      break;
    }

    visit[i][0] = i * 100;
    q.push(pair<int, int>(i, 0));
    bang.push(-2);
  }

  while (!q.empty()) {
    sti = q.front().first;
    stj = q.front().second;

    b = bang.front();

    q.pop();
    bang.pop();

    gostraight(b, sti, stj, q, bang);
  }

  return visit[n - 1][n - 1];
}

int solution(vector<vector<int>> board) {
  int answer = 0;
  n = board.size();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == 0)
        visit[i][j] = 100000000;
      else
        visit[i][j] = board[i][j];
    }
  }

  answer = bfs();

  return answer;
}