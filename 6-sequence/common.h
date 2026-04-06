#pragma once
#include <iostream>
#include <chrono>

struct TimeGuard {
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;

    TimeGuard() : tp(Clock::now()) {
    }

    ~TimeGuard() {
        std::cout << "elapsed "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - tp)
                  << " ms" << std::endl;
    }

private:
    TimePoint tp;
};
