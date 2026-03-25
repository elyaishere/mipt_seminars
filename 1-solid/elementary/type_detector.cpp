#include <initializer_list>

template <typename T>
class DT;

int main() {
    auto x1 = {1, 2, 3};  // initializer_list
    auto x2{1};           // initializer_list ? int ?
    auto x3 = {1};        // int ? initializer_list ?

    DT<decltype(x1)> _1;
    DT<decltype(x2)> _2;
    DT<decltype(x3)> _3;
}
