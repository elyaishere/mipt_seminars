#pragma once
#include <cstddef>
#include <cassert>
#include <cstring>
#include <iostream>

// deque
// [[block] [block] [block] [block] [block]]
//           ^start          ^end
// ^first                                  ^first+cap

class GapBuffer {
public:
    GapBuffer(const GapBuffer&) = delete;
    GapBuffer& operator=(const GapBuffer&) = delete;

    GapBuffer(size_t size) {
        if (size) {
            _buf = new char[size];
            _size = size;
        }
    }

    ~GapBuffer() {
        delete _buf;
    }

    void print_raw() const {
        _print(true);
    }

    void print() const {
        _print(false);
    }

    void step_forward() {
        // [         |               |  ]
        //    presize^<-----gap----->^postsize
        // [          |               | ]
        //     presize^<-----gap----->^postsize
        if (_postsize > 0) {
            _buf[_presize] = _buf[_size - _postsize];
            ++_presize;
            --_postsize;
        }
    }

    void step_backward() {
        // [         |               |  ]
        //    presize^<-----gap----->^postsize
        // [        |               |   ]
        //   presize^<-----gap----->^postsize
        if (_presize > 0) {
            _buf[_size - _postsize - 1] = _buf[_presize - 1];
            ++_postsize;
            --_presize;
        }
    }

    void move(size_t pos) {
        if (pos > _presize) {
            for (auto i = pos - _presize; i--;) {
                step_forward();
            }
        } else {
            for (auto i = _presize - pos; i--;) {
                step_backward();
            }
        }
    }

    void insert(const char* s) {
        // [         |               |  ]
        //    presize^<-----gap----->^postsize
        // [         [s   ]|         |  ]
        //          presize^<--gap-->^postsize
        while (*s != '\0') {
            insert(*s);
            ++s;
        }
    }

    void insert(char c) {
        // [         |               |  ]
        //    presize^<-----gap----->^postsize
        // [         c|              |  ]
        //     presize^<----gap----->^postsize
        if (_presize + _postsize == _size) {
            expand();
        }
        _buf[_presize++] = c;
    }

private:
    void expand() {
        // [         ||  ]
        //    presize^^postsize
        // [         |               |  ]
        //    presize^<-----gap----->^postsize
        auto newsize = std::max(_size * 2, 1uz);
        auto newbuf = new char[newsize];
        memcpy(newbuf, _buf, _presize);
        memcpy(newbuf + newsize - _postsize, _buf + _size - _postsize, _postsize);
        delete _buf;

        _buf = newbuf;
        _size = newsize;
    }

    void _print(bool raw) const {
        size_t i{0};
        for (; i < _presize; ++i)
            std::cout << _buf[i];

        if (raw) {
            std::cout << '[';
            for (; i < _size - _postsize; ++i)
                std::cout << ' ';
            std::cout << ']';
        } else
            i = _size - _postsize;

        for (; i < _size; ++i)
            std::cout << _buf[i];

        std::cout << std::endl;
    }

    char* _buf{nullptr};
    size_t _size{0}, _presize{0}, _postsize{0};
    // [         |                    |  ]
    //    presize^<--------gap------->^postsize
};
