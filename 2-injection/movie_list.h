#pragma once
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

#include "movie.h"
#include "movie_finder.h"
#include "service_locator.h"

class MovieList {
public:
    using inject = std::tuple<IMovieFinder *>;

    MovieList(IMovieFinder *finder) : finder(finder) {
    }

    std::vector<std::shared_ptr<Movie>> MoviesDirectedBy(const std::string &director) {
        auto allMovies = finder->FindAll();
        allMovies.erase(
            std::remove_if(allMovies.begin(), allMovies.end(),
                           [&director](const auto &item) { return item->director != director; }));
        return allMovies;
    }

private:
    std::shared_ptr<IMovieFinder> finder;
};
