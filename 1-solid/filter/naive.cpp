#include <string>
#include <vector>

enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product {
    std::string name;
    Color color;
    Size size;
};

struct ProductFilter {
    using Items = std::vector<Product>;

    Items ByColor(const Items& products, Color color) {
        Items result;
        for (auto& p : products) {
            if (p.color == color)
                result.push_back(p);
        }
        return result;
    }

    Items BySize(const Items& products, Size size) {
        Items result;
        for (auto& p : products) {
            if (p.size == size)
                result.push_back(p);
        }
        return result;
    }
    // color AND size?
};
