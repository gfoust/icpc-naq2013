#include <iostream>
#include <stack>
using std::cin;
using std::cout;
using std::endl;

int main() {
  int n;
  cin >> n;
  std::stack<int> s;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    x = x % 2;
    if (!s.empty() && s.top() == x) {
      s.pop();
    }
    else {
      s.push(x);
    }
  }
  cout << s.size();
}
