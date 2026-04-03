#pragma once
#include <chrono>
#include <string>

class Account;
class Category;

class Operation {
public:
    enum class Type {
        Income,
        Outcome,
    };

private:
    const size_t m_id;
    Type m_type;
    uint64_t m_amount;
    std::chrono::system_clock::time_point m_tp;
    std::string m_description;

    const Account &m_account;
    const Category &m_category;
};
