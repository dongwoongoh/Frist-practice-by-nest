#define ll long long int
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct pa {
  ll x, y, p, q;
  bool operator<(const struct pa &t) const {
    if (q * t.p == t.q * p) {
      if (x == t.x) {
        return y < t.y;
      } else if (y == t.y) {
        return x < t.x;
      }
      if (p * q > 0 && t.q * t.p > 0)
        return y < t.y;
      else
        return y > t.y;
    }
    return q * t.p < t.q * p;
  }
  struct pa operator-(struct pa &b) {
    return {x - b.x, y - b.y};
  }
  bool operator==(struct pa &t) { return x == t.x && y == t.y; }
};

struct line {
  struct pa pos[2];
};

ll ccw2(struct pa p, struct pa q) { return p.x * q.y - p.y * q.x; }

int ccw(struct pa a, struct pa b, struct pa c) {
  ll tmp = ccw2(b - a, c - a);
  if (tmp > 0)
    return 1;
  else if (tmp == 0)
    return 0;
  else
    return -1;
}

int N, M;
struct pa pos[102];
struct pa arr[102];

bool between(struct pa a, struct pa b, struct pa c) {
  if (ccw(a, b, c) != 0)
    return false;
  if (a.x != b.x) {
    return (a.x <= c.x && b.x >= c.x) || (b.x <= c.x && a.x >= c.x);
  } else {
    return (a.y <= c.y && b.y >= c.y) || (b.y <= c.y && a.y >= c.y);
  }
}

bool isline_intersect(struct line l1, struct line l2) {

  int std1 = ccw(l1.pos[0], l1.pos[1], l2.pos[0]) *
             ccw(l1.pos[0], l1.pos[1], l2.pos[1]);
  int std2 = ccw(l2.pos[0], l2.pos[1], l1.pos[0]) *
             ccw(l2.pos[0], l2.pos[1], l1.pos[1]);

  if (std1 <= 0 && std2 <= 0) {
    if (std1 == 0 && std2 == 0) {
      if (between(l1.pos[0], l1.pos[1], l2.pos[0]) ||
          between(l1.pos[0], l1.pos[1], l2.pos[1]) ||
          between(l2.pos[0], l2.pos[1], l1.pos[0]) ||
          between(l2.pos[0], l2.pos[1], l1.pos[1])) {
        return true;
      } else
        return false;
    } else
      return true;
  } else
    return false;
}

bool isPointInPolygon(struct pa &P, vector<struct pa> &V) {
  int cnt = 0;

  for (int i = 0; i < V.size(); i++) {
    struct line l1;
    l1.pos[0] = {0, 0};
    l1.pos[1] = {20000, 0};

    struct pa p1 = V[i] - P;
    struct pa p2 = V[(i + 1) % V.size()] - P;

    if (between(p1, p2, l1.pos[0])) {
      return true;
    }
    if ((p1.y < 0 && p2.y >= 0 && ccw(p1, p2, {0, 0}) == 1) ||
        (p2.y < 0 && p1.y >= 0 && ccw(p2, p1, {0, 0}) == 1)) {
      cnt++;
    }
  }
  return (cnt & 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int tc;
  cin >> tc;
  while (tc--) {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
      cin >> arr[i].x >> arr[i].y;
      if (arr[i].x < arr[0].x) {
        swap(arr[i], arr[0]);
      } else if (arr[i].x == arr[0].x && arr[i].y < arr[0].y) {
        swap(arr[i], arr[0]);
      }
    }
    for (int i = 1; i < N; i++) {
      arr[i].p = arr[i].x - arr[0].x;
      arr[i].q = arr[i].y - arr[0].y;
    }

    sort(arr + 1, arr + N);

    for (int i = 0; i < M; i++) {
      cin >> pos[i].x >> pos[i].y;
      if (pos[i].x < pos[0].x) {
        swap(pos[i], pos[0]);
      } else if (pos[i].x == pos[0].x && pos[i].y < pos[0].y) {
        swap(pos[i], pos[0]);
      }
    }
    for (int i = 1; i < M; i++) {
      pos[i].p = pos[i].x - pos[0].x;
      pos[i].q = pos[i].y - pos[0].y;
    }
    sort(pos + 1, pos + M);

    vector<struct pa> V;
    V.push_back(arr[0]);
    for (int i = 1; i < N; i++) {
      while (V.size() >= 2 &&
             ccw(V[V.size() - 2], V[V.size() - 1], arr[i]) <= 0) {
        V.pop_back();
      }
      V.push_back(arr[i]);
    }
    vector<struct pa> V2;
    V2.push_back(pos[0]);
    for (int i = 1; i < M; i++) {
      while (V2.size() >= 2 &&
             ccw(V2[V2.size() - 2], V2[V2.size() - 1], pos[i]) <= 0) {
        V2.pop_back();
      }
      V2.push_back(pos[i]);
    }

    bool cross = false;

    if (V.size() > 2 && V2.size() > 2) {
      for (auto &p : V) {
        cross |= isPointInPolygon(p, V2);
        if (cross)
          break;
      }
      for (auto &p : V2) {
        cross |= isPointInPolygon(p, V);
        if (cross)
          break;
      }
    } else if (V.size() >= 2 && V2.size() == 2) {
      for (int i = 0; i < V.size() && !cross; i++) {
        cross |=
            isline_intersect({V[i], V[(i + 1) % V.size()]}, {V2[0], V2[1]});
      }
    } else if (V.size() >= 2 && V2.size() == 1) {
      cross |= isPointInPolygon(V2[0], V);
    } else if (V.size() == 2 && V2.size() >= 2) {
      for (int i = 0; i < V2.size() && !cross; i++) {
        cross |=
            isline_intersect({V2[i], V2[(i + 1) % V2.size()]}, {V[0], V[1]});
      }
    } else if (V.size() == 1 && V2.size() >= 2) {
      cross |= isPointInPolygon(V[0], V2);
    }

    cout << (cross ? "NO\n" : "YES\n");
  }
}