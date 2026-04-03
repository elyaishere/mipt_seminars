#pragma once
#include <string>

class Account {
private:
    const size_t m_id;
    const std::string m_name;
    int64_t m_balance{0};
};
