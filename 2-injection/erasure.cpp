#include <functional>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "movie.h"

using Movies = std::vector<std::shared_ptr<Movie>>;

class DummyFinder {
public:
    Movies FindAll() {
        return {std::make_shared<Movie>("E.T.", "Steven Spielberg"),
                std::make_shared<Movie>("Pulp Fiction", "Quentin Tarantino"),
                std::make_shared<Movie>("Kill Bill", "Quentin Tarantino")};
    }

private:
};

class MovieList {
public:
    MovieList(std::function<Movies()>&& finder) : finder(std::move(finder)) {
    }

    Movies MoviesDirectedBy(const std::string& director) {
        auto allMovies = finder();
        allMovies.erase(
            std::remove_if(allMovies.begin(), allMovies.end(),
                           [&director](const auto& item) { return item->director != director; }));
        return allMovies;
    }

private:
    std::function<Movies()> finder;
};

int main() {
    MovieList list([] {
        static DummyFinder impl;
        return impl.FindAll();
    });
    for (auto i : list.MoviesDirectedBy("Quentin Tarantino"))
        std::cout << i->name << std::endl;
}
