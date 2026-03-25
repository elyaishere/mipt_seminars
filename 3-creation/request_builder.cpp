#include "request_builder.h"

namespace http {

HttpRequestBuilder::HttpRequestBuilder(const std::string &url) : req(url) {
}

HttpRequestBuilder &HttpRequestBuilder::add_method(const std::string &method) {
    req.method = method;
    return *this;
}

HttpRequestBuilder &HttpRequestBuilder::add_body(const std::string &body) {
    req.body = body;
    return *this;
}

HttpRequestBuilder &HttpRequestBuilder::add_headers(const HttpRequest::ParamData &headers) {
    req.headers = headers;
    return *this;
}

HttpRequestBuilder &HttpRequestBuilder::add_query_args(const HttpRequest::ParamData &query_args) {
    req.query_args = query_args;
    return *this;
}

HttpRequest HttpRequestBuilder::build() {
    return req;
}

std::ostream &operator<<(std::ostream &out, const HttpRequestBuilder &builder) {
    out << builder.req;
    return out;
}

}  // namespace http
