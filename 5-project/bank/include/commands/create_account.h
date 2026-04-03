#pragma once
#include <string>
#include "command.h"

class AccountFacade;

class CreateAccount : public Command {
public:
    CreateAccount(const AccountFacade &, const std::string &name);
    void Do() override;
    void Undo() override;

private:
    std::string m_name;
    size_t m_id;
    const AccountFacade &m_accounts;
};
