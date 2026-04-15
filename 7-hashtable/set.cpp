#include <unordered_set>
#include <string>

#include "../6-sequence/common.h"

using namespace std;

struct string_hash {
    using is_transparent = void;
    [[nodiscard]] size_t operator()(const char *txt) const {
        return hash<string_view>{}(txt);
    }
    [[nodiscard]] size_t operator()(string_view txt) const {
        return hash<string_view>{}(txt);
    }
    [[nodiscard]] size_t operator()(const string &txt) const {
        return hash<string>{}(txt);
    }
};

int main() {
    unordered_set<string /*, string_hash, equal_to<>*/> s{
        "Whatever is worth doing is worth doing well.",
        "People who don't think shouldn't talk.",
        "Begin at the beginning and go on till you come to the end; then stop.",
        "All that matters is what we do for each other.",
    };

    const char *look_for = "All that matters is what we do for each other.";
    size_t ITERATIONS = 1000'000;
    {
        TimeGuard _;
        for (auto i = 0uz; i < ITERATIONS; ++i) {
            s.emplace(look_for);
        }
    }

    {
        TimeGuard _;
        for (auto i = 0uz; i < ITERATIONS; ++i) {
            if (s.find(look_for) == s.end())
                s.emplace(look_for);
        }
    }
}
