#pragma once
#include <string>
#include "account.h"
#include "category.h"
#include "operation.h"

class Factory {
private:
    static size_t GenId();

public:
    static std::shared_ptr<Account> CreateAccount(const std::string& name);
    static std::shared_ptr<Category> CreateCategory(const std::string& name, Category::Type);
    static std::shared_ptr<Operation> CreateOperation(const std::string& name, Operation::Type,
                                                      size_t amount,
                                                      const std::string& description = "");
};
