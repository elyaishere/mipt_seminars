#pragma once
#include <cstdio>
#include <utility>
#include <unordered_map>
#include <functional>

#include "flyweight.h"

template <typename T>
class factory {
    friend flyweight<T>;

    using hash_t = size_t;
    using id_t = size_t;

    struct Item final {
        id_t const id{};
        size_t refcount{};
        T obj;

        template <typename TT>
        Item(id_t i, size_t ref, TT&& o) : id(i), refcount(ref), obj(std::forward<TT>(o)) {
        }
    };

public:
    template <typename TT>
    flyweight<T> operator()(TT&& obj) {
        id_t id = 0;
        if (contains(obj, id)) {
            ++(m_index[id]->refcount);
            return flyweight<T>(this, id);
        }

        auto hash = std::hash<std::decay_t<TT>>{}(obj);
        auto it = m_store.emplace(hash, Item(m_counter++, 1uz, std::forward<TT>(obj)));

        Item* elem = &it->second;
        m_index.emplace(elem->id, elem);
        return flyweight<T>(this, elem->id);
    }

    Item* operator[](id_t id) const {
        auto it = m_index.find(id);
        return (it != m_index.end()) ? it->second : nullptr;
    }

private:
    using store_t = std::unordered_multimap<hash_t, Item>;
    using index_t = std::unordered_map<id_t, Item* const>;

    size_t m_counter{};
    store_t m_store;
    index_t m_index;

    template <typename TT>
    bool contains(TT&& obj, id_t& id) const {
        auto range = m_store.equal_range(std::hash<std::decay_t<TT>>{}(obj));
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second.obj == obj) {
                id = it->second.id;
                return true;
            }
        }
        return false;
    }

    void inc(id_t id) {
        auto it = m_index.find(id);
        if (it != m_index.end()) {
            ++(it->second->refcount);
        }
    }
    void dec(id_t id) {
        auto it = m_index.find(id);
        if (it == m_index.end() || --(it->second->refcount))
            return;
        Item* ptr = it->second;
        m_index.erase(it);
        auto range = m_store.equal_range(std::hash<T>{}(ptr->obj));
        for (auto store_it = range.first; store_it != range.second; ++store_it) {
            if (id == store_it->second.id) {
                m_store.erase(store_it);
                return;
            }
        }
    }
};

template <typename T>
class static_factory {
public:
    static factory<T>* get() {
        static factory<T> factory;
        return &factory;
    }
};
