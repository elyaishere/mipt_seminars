#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include <typeinfo>
#include <tuple>
#include <type_traits>

#include "movie_list.h"
#include "movie_finder.h"

class Injector {
public:
    template <typename Interface, typename Impl>
    void Bind() {
        bindings[typeid(Interface).hash_code()] = [this]() { return new Impl; };
    }

    template <typename T>
    T Create() {
        return CreateImpl<T>(typename T::inject{});
    }

private:
    // https://godbolt.org/z/nnrhbhc87
    template <typename T, typename... Deps>
    T CreateImpl(std::tuple<Deps...>) {
        if constexpr (sizeof...(Deps) == 0) {
            return T();
        } else {
            return T(FindDependency<std::remove_pointer_t<Deps>>()...);
        }
    }

    template <typename T>
    T* FindDependency() {
        return static_cast<T*>(bindings[typeid(T).hash_code()]());
    }

    std::unordered_map<size_t, std::function<void*()>> bindings;
};
