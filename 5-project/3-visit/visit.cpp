#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

// explicit deduction guide (not needed as of C++20)
// template<class... Ts>
// overloaded(Ts...) -> overloaded<Ts...>;

int main() {
    using value_t = std::variant<int, long, double, std::string>;
    std::vector<value_t> vec = {10, 15l, 1.5, "hello"};

    for (auto& v : vec) {
        std::visit([](auto&& arg) { std::cout << arg; }, v);

        value_t w = std::visit([](auto&& arg) -> value_t { return arg + arg; }, v);
        std::cout << ". After doubling, variant holds ";
        std::visit(
            [](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, int>)
                    std::cout << "int with value " << arg << '\n';
                else if constexpr (std::is_same_v<T, long>)
                    std::cout << "long with value " << arg << '\n';
                else if constexpr (std::is_same_v<T, double>)
                    std::cout << "double with value " << arg << '\n';
                else if constexpr (std::is_same_v<T, std::string>)
                    std::cout << "std::string with value " << std::quoted(arg) << '\n';
                else
                    static_assert(false, "non-exhaustive visitor!");
            },
            w);
    }

    for (auto& v : vec) {
        std::visit(overloaded{[](auto arg) { std::cout << arg << ' '; },
                              [](double arg) { std::cout << std::fixed << arg << ' '; },
                              [](const std::string& arg) { std::cout << std::quoted(arg) << ' '; }},
                   v);
    }
}
