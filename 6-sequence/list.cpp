#include <iostream>
#include <list>
#include "common.h"

using namespace std;

int main() {
    // insertion
    size_t INSERT_NUMBER = 100'000;
    {
        list<int> elements;
        // warmup

        for (int i = 0; i < 2 * INSERT_NUMBER; ++i)
            elements.push_back(i);
    }

    {
        list<int> elements;
        cout << "push_back\n";
        TimeGuard _;
        for (int i = 0; i < INSERT_NUMBER; ++i)
            elements.push_back(i);
    }

    {
        list<int> elements;
        cout << "push_front\n";
        TimeGuard _;
        for (int i = 0; i < INSERT_NUMBER; ++i)
            elements.push_front(i);
    }
    // iteration
    {
        list<int> elements(10'000'000);
        cout << "iteration\n";
        TimeGuard _;
        for (auto& i : elements) {
            asm volatile("" : "+r,m"(i));
        }
    }
}
