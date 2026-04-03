#pragma once
#include <string>
#include <vector>

class Account;
class Category;
class Operation;

class Exporter {
public:
    virtual ~Exporter() = default;
    virtual void Visit(const Account&) = 0;
    virtual void Visit(const Category&) = 0;
    virtual void Visit(const Operation&) = 0;
};
