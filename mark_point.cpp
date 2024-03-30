#include <iostream>
#include <string>
#include <vector>
using namespace std;

long long solution(int _k, int _d) {
  long long k = _k;
  long long d = _d;
  long long answer = 0;
  long long ak = 0;
  long long bk = d - (d % k);
  while (ak <= d) {
    answer += (bk / k + 1);
    ak += k;
    while (ak * ak + bk * bk > d * d && bk > 0) {
      bk -= k;
    }
  }
  return answer;
}