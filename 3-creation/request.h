#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
/*
1) много конструкторов и параметров
2) порядок аргументов в конструкторе важен, указываем даже ненужные, можно ошибиться с номером
аргумента 3) модификация 1: add_smth -> Builder & 4) всё еще возможно явно создать объект класса =>
конструктор в protected 5)
```cpp
std::unique_ptr<HttpRequestBuilder> HttpRequest::build(const std::string &url);
HttpRequestBuilder::operator HttpRequest() const; // либо метод build внутри билдера, который
возвращает реквест
```*/

namespace http {
class HttpRequestBuilder;

class HttpRequest {
    friend class HttpRequestBuilder;
    friend std::ostream &operator<<(std::ostream &, const HttpRequest &);

public:
    using ParamData = std::unordered_map<std::string, std::string>;

    HttpRequest(const std::string &url, const std::string &method = "GET",
                const std::string &body = "", const ParamData &headers = {},
                const ParamData &query_args = {});

    // alternatively
    // HttpRequest(const std::string &url);
    // HttpRequest(const std::string &url, const std::string &method);
    // HttpRequest(const std::string &url, const std::string &method, const std::string &body);
    // HttpRequest(const std::string &url, const std::string &method, const std::string &body, const
    // Parameters &headers); HttpRequest(const std::string &url, const std::string &method, const
    // std::string &body, const Parameters &headers, const Parameters &query_args);

private:
    std::string method /* GET(default)/POST/PUT */, url /* required */, body /* may be empty */;
    std::unordered_map<std::string, std::string> headers /* may be empty */,
        query_args /* may be empty */;
};

std::ostream &operator<<(std::ostream &out, const HttpRequest &);
}  // namespace http
