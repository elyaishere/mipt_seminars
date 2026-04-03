#pragma once

#include <algorithm>
#include <cstdio>
#include <initializer_list>

namespace example {
template <typename T>
class Vector {
    friend void swap(Vector &lhs, Vector &rhs);

public:
    class Iterator {
    public:
        explicit Iterator(T *ptr) : ptr{ptr} {
        }
        bool operator==(const Iterator &other) const = default;
        Iterator &operator++() {
            ++ptr;
            return *this;
        }
        T &operator*() {
            return *ptr;
        }

    private:
        T *ptr;
    };

    Vector() = default;
    Vector(std::initializer_list<T> elems) {
        try {
            m_data = new T[elems.size()];
            std::copy(elems.begin(), elems.end(), m_data);
            m_size = elems.size();
        } catch (...) {
            delete m_data;
            m_data = nullptr;
        }
    }
    Vector(size_t s) {
        try {
            m_data = new T[s];
            m_size = s;
        } catch (...) {
            delete m_data;
            m_data = nullptr;
        }
    }
    Vector(const Vector &other) {
        m_data = new T[other.m_size];
        try {
            std::copy(other.m_data, other.m_data + other.m_size, m_data);
            m_size = other.m_size;
        } catch (...) {
            delete m_data;
            m_data = nullptr;
        }
    }
    Vector(Vector &&other) {
        using namespace std;
        swap(m_data, other.m_data);
        swap(m_size, other.m_size);
    }
    Vector &operator=(const Vector &other) {
        Vector tmp(other);
        swap(tmp, *this);
        return *this;
    }
    Vector &operator=(Vector &&other) {
        swap(other, *this);
        return *this;
    }

    auto size() const noexcept {
        return m_size;
    }
    const T &operator[](size_t idx) const noexcept {
        return m_data[idx];
    }
    T &operator[](size_t idx) noexcept {
        return m_data[idx];
    }

    Iterator begin() {
        return Iterator{m_data};
    }
    Iterator end() {
        return Iterator{m_data + m_size};
    }

private:
    T *m_data{nullptr};
    size_t m_size{0};
};

template <typename T>
void swap(Vector<T> &lhs, Vector<T> &rhs) noexcept {
    using namespace std;
    swap(lhs.m_data, rhs.m_data);
    swap(lhs.m_size, rhs.m_size);
}
}  // namespace example
