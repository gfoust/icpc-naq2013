#include <array>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

std::array<bool, 32'001> sieve;
vector<int> primes;

struct Sum {
  int lhs, rhs;
};

void makePrimes() {
  sieve.fill(true);
  for (int i = 2; i * i <= 32'000; ++i) {
    for (int j = 2 * i; j <= 32'000; j += i) {
      sieve[j] = false;
    }
  }
  primes.reserve(3500);
  for (int i = 2; i <= 32'000; ++i) {
    if (sieve[i]) {
      primes.push_back(i);
    }
  }
  std::cerr << "Found " << primes.size() << " primes" << endl;
}

vector<Sum> getSums(int x) {
  vector<Sum> sums;
  for (int i = 0; i < primes.size(); ++i) {
    for (int j = i; j < primes.size(); ++j) {
      int sum = primes[i] + primes[j];
      if (sum == x) {
        sums.push_back({ primes[i], primes[j] });
      }
      else if (sum > x) {
        break;
      }
    }
  }
  return sums;
}

int main() {
  makePrimes();
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    auto sums = getSums(x);
    cout << x << " has " << sums.size() << " representation(s)" << endl;
    for (auto sum : sums) {
      cout << sum.lhs << '+' << sum.rhs << endl;
    }
    cout << endl;
  }
}


