#pragma once

#include <typeinfo>
#include <unordered_map>

#include "movie_finder.h"

class Locator {
public:
    static Locator& Instance() {
        static Locator instance;
        return instance;
    }

    Locator(const Locator&) = delete;
    Locator& operator=(const Locator&) = delete;

    template <typename T>
    std::shared_ptr<T> GetService() const {
        auto service_ptr = services.at(typeid(T).hash_code());
        return std::shared_ptr<T>(service_ptr, static_cast<T*>(service_ptr.get()));
    }

    template <typename T>
    void SetService(T* service_ptr) {
        services[typeid(T).hash_code()] = std::shared_ptr<T>(service_ptr);
    }

protected:
    Locator() = default;
    ~Locator() = default;

private:
    std::unordered_map<size_t, std::shared_ptr<void>> services;
};
