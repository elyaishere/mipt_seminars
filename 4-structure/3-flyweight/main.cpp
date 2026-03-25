#include <string>

#include "factory.h"
#include "flyweight.h"

#include <iostream>

struct user_entry {
    std::string first_name;
    std::string last_name;
    int age;
};

// std::vector<user_entry> users(10'000);

// struct user_entry
// {
//   flyweight<std::string> first_name;
//   flyweight<std::string> last_name;
//   int                    age;
// };

int main() {
    std::string const doe{"Doe"};
    user_entry JohnDoe{std::string{"John"}, std::string{"Doe"}, 21},
        JaneDoe{std::string{"Jane"}, doe, 21};

    std::cout << &JohnDoe.last_name << ' ' << &JaneDoe.last_name << std::endl;
    // std::cout << JohnDoe.last_name.get() << ' ' << JaneDoe.last_name.get() << std::endl;
    // std::cout << &JohnDoe.last_name.get() << ' ' << &JaneDoe.last_name.get() << std::endl;
}
