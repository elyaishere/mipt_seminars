#include "vector.h"
#include "tree.h"

#include <iostream>

using namespace example;

namespace example {
// Vector<int>::Iterator begin(const Vector<int>&) {
//     //
// }

// Vector<int>::Iterator end(const Vector<int>&) {
//     //
// }
}  // namespace example

int main() {
    Vector myvec{1, 2, 3, 4, 5};
    for (size_t i = 0; i < myvec.size(); ++i) {
        std::cout << myvec[i] << std::endl;
    }

    // https://en.cppreference.com/w/cpp/language/range-for.html
    std::cout << "range-based for" << std::endl;
    for (auto i : myvec) {
        std::cout << i << std::endl;
    }

    BinaryTree tree{1, 2, 3, 4, 5};
    //    1
    //   / \
    //  2   3
    // / \
    // 4  5

    for (auto i : tree)
        std::cout << i << std::endl;
    std::cout << "done\n";
}
