#include "request.h"
#include "request_builder.h"

using namespace http;

int main() {
    HttpRequest req(
        "/", "GET", "",
        {{"Host", "google.com"}});  // порядок аргументов, нельзя скипнуть, можно спутать аргументы
    std::cout << req << std::endl;

    HttpRequestBuilder builder("/");
    builder.add_method("GET").add_headers({{"Host", "google.com"}});

    std::cout << builder << std::endl;
}