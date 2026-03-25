#pragma once
#include "request.h"

namespace http {
class HttpRequestBuilder {
public:
    HttpRequestBuilder(const std::string& url);
    HttpRequestBuilder& add_method(const std::string& method);
    HttpRequestBuilder& add_body(const std::string& body);
    HttpRequestBuilder& add_headers(const HttpRequest::ParamData& headers);
    HttpRequestBuilder& add_query_args(const HttpRequest::ParamData& query_args);

    HttpRequest build();

private:
    HttpRequest req;

    friend std::ostream& operator<<(std::ostream&, const HttpRequestBuilder&);
};
}  // namespace http
