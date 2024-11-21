#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < n; ++i)
#define REP(i, n) for (int i = 1; i <= n; ++i)
#define FAST                                                                   \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);                                                              \
  ios::sync_with_stdio(false)
using namespace std;

vector<int> g, ng, sfx, cnt, lcp, ordered;

void getsfx(string &s) {
  int n = s.size();
  int mx = max(257, n + 1);

  g.resize(n + 1);
  ng.resize(n + 1);
  sfx.resize(n);
  ordered.resize(n);

  for (int i = 0; i < n; ++i)
    g[i] = s[i];

  for (int t = 1; t < n; t <<= 1) {
    cnt.clear();
    cnt.resize(mx);
    for (int i = 0; i < n; ++i)
      cnt[g[min(i + t, n)]]++;
    for (int i = 1; i < mx; ++i)
      cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; --i)
      ordered[--cnt[g[min(i + t, n)]]] = i;

    cnt.clear();
    cnt.resize(mx);
    for (int i = 0; i < n; ++i)
      cnt[g[i]]++;
    for (int i = 1; i < mx; ++i)
      cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; --i)
      sfx[--cnt[g[ordered[i]]]] = ordered[i];

    auto cmp = [&](int i, int j) {
      if (g[i] == g[j])
        return g[i + t] < g[j + t];
      return g[i] < g[j];
    };

    ng[sfx[0]] = 1;
    for (int i = 1; i < n; ++i) {
      if (cmp(sfx[i - 1], sfx[i]))
        ng[sfx[i]] = ng[sfx[i - 1]] + 1;
      else
        ng[sfx[i]] = ng[sfx[i - 1]];
    }
    g = ng;
  }

  lcp.resize(n);
  for (int i = 0; i < n; ++i)
    g[sfx[i]] = i;

  for (int i = 0, k = 0; i < n; ++i, k = max(k - 1, 0)) {
    if (g[i] == n - 1)
      continue;
    for (int j = sfx[g[i] + 1]; s[i + k] == s[j + k]; ++k)
      ;
    lcp[g[i]] = k;
  }
}

int main() {
  FAST;
  string input;
  cin >> input;
  getsfx(input);

  for (auto x : sfx)
    cout << x + 1 << ' ';
  cout << '\n';
  cout << 'x' << ' ';
  for (int i = 0; i < lcp.size() - 1; ++i)
    cout << lcp[i] << ' ';

  return 0;
}