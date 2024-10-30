#include <iostream>
using namespace std;

int main() {
  int num, max = -1;
  int a;

  for (int i = 1; i <= 9; i++) {
    cin >> num;

    if (num > max) {
      max = num;
      a = i;
    }
  }

  cout << max << endl;
  cout << a << endl;
}