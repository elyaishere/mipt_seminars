#pragma once

#include "filter.h"
#include "product.h"
#include "specification.h"

struct ProductFilter : IFilter<Product, ProductFilter> {
    friend class IFilter<Product, ProductFilter>;
    using Products = Items<Product>;

private:
    Products FilterImpl(const Products &items, const ISpecification<Product> &spec) {
        Products result;
        for (const auto &p : items) {
            if (spec.IsSatisfied(p))
                result.push_back(p);
        }
        return result;
    }
};
