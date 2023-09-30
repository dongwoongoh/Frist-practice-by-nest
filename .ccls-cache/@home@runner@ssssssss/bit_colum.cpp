#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int div(long long n, long long l, long long r) {
  if (l > r)
    return 0;
  if (n == 1) {
    return 1;
  }
  int ret = 0;
  long long s = n / 5;
  for (int i = 0; i < 5; i++) {
    if (i == 2)
      continue;
    ret += div(s, max(s * i, l) - (s * i), min(s * (i + 1) - 1, r) - (s * i));
  }
  return ret;
}

int solution(int n, long long l, long long r) {
  return div(pow(5, n), l - 1, r - 1);
}