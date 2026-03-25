#include "spline.h"
#include "math.h"
#include <new>

class Spline::SplineImpl {
public:
    SplineImpl(std::vector<double> x, std::vector<double> y, double a, double b)
        : x_{std::move(x)}, y_{std::move(y)}, d_(x_.size()) {
        auto ret = mySplineSnd(x_.data(), y_.data(), x_.size(), a, b, d_.data());
        if (ret == -1) {
            throw std::bad_alloc{};
        } else if (ret == -2) {
            throw std::invalid_argument{"Not monotonic"};
        }
    }
    double Interpolate(double x) const {
        if (double y; mySplintCube(x_.data(), y_.data(), d_.data(), d_.size(), x, &y)) {
            throw std::runtime_error{"Array is empty"};
        } else {
            return y;
        }
    }

private:
    std::vector<double> x_, y_, d_;
};

Spline::Spline(std::vector<double> x, std::vector<double> y, double a, double b)
    : impl_{std::make_unique<SplineImpl>(std::move(x), std::move(y), a, b)} {
}

Spline::~Spline() = default;

double Spline::Interpolate(double x) const {
    return impl_->Interpolate(x);
}
