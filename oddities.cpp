#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    cout << x << " is " << (x % 2 ? "odd" : "even") << endl;
  }
}