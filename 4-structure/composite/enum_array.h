#pragma once
#include <cstdio>
#include <cstdint>
#include <type_traits>
#include <array>

class Node;
class Config;
class FilterList;

template <typename Enum, typename T>
class EnumArray {
    static_assert(std::is_enum_v<Enum>);

public:
    constexpr T& operator[](Enum e) noexcept {
        return data[static_cast<size_t>(e)];
    }
    constexpr const T& operator[](Enum e) const noexcept {
        return data[static_cast<size_t>(e)];
    }
    auto begin() const noexcept {
        return data.begin();
    }
    auto end() const noexcept {
        return data.end();
    }

private:
    static constexpr size_t size = static_cast<size_t>(Enum::size);
    std::array<T, size> data;
};

class FilterManager {
public:
    FilterManager(const Config&);
    void ParseFilterListFromConfig(FilterList&);

private:
    enum ParamIndex : uint8_t { types = 0, names = 1, size };
    enum HandlerIndex : uint8_t {
        states = 0,
        flags = 1,
        param_ops,
        param_ids,
        filters,
        flt_ops,
        flt_flags,
        size
    };

    EnumArray<ParamIndex, const Node*> params;
    EnumArray<HandlerIndex, const Node*> handler;
};
