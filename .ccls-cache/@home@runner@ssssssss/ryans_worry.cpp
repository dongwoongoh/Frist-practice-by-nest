#include <algorithm>
#include <vector>
using namespace std;

int solution(int n, int m, vector<vector<int>> timetable) {
  vector<int> count(1321);
  for (auto &ve : timetable) {
    for (int i = ve.front(); i <= ve.back(); ++i) {
      count[i]++;
    }
  }

  int people = *max_element(count.begin(), count.end());
  if (people <= 1) {
    return 0;
  }

  for (int dis = 2 * n - 2; dis > 0; --dis) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        vector<pair<int, int>> ve({{i, j}});
        for (int y = i; y < n; ++y) {
          for (int x = 0; x < n; ++x) {
            if (y == i && x <= j)
              continue;

            bool canPush = true;
            for (auto &p : ve) {
              int distance = abs(p.first - y) + abs(p.second - x);
              if (distance < dis) {
                canPush = false;
                break;
              }
            }

            if (canPush) {
              ve.emplace_back(y, x);
              if (people == ve.size()) {
                return dis;
              }
            }
          }
        }
      }
    }
  }

  return 0;
}