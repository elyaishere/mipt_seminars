#include <iostream>

#include "movie_list.h"
#include "injector.h"

int main() {

    // Injector
    Injector injector;
    injector.Bind<IMovieFinder, DummyFinder>();
    auto list = injector.Create<MovieList>();
    for (auto i : list.MoviesDirectedBy("Quentin Tarantino"))
        std::cout << i->name << std::endl;

    // Locator
    // auto &locator = Locator::Instance();
    // locator.SetService(static_cast<IMovieFinder *>(new DummyFinder));
    // MovieList list;
    // for (auto i : list.MoviesDirectedBy("Quentin Tarantino"))
    //     std::cout << i->name << std::endl;
}
