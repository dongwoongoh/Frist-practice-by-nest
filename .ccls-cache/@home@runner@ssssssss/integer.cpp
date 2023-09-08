#include <algorithm>
#include <vector>
using namespace std;

int Min(int A, int B) {
  if (A < B)
    return A;
  return B;
}
int Max(int A, int B) {
  if (A > B)
    return A;
  return B;
}

int solution(int n, vector<vector<int>> data) {
  int answer = 0;
  sort(data.begin(), data.end());
  for (int i = 0; i < n; i++) {
    int x = data[i][0];
    int y = data[i][1];

    for (int j = i + 1; j < n; j++) {
      int xx = data[j][0];
      int yy = data[j][1];

      if (x == xx || y == yy)
        continue;

      bool Flag = true;
      for (int k = i + 1; k < j; k++) {
        int cx = data[k][0];
        int cy = data[k][1];
        if ((x < cx && cx < xx) && (Min(y, yy) < cy && cy < Max(y, yy))) {
          Flag = false;
          break;
        }
      }
      if (Flag == true)
        answer++;
    }
  }
  return answer;
}