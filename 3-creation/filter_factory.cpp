#include <vector>
#include <tuple>
#include <map>
#include <string>
#include <iostream>

using Pixel = std::tuple<double, double, double>;
using Image = std::array<std::array<Pixel, 3>, 3>;

class Filter {
public:
    virtual void Apply(Image& img) = 0;
    virtual ~Filter() = default;
};

class Greyscale : public Filter {
public:
    virtual void Apply(Image& img) override {
        std::cout << "greyscale filter\n";
    }
};

class Negative : public Filter {
public:
    virtual void Apply(Image& img) override {
        std::cout << "negative filter\n";
    }
};

//...

struct FilterDescriptor {
    std::string name;
};

class FilterFactory {
    using PFilterProducer = Filter* (*)(const FilterDescriptor& fd);

public:
    Filter* MakeFilter(const FilterDescriptor& fd) {
        auto it = filterProducers_.find(fd.name);
        if (it == filterProducers_.end())
            throw std::runtime_error("unknown filter");
        return it->second(fd);
    }

    void RegisterProducer(std::string_view name, PFilterProducer f) {
        filterProducers_.emplace(std::string{name}, f);
    }

private:
    std::map<std::string, PFilterProducer> filterProducers_;
};

Filter* GreyscaleFilterMaker(const FilterDescriptor& fd) {
    return new Greyscale();
}
