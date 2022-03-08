#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

const int SEC_PER_MIN = 60;
const int SEC_PER_DEG = 60 * 60;
const int MAX_DEG = 60 * 60 * 360;
const double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

double biggest(double r, int n, int theta) {
  vector<int> degs;
  degs.reserve(n);
  int ang = 0;
  for (int i = 0; i < n; ++i) {
    degs.push_back(ang);
    ang = (ang + theta) % MAX_DEG;
  }
  std::sort(degs.begin(), degs.end());
  int maxdiff = MAX_DEG - degs.back();
  for (int i = 1; i < n; ++i) {
    maxdiff = std::max(maxdiff, degs[i] - degs[i - 1]);
  }
  return (PI * r * r) / 360.0 * ((double)maxdiff / SEC_PER_DEG);
}

int main() {
  cout << std::fixed;
  int m;
  cin >> m;
  for (int i = 0; i < m; ++i) {
    int r, n, deg, min, sec;
    cin >> r >> n >> deg >> min >> sec;
    cout << biggest(r, n % MAX_DEG, deg * SEC_PER_DEG + min * SEC_PER_MIN + sec) << endl;
  }
}