#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

vector<int> nextPascal(vector<int>& cs) {
  vector<int> ds(cs.size() + 1);
  ds.front() = cs.front();
  for (int i = 1; i < cs.size(); ++i) {
    ds[i] = cs[i - 1] + cs[i];
  }
  ds.back() = cs.back();
  return ds;
}

int eval(vector<int>& cs, int x) {
  int sum = 0;
  int powx = 1;
  for (size_t i = 0; i < cs.size(); ++i, powx *= x) {
    sum += cs[i] * powx;
  }
  return sum;
}

int dot(vector<int>& v, vector<int>& w) {
  int sum = 0;
  for (int i = 0; i < v.size(); ++i) {
    sum += v[i] * w[i];
  }
  return sum;
}

vector<int> findTs(vector<int>& cs) {
  vector<int> ps = { 1 };
  vector<int> ts;
  for (int i = 0; i < cs.size(); ++i) {
    ts.push_back(eval(cs, i) - dot(ts, ps));
    ps = nextPascal(ps);
  }
  return ts;
}

int main() {
  int degree;
  while (cin >> degree && degree > 0) {
    vector<int> cs(degree + 1);
    for (int i = 0; i <= degree; ++i) {
      cin >> cs[degree - i];
    }
    bool first = true;
    for (int t : findTs(cs)) {
      if (first) first = false;
      else cout << ' ';
      cout << t;
    }
    cout << endl;
  }
}