#include <iostream>
#include <vector>

struct Simple {
    Simple() {
        std::cout << "ctor\n";
    }

    Simple(const Simple&) {
        std::cout << "copy\n";
    }

    Simple(Simple&&) noexcept {
        std::cout << "move\n";
    }

    Simple& operator=(const Simple&) {
        std::cout << "copy\n";
        return *this;
    }

    Simple& operator=(Simple&&) {
        std::cout << "move\n";
        return *this;
    }

    ~Simple() {
        std::cout << "dtor\n";
    }
};

using namespace std;

int main() {
    vector<Simple> vec(4);
    vec.insert(vec.begin(), Simple());
}
