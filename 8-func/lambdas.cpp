#include <functional>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  auto basicLambda{[] { cout << "Hello from Lambda" << endl; }};

  // class __lambda_6_24
  // {
  //     public:
  //     inline void operator()() const {
  //         std::operator<<(std::cout, "Hello from
  //         Lambda").operator<<(std::endl);
  //     }
  // };

  int init = 42;
  auto lessBasicLambda{[&init](int delta) { return ++init; }};

  // class __lambda_7_28
  // {
  //     public:
  //         inline int operator()(int delta) const
  //         {
  //         return init + delta;
  //         }
  //     private:
  //         int init;
  //     public:
  //         __lambda_7_28(int & _init)
  //         : init{_init}
  //         {}
  // };

  auto add_any = [](auto a, auto b) { return a + b; };
  add_any(3, 4);
  add_any(1.5, 2.7);
  add_any(1.5, 27);

  int x = 1;
  auto f = [x]() mutable { return ++x; };
  auto g = f;
  std::cout << f() << g() << std::endl;

  std::vector<std::function<int(int)>> operations;
  operations.push_back([](int x) { return x + 1; });
  operations.push_back([](int x) { return x * 2; });

  // recursive ?
  auto factorial = [](this auto &&self, int n) -> int {
    return n > 1 ? n * self(n - 1) : 1;
  };

  std::cout << factorial(5) << std::endl;
}
