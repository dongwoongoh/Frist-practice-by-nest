#include <algorithm>
#include <climits>
#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct state {
  int a, b;
  double c;
};

double ans = 0;

int N, M, x, y;
vector<pair<int, int>> v;
vector<state> e;
int res = 0;
int p[1001];

bool cmp(state a, state b) { return a.c < b.c; }

double dist(int x, int y) {
  return (double)sqrt(pow(abs(v[x].first - v[y].first), 2) +
                      pow(abs(v[x].second - v[y].second), 2));
}

int find(int n) {
  if (p[n] == n)
    return n;
  return p[n] = find(p[n]);
}

bool union_node(int x, int y) {
  int px = find(x), py = find(y);

  if (px == py)
    return false;

  p[max(px, py)] = min(px, py);

  return true;
}

int main() {

  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed;
  cout.precision(2);

  cin >> N >> M;
  for (int i = 0; i <= N; i++)
    p[i] = i;

  for (int i = 0; i < N; i++) {
    cin >> x >> y;
    v.push_back({x, y});
  }
  for (int i = 0; i < M; i++) {
    cin >> x >> y;
    union_node(x, y);
  }
  for (int i = 0; i < N - 1; i++) {
    for (int j = i + 1; j < N; j++) {
      e.push_back({i + 1, j + 1, dist(i, j)});
    }
  }

  sort(e.begin(), e.end(), cmp);

  for (int i = 0; i < e.size(); i++) {
    if (union_node(e[i].a, e[i].b)) {
      res++;
      ans += e[i].c;
    }
  }

  cout << ans;

  return 0;
}