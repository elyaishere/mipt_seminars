#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

union S {
    std::int32_t n;      // 4
    std::uint16_t s[2];  // 4
    std::uint8_t c;      // 1
};

union SU {
    std::string str;
    std::vector<int> vec;
    ~SU() {
    }
};

struct UnionClass {
    enum { CHAR, INT, DOUBLE } tag;
    union {
        char c;
        int i;
        double d;
    };
};

void print_s(const UnionClass& s) {
    switch (s.tag) {
        case UnionClass::CHAR:
            std::cout << s.c << '\n';
            break;
        case UnionClass::INT:
            std::cout << std::dec << s.i << '\n';
            break;
        case UnionClass::DOUBLE:
            std::cout << s.d << '\n';
            break;
    }
}

int main() {
    std::cout << sizeof(S) << '\n';

    S s1 = {0x12345678};
    std::cout << std::hex << "s1.n = " << s1.n << '\n';

    s1.s[0] = 0x0011;
    // UB
    std::cout << "s1.c is now " << +s1.c << '\n' << "s1.n is now " << s1.n << '\n';

    // --------------------------------------------------
    SU s2 = {"Hello, world"};
    std::cout << "s2.str = " << s2.str << '\n';
    s2.str.~basic_string();
    new (&s2.vec) std::vector<int>;
    s2.vec.push_back(10);
    std::cout << s2.vec.size() << '\n';
    s2.vec.~vector();
    // --------------------------------------------------
    // UnionClass s = {UnionClass::CHAR, 'a'};
    // print_s(s);
    // s.tag = UnionClass::INT;
    // s.i = 123;
    // print_s(s);
}
