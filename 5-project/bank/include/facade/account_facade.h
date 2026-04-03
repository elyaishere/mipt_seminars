#pragma once
#include "../storage/storage.h"
#include "../entity/account.h"
#include <memory>

class AccountFacade {
public:
    explicit AccountFacade(std::shared_ptr<Storage<Account>>);
    std::shared_ptr<Account> CreateAccount(const std::string& name);
    void Deposit(size_t id, uint64_t amount);
    void Withdraw(size_t id, uint64_t amount);
    void DeleteAccount(size_t id);

private:
    std::shared_ptr<Storage<Account>> m_storage;
};
