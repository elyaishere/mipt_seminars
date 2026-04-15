#include <map>
#include <unordered_map>
#include <string>
#include <string_view>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace string_view_literals;

void* operator new(std::size_t sz) {
    cout << "Allocating: " << sz << '\n';
    return malloc(sz);
}

void operator delete(void* ptr) noexcept {
    free(ptr);
}

struct string_hash {
    using is_transparent = void;
    [[nodiscard]] size_t operator()(const char* txt) const {
        return hash<string_view>{}(txt);
    }
    [[nodiscard]] size_t operator()(string_view txt) const {
        return hash<string_view>{}(txt);
    }
    [[nodiscard]] size_t operator()(const string& txt) const {
        return hash<string>{}(txt);
    }
};

int main() {
    map<string, int, std::less<> > intMap{
        {"Take some more tea", 1},
        {"I've had nothing yet, so I can't take more.", 2},
        {"You mean you can't take less, it's very easy to take more than nothing.", 3}};

    cout << "Lookup in intMap with by const char*:\n";
    cout << intMap.contains("I've had nothing yet, so I can't take more.") << '\n';

    // cout << "Lookup in intMap with by string_view:\n";
    // cout << intMap.contains("I've had nothing yet, so I can't take more."sv) << '\n';

    // less<string>
    // less<>

    unordered_map<string, int, string_hash, equal_to<> > intHashMap{
        {"Take some more tea", 1},
        {"I've had nothing yet, so I can't take more.", 2},
        {"You mean you can't take less, it's very easy to take more than nothing.", 3}};

    cout << "Lookup in intHashMap with by const char*:\n";
    cout << intHashMap.contains("I've had nothing yet, so I can't take more."sv) << '\n';
}
