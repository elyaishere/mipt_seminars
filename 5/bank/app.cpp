#include "include/storage/storage.h"
#include "include/storage/cache.h"
#include "include/entity/account.h"
#include "include/entity/category.h"
#include "include/entity/operation.h"
#include "include/commands/manager.h"
#include "include/commands/create_account.h"
#include "include/facade/account_facade.h"

int main() {
    auto accounts = std::make_shared<Storage<Account>>();
    auto categories = std::make_shared<Storage<Category>>();
    auto operations = std::make_shared<Storage<Operation>>();

    auto cached_accounts = std::make_shared<Cache<Account>>(accounts);

    AccountFacade account_facade(cached_accounts);

    CommandManager cmd_manager;
    cmd_manager.Do(std::make_unique<CreateAccount>(account_facade, "main account"));
    // cmd_manager.Undo();
};
