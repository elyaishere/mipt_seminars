#include <iostream>
#include <cassert>
#include <stdexcept>
#include <climits>
#include <cstdint>
#include <vector>
#include <iostream>
#include <type_traits>

/*
enum Unscoped1 { a, b, c=0 };
enum Unscoped2 { d, e, f=e+2 };

enum class Scoped1 { a, b, c=0 };
enum class Scoped2 { d, e, f=e+2 };
*/

enum e1 { a = 5000000000 };
enum class e2 {};
enum class e3 : unsigned {};
enum class e4 : int {};

int main() {
    constexpr bool e1_t = std::is_same_v<std::underlying_type_t<e1>, int>;
    constexpr bool e2_t = std::is_same_v<std::underlying_type_t<e2>, int>;
    constexpr bool e3_t = std::is_same_v<std::underlying_type_t<e3>, int>;
    constexpr bool e4_t = std::is_same_v<std::underlying_type_t<e4>, int>;

    std::cout << "underlying type for 'e1' is " << (e1_t ? "int" : "non-int") << '\n'
              << "underlying type for 'e2' is " << (e2_t ? "int" : "non-int") << '\n'
              << "underlying type for 'e3' is " << (e3_t ? "int" : "non-int") << '\n'
              << "underlying type for 'e4' is " << (e4_t ? "int" : "non-int") << '\n';

    std::cout << typeid(std::underlying_type_t<e1>).name();
}

/*
enum color { red, yellow, green=20, blue };
color c = 1;    // error: int -> color
int i = yellow; // ok: color -> int

enum class Color { red, yellow, green };
int x = Color::red; // error: Color -> int

enum direction { left = 'l', right = 'r' };
void g() {
    direction d;          // OK
    d = left;             // OK
    d = direction::right; // OK
}

enum class altitude { high = 'h', low = 'l' };
void h() {
    altitude a;        // OK
    a = high;          // error: high not in scope
    a = altitude::low; // OK
}

enum {};
enum {fast = 'f', slow = 's'};
// fast;
*/
