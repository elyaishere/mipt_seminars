#include <iostream>
#include <vector>

#include "common.h"

using namespace std;

int main() {
    // insertion
    size_t INSERT_NUMBER = 10000'000;
    vector<int> elements;
    {
        elements.clear();
        elements.shrink_to_fit();
        // warmup

        for (int i = 0; i < 2 * INSERT_NUMBER; ++i)
            elements.push_back(i);
    }

    {
        elements.clear();
        elements.shrink_to_fit();
        cout << "push_back\n";
        TimeGuard _;
        for (int i = 0; i < INSERT_NUMBER; ++i)
            elements.push_back(i);
    }

    {
        elements.clear();
        elements.shrink_to_fit();
        elements.reserve(INSERT_NUMBER);
        cout << "push_back with reserve\n";
        TimeGuard _;
        for (int i = 0; i < INSERT_NUMBER; ++i)
            elements.push_back(i);
    }

    {
        elements.clear();
        elements.shrink_to_fit();
        cout << "insert(begin)\n";
        TimeGuard _;
        for (int i = 0; i < INSERT_NUMBER; ++i)
            elements.insert(elements.begin(), i);
    }
    // iteration
    {
        vector<int> elements(10'000'000);
        cout << "iteration\n";
        TimeGuard _;
        for (auto& i : elements) {
            asm volatile("" : "+r,m"(i));
        }
    }
}
