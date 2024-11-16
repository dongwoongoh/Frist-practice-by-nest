#include <algorithm>
#include <complex>
#include <iostream>
#include <vector>
using namespace std;

const double PI = acos(-1);
typedef complex<double> cpx;
bool one_only[200001];

void FFT(vector<cpx> &f, bool inv = false) {
  int n = f.size(), j = 0;
  vector<cpx> roots(n / 2);
  for (int i = 1; i < n; i++) {
    int bit = (n >> 1);
    while (j >= bit) {
      j -= bit;
      bit >>= 1;
    }
    j += bit;
    if (i < j)
      swap(f[i], f[j]);
  }
  double ang = 2 * PI / n * (inv ? -1 : 1);
  for (int i = 0; i < n / 2; i++) {
    roots[i] = cpx(cos(ang * i), sin(ang * i));
  }
  for (int i = 2; i <= n; i <<= 1) {
    int step = n / i;
    for (int j = 0; j < n; j += i) {
      for (int k = 0; k < i / 2; k++) {
        cpx u = f[j + k], v = f[j + k + i / 2] * roots[step * k];
        f[j + k] = u + v;
        f[j + k + i / 2] = u - v;
      }
    }
  }
  if (inv)
    for (int i = 0; i < n; i++)
      f[i] /= n;
}

vector<cpx> mul(vector<cpx> a, vector<cpx> b) {
  int n = 1;
  while ((n < a.size() + 1) || (n < b.size() + 1))
    n *= 2;
  n *= 2;

  a.resize(n);
  b.resize(n);
  vector<cpx> c(n);

  FFT(a, 0);
  FFT(b, 0);

  for (int i = 0; i < n; i++) {
    c[i] = a[i] * b[i];
  }

  FFT(c, 1);

  vector<cpx> ret(n);
  for (int i = 0; i < n; i++) {
    ret[i] = cpx(round(c[i].real()), round(c[i].imag()));
  }
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  vector<cpx> polynomial(200001, cpx(0, 0));
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int v;
    cin >> v;
    one_only[v] = true;
    polynomial[v] = cpx(1, 0);
  }

  auto res = mul(polynomial, polynomial);

  int ans = 0;

  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int v;
    cin >> v;
    if (res[v].real() != 0 || one_only[v] == true) {
      ans++;
    }
  }
  cout << ans;
  return 0;
}