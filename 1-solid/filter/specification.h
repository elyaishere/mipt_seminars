#pragma once

template <typename T>
struct ISpecification {
    virtual bool IsSatisfied(const T &item) const = 0;
};
