#pragma once
#include <string>

class Category {
public:
    enum class Type {
        Income,
        Outcome,
    };

private:
    const size_t m_id;
    const std::string m_name;
    Type m_type;
};
