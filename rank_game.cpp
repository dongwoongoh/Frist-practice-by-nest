#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> A, vector<int> B) {
  int answer = 0;
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  int a_idx = 0;
  for (int i = 0; i < B.size(); i++) {
    if (A[a_idx] < B[i]) {
      a_idx++;
      answer++;
    }
  }
  return answer;
}