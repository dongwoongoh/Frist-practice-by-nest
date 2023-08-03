#include <string>
#include <vector>

using namespace std;

int M, N, Size, Point;
vector<vector<int>> MAP;

void Make_MAP(vector<vector<int>> lock) {
  int lock_x = 0;
  int lock_y = 0;
  for (int i = M - 1; i < Size - (M - 1); i++, lock_x++) {
    for (int j = M - 1; j < Size - (M - 1); j++, lock_y++) {
      MAP[i][j] = lock[lock_x][lock_y];
      if (MAP[i][j] == 0)
        Point++;
    }
    lock_y = 0;
  }
}

int Sum_Key_And_Lock(int Sx, int Sy, vector<vector<int>> key) {
  int x_Idx = 0;
  int y_Idx = 0;
  int Check = 0;
  for (int x = Sx; x < Sx + M; x++, x_Idx++) {
    for (int y = Sy; y < Sy + M; y++, y_Idx++) {
      if (MAP[x][y] == 1 && key[x_Idx][y_Idx] == 1)
        return -1;
      if (MAP[x][y] == 0 && key[x_Idx][y_Idx] == 0)
        return -1;
      if (MAP[x][y] == 0 && key[x_Idx][y_Idx] == 1)
        Check++;
    }
    y_Idx = 0;
  }
  return Check;
}

void Rotate_Key(vector<vector<int>> &Key) {
  vector<vector<int>> Temp = Key;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      Temp[i][j] = Key[M - 1 - j][i];
    }
  }
  Key = Temp;
}

bool Move_MAP(vector<vector<int>> key) {
  for (int R = 0; R < 4; R++) {
    for (int i = 0; i < M + N - 1; i++) {
      for (int j = 0; j < M + N - 1; j++) {
        int Result = Sum_Key_And_Lock(i, j, key);
        if (Result == Point)
          return true;
      }
    }
    Rotate_Key(key);
  }
  return false;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
  M = key.size();
  N = lock.size();
  Size = N + 2 * (M - 1);
  MAP.resize(Size, vector<int>(Size, 2));
  Make_MAP(lock);
  bool answer = Move_MAP(key);
  return answer;
}
