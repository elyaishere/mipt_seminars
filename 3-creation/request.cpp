#include "request.h"
#include "request_builder.h"

namespace http {

HttpRequest::HttpRequest(const std::string &url, const std::string &method, const std::string &body,
                         const ParamData &headers, const ParamData &query_args)
    : method(method), url(url), body(body), headers(headers), query_args(query_args) {
}

std::ostream &operator<<(std::ostream &out, const HttpRequest &req) {
    out << req.method << ' ' << req.url << (req.query_args.empty() ? "" : "?");
    for (auto it = req.query_args.begin(); it != req.query_args.end();) {
        const auto &[k, v] = *it;
        ++it;
        out << k << '=' << v << (it == req.query_args.end() ? "" : "&");
    }
    out << "HTTP/1.1\r\n";
    for (const auto &[k, v] : req.headers)
        out << k << ':' << v << "\r\n";
    out << "\r\n";
    out << req.body;
    return out;
}
}  // namespace http
