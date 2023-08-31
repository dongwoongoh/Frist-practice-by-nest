#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<string> operations) {
  vector<int> answer;
  priority_queue<int, vector<int>, less<int>> pq1;
  priority_queue<int, vector<int>, greater<int>> pq2;
  int cnt = 0;
  int size = operations.size();

  for (int i = 0; i < size; ++i) {
    stringstream ss;
    ss.str(operations[i]);
    string temp;
    ss >> temp;
    if (temp == "I") {
      ss >> temp;
      pq1.push(stoi(temp));
      pq2.push(stoi(temp));
      ++cnt;
    } else if (temp == "D" && cnt > 0) {
      ss >> temp;
      if (temp == "-1") {
        pq2.pop();
      } else if (temp == "1") {
        pq1.pop();
      }
      --cnt;
      if (cnt == 0) {
        while (!pq1.empty()) {
          pq1.pop();
        }
        while (!pq2.empty()) {
          pq2.pop();
        }
      }
    }
  }

  if (cnt == 0) {
    answer.push_back(0);
    answer.push_back(0);
  } else {
    answer.push_back(pq1.top());
    answer.push_back(pq2.top());
  }
  return answer;
}