#include <vector>
using namespace std;

int DP[100010];
int Bigger(int A, int B) {
  if (A > B)
    return A;
  return B;
}

int solution(vector<int> sticker) {
  int answer = 0;
  int N = sticker.size();
  if (N == 1)
    return sticker[0];

  DP[0] = sticker[0];
  DP[1] = sticker[0];
  for (int i = 2; i < N - 1; i++) {
    DP[i] = Bigger(DP[i - 2] + sticker[i], DP[i - 1]);
  }
  answer = Bigger(answer, DP[N - 2]);
  DP[0] = 0;
  DP[1] = sticker[1];
  for (int i = 2; i < N; i++) {
    DP[i] = Bigger(DP[i - 2] + sticker[i], DP[i - 1]);
  }
  answer = Bigger(answer, DP[N - 1]);

  return answer;
}