#include "product_filter.h"
#include "filter.h"
#include "specifications.h"

#include <iostream>
#include <vector>

int main() {
    std::vector<Product> products{
        {"Apple", Color::Green, Size::Medium},
        {"Lime", Color::Green, Size::Small},
        {"Tomato", Color::Red, Size::Medium},
    };

    ProductFilter pf;
    ColorSpecification is_green(Color::Green);
    SizeSpecification is_small(Size::Small);
    AndSpecification and_spec{is_green, is_small};

    for (auto& x : pf.Filter(products, and_spec))
        std::cout << x.name << " is green and small\n";
}
