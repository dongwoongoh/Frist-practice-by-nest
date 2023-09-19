#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> orders;
void backtracking(int remain, int idx, vector<int> order) {
  if (remain <= 0) {
    orders.push_back(order);
    return;
  }

  for (int i = idx; i < order.size(); i++) {
    order[i]++;
    backtracking(remain - 1, i, order);
    order[i]--;
  }
}

int simulation(vector<int> order, vector<vector<int>> reqs) {
  priority_queue<int, vector<int>, greater<int>> pq[order.size()];
  int result = 0;

  for (int i = 1; i < order.size(); i++) {
    for (int j = 0; j < order[i]; j++)
      pq[i].push(0);
  }

  for (auto req : reqs) {
    int arrive = req[0];
    int time = req[1];
    int idx = req[2];
    int picked = pq[idx].top();
    pq[idx].pop();
    if (picked > arrive) {
      result += picked - arrive;
      pq[idx].push(picked + time);
    } else if (picked < arrive)
      pq[idx].push(arrive + time);
    else
      pq[idx].push(picked + time);
  }

  return result;
}
int solution(int k, int n, vector<vector<int>> reqs) {
  int answer = 99999999;

  vector<int> kind(k + 1, 1);
  backtracking(n - k, 1, kind);

  for (auto order : orders) {
    answer = min(answer, simulation(order, reqs));
  }
  return answer;
}