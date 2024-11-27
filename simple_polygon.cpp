#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef long long ll;

struct p {
  ll x, y, idx;
  bool operator<(const p &t) const {
    if (x != t.x)
      return x < t.x;
    return y < t.y;
  }
  bool operator==(const p &t) const { return x == t.x && y == t.y; }
};

int ccw(p a, p b, p c) {
  ll res = a.x * b.y + b.x * c.y + c.x * a.y;
  res -= b.x * a.y + c.x * b.y + a.x * c.y;
  if (res > 0)
    return 1;
  if (res)
    return -1;
  return 0;
}

ll dist(p a, p b) {
  ll dx = a.x - b.x;
  ll dy = a.y - b.y;
  return dx * dx + dy * dy;
}

int n;
vector<p> v;

void solve() {
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i].x >> v[i].y;
    v[i].idx = i;
  }
  swap(v[0], *min_element(v.begin(), v.end()));
  sort(v.begin() + 1, v.end(), [&](p &a, p &b) {
    int cw = ccw(v[0], a, b);
    if (cw)
      return cw > 0;
    return dist(v[0], a) < dist(v[0], b);
  });
  int pt = v.size() - 1;
  for (int i = v.size() - 1; i >= 1; i--) {
    if (ccw(v[0], v[pt], v[pt - 1]) == 0) {
      pt--;
    } else {
      break;
    }
  }
  reverse(v.begin() + pt, v.end());
  for (auto i : v)
    cout << i.idx << " ";
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t;
  cin >> t;
  while (t--)
    solve();
}