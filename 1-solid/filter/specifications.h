#pragma once

#include "specification.h"
#include "product.h"

struct ColorSpecification : ISpecification<Product> {
    Color color;
    explicit ColorSpecification(Color color) : color{color} {
    }
    bool IsSatisfied(const Product &item) const override {
        return item.color == color;
    }
};

struct SizeSpecification : ISpecification<Product> {
    Size size;
    explicit SizeSpecification(Size size) : size{size} {
    }
    bool IsSatisfied(const Product &item) const override {
        return item.size == size;
    }
};

struct AndSpecification : ISpecification<Product> {
    ISpecification<Product> &spec1;
    ISpecification<Product> &spec2;

    AndSpecification(ISpecification<Product> &spec1, ISpecification<Product> &spec2)
        : spec1{spec1}, spec2{spec2} {
    }

    bool IsSatisfied(const Product &item) const override {
        return spec1.IsSatisfied(item) && spec2.IsSatisfied(item);
    }
};
