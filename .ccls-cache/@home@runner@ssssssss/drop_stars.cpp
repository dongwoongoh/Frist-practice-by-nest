#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll A[100001];
ll tr[400001];
ll lazy[400001];
void update_lazy(int x, int s, int e);
ll sum(int x, int s, int e, int l, int r) {
  update_lazy(x, s, e);
  if (s > r || e < l)
    return 0;
  else if (s >= l && e <= r)
    return tr[x];
  else
    return sum(x * 2, s, (s + e) / 2, l, r) +
           sum(x * 2 + 1, (s + e) / 2 + 1, e, l, r);
}
void update_range(int x, int s, int e, int l, int r, ll val) {
  update_lazy(x, s, e);
  if (s > r || e < l)
    return;
  if (s >= l && e <= r) {
    tr[x] += (e - s + 1) * val;
    if (s != e) {
      lazy[x * 2] += val;
      lazy[x * 2 + 1] += val;
    }
    return;
  }
  update_range(x * 2, s, (s + e) / 2, l, r, val);
  update_range(x * 2 + 1, (s + e) / 2 + 1, e, l, r, val);
  tr[x] = tr[x * 2] + tr[x * 2 + 1];
}
void update_lazy(int x, int s, int e) {
  if (lazy[x] != 0) {
    tr[x] += (e - s + 1) * lazy[x];
    if (s != e) {
      lazy[x * 2] += lazy[x];
      lazy[x * 2 + 1] += lazy[x];
    }
    lazy[x] = 0;
  }
}
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++)
    cin >> A[i];
  for (int i = 1; i <= N; i++) {
    update_range(1, 1, N, i, i, A[i] - A[i - 1]);
  }
  int Q;
  cin >> Q;
  while (Q--) {
    int a;
    cin >> a;
    if (a == 1) {
      int l, r;
      cin >> l >> r;
      update_range(1, 1, N, l, r, 1);
      update_range(1, 1, N, r + 1, r + 1, -(r - l + 1));
    } else {
      int x;
      cin >> x;
      cout << sum(1, 1, N, 1, x) << '\n';
    }
  }
}