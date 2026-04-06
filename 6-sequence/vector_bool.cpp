#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

int main() {
    std::vector<int> vec;
    std::cout << typeid(vec[0]).name() << std::endl;

    std::vector<bool> vecb{1, 0, 1};
    std::cout << typeid(vecb[0]).name() << std::endl;
}

// template <class _Allocator>
// class vector<bool, _Allocator> {
// private:
//     using reference = __bit_reference<vector>;
//     static const unsigned __bits_per_word = static_cast<unsigned>(sizeof(size_t) * CHAR_BIT);

//     size_t __begin_;
//     size_t __size_;
// public:
//     reference operator[](size_type __pos) {
//         return reference(__begin_ + __pos / __bits_per_word, size_t(1) << __pos %
//         __bits_per_word);
//     }
// };

// template <class _Cp>
// class __bit_reference {
//   size_t* __seg_;
//   size_t __mask_;

// public:
//     __bit_reference(size_t* seg, size_t mask);
//     operator bool() const {
//         return static_cast<bool>(*__seg_ & __mask_);
//     }
// };
