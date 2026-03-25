#pragma once

#include <vector>

template <typename T>
class ISpecification;

template <typename T>
using Items = std::vector<T>;

template <typename T, typename Derived>
struct IFilter {
    Items<T> Filter(const Items<T> &items, const ISpecification<T> &spec) {
        return static_cast<Derived *>(this)->FilterImpl(items, spec);
    }
};
