#include <cassert>
#include <iostream>
#include <string>
#include <variant>

struct Simple {
    Simple() {
        std::cout << "Simple::ctor\n";
    }
    Simple(const Simple&) = default;
    Simple& operator=(const Simple&) = default;
};

int main() {
    std::variant<int, float> v, w;
    v = 42;
    std::cout << std::get<int>(v) << std::endl;
    std::cout << std::get<int>(w) << std::endl;

    std::cout << "holds int: " << std::holds_alternative<int>(v) << std::endl;
    v = 42.f;
    std::cout << "holds int: " << std::holds_alternative<int>(v) << std::endl;

    // std::get<double>(v);
    // std::get<float>(v);

    std::variant<std::monostate, Simple> s;
}
