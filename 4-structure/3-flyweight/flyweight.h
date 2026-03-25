#pragma once

#include <utility>
#include <cstddef>

template <typename>
class static_factory;

template <typename>
class factory;

template <typename T>
class flyweight final {
public:
    using factory_t = factory<T>;

    flyweight() = default;

    template <typename TT>
    flyweight(TT&& obj) : m_factory(static_factory<T>::get()), m_id(0) {
        auto fw = (*m_factory)(std::forward<TT>(obj));
        fw.m_factory = nullptr;
        m_id = fw.m_id;
    }

    flyweight(flyweight const& fw) : m_factory(fw.m_factory), m_id(fw.m_id) {
        if (m_factory)
            m_factory->inc(m_id);
    }

    flyweight(flyweight&& fw) : m_factory(fw.m_factory), m_id(fw.m_id) {
        fw.m_factory = nullptr;
        fw.m_id = 0;
    }

    flyweight& operator=(flyweight const& fw) {
        flyweight(fw).swap(*this);
        return *this;
    }

    flyweight& operator=(flyweight&& fw) {
        flyweight(std::move(fw)).swap(*this);
        return *this;
    }

    ~flyweight() {
        if (m_factory)
            m_factory->dec(m_id);
    }

    const T& get() const {
        return (*m_factory)[m_id]->obj;
    }

    T& get() {
        return (*m_factory)[m_id]->obj;
    }

private:
    friend factory_t;
    flyweight(factory_t* f, typename factory_t::id_t id) : m_factory(f), m_id(id) {
    }

    void swap(flyweight& fw) noexcept {
        using namespace std;
        swap(m_factory, fw.m_factory);
        swap(m_id, fw.m_id);
    }

    factory_t* m_factory{nullptr};
    typename factory_t::id_t m_id{0};
};
