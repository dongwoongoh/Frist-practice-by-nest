#include <algorithm>
#include <string>
#include <vector>

#define MAX 110
using namespace std;

int N;
int Pole[MAX][MAX];
int Bo[MAX][MAX];

struct STRUCTURE {
  int x;
  int y;
  int Shape;
  int Exist;
};

vector<STRUCTURE> List;

bool Check_Install_Pole(int x, int y) {
  if (x == N)
    return true;
  if (y - 1 >= 0 && Bo[x][y - 1] == true)
    return true;
  if (Bo[x][y] == true)
    return true;
  if (Pole[x + 1][y] == true)
    return true;
  return false;
}

bool Check_Install_Bo(int x, int y) {
  if (Pole[x + 1][y] == true)
    return true;
  if (y + 1 <= N && Pole[x + 1][y + 1] == true)
    return true;
  if (Bo[x][y - 1] == true && Bo[x][y + 1] == true)
    return true;
  return false;
}

void Check_Delete_Pole(int x, int y) {
  int Idx = 0;
  Pole[x][y] = false;
  for (int i = 0; i < List.size(); i++) {
    int Lx = List[i].x;
    int Ly = List[i].y;
    int LShape = List[i].Shape;
    if (x == Lx && y == Ly && LShape == 0) {
      Idx = i;
      continue;
    }
    if (List[i].Exist == -1)
      continue;

    if (LShape == 0 && Check_Install_Pole(Lx, Ly) == false) {
      Pole[x][y] = true;
      return;
    }
    if (LShape == 1 && Check_Install_Bo(Lx, Ly) == false) {
      Pole[x][y] = true;
      return;
    }
  }
  List[Idx].Exist = -1;
}

void Check_Delete_Bo(int x, int y) {
  int Idx = 0;
  Bo[x][y] = false;
  for (int i = 0; i < List.size(); i++) {
    int Lx = List[i].x;
    int Ly = List[i].y;
    int LShape = List[i].Shape;
    if (x == Lx && y == Ly && LShape == 1) {
      Idx = i;
      continue;
    }
    if (List[i].Exist == -1)
      continue;

    if (LShape == 0 && Check_Install_Pole(Lx, Ly) == false) {
      Bo[x][y] = true;
      return;
    }
    if (LShape == 1 && Check_Install_Bo(Lx, Ly) == false) {
      Bo[x][y] = true;
      return;
    }
  }
  List[Idx].Exist = -1;
}

bool Compare(STRUCTURE A, STRUCTURE B) {
  if (A.Exist >= B.Exist) {
    if (A.Exist == B.Exist) {
      if (A.y <= B.y) {
        if (A.y == B.y) {
          if (A.x >= B.x) {
            if (A.x == B.x) {
              if (A.Shape < B.Shape) {
                return true;
              }
              return false;
            }
            return true;
          }
          return false;
        }
        return true;
      }
      return false;
    }
    return true;
  }
  return false;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
  N = n;
  List.clear();
  vector<vector<int>> answer;
  for (int i = 0; i < build_frame.size(); i++) {
    int x = build_frame[i][1];
    int y = build_frame[i][0];
    int Shape = build_frame[i][2];
    int Install = build_frame[i][3];
    x = n - x;

    if (Install == 1) {
      if (Shape == 0 && Check_Install_Pole(x, y) == true) {
        List.push_back({x, y, Shape, 1});
        Pole[x][y] = true;
      }
      if (Shape == 1 && Check_Install_Bo(x, y) == true) {
        List.push_back({x, y, Shape, 1});
        Bo[x][y] = true;
      }
    } else {
      if (Shape == 0)
        Check_Delete_Pole(x, y);
      if (Shape == 1)
        Check_Delete_Bo(x, y);
    }
  }
  sort(List.begin(), List.end(), Compare);
  for (int i = 0; i < List.size(); i++) {
    if (List[i].Exist == -1)
      break;
    answer.push_back({List[i].y, N - List[i].x, List[i].Shape});
  }
  return answer;
}
