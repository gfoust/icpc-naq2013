#include <iostream>
#include <vector>
using namespace std;

void evenup(vector<unsigned>& left, vector<unsigned>& right, unsigned init) {
  vector<unsigned> bits;
  bits.reserve(20);
  while (init > 0) {
    bits.push_back(init % 3);
    init /= 3;
  }
  bits.push_back(0);

  for (unsigned i = 0, pow3 = 1; i < bits.size(); ++i, pow3 *= 3) {
    if (bits[i] == 1) {
      right.push_back(pow3);
    }
    if (bits[i] == 2) {
      left.push_back(pow3);
      ++bits[i];
    }
    if (bits[i] == 3) {
      bits[i] = 0;
      bits[i + 1]++;
    }
  }
}

int main() {
  int num;
  cin >> num;
  for (int i = 0; i < num; ++i) {
    vector<unsigned> left, right;
    left.reserve(20);
    right.reserve(20);

    unsigned init;
    cin >> init;
    if (init > 0) {
      evenup(left, right, init);
    }

    if (i > 0) cout << endl;
    cout << "left pan:";
    for (unsigned i = left.size(); i > 0; --i) {
      cout << ' ' << left[i - 1];
    }
    cout << "\nright pan:";
    for (unsigned i = right.size(); i > 0; --i) {
      cout << ' ' << right[i - 1];
    }
    cout << endl;
  }
}