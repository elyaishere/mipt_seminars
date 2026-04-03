#pragma once
#include "storage.h"

#include <unordered_map>
#include <memory>

template <typename T>
class InMemoryStorage : public Storage<T> {
public:
    void Add(const std::shared_ptr<T>& entity) override;
    void Remove(size_t id) override;
    void Update(const std::shared_ptr<T>& entity) override;

private:
    std::unordered_map<size_t, std::shared_ptr<T>> m_data;
};
