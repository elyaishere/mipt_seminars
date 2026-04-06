#include <vector>
#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> coll1;
    vector<int> coll2;

    for (int i = 1; i <= 9; ++i) {
        coll1.push_back(i);
    }

    // copy(coll1.begin(), coll1.end(), coll2.begin());

    copy(coll1 .begin(), coll1.end(), back_inserter(coll2));

    for (auto i = coll2.rbegin(); i != coll2.rend(); ++i)
        std::cout << *i << ' ';
    std::cout << std::endl;
}
