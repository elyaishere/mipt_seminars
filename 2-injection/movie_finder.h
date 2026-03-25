#pragma once
#include <vector>
#include <memory>

#include "movie.h"

class IMovieFinder {
public:
    virtual std::vector<std::shared_ptr<Movie>> FindAll() = 0;
    virtual ~IMovieFinder() = default;
};

/*------------------------------------------------------------------*/

class DummyFinder : public IMovieFinder {
public:
    using inject = std::tuple<>;
    std::vector<std::shared_ptr<Movie>> FindAll() override {
        return {std::make_shared<Movie>("E.T.", "Steven Spielberg"),
                std::make_shared<Movie>("Pulp Fiction", "Quentin Tarantino"),
                std::make_shared<Movie>("Kill Bill", "Quentin Tarantino")};
    }

private:
};
