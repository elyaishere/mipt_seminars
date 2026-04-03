#pragma once
#include <string>
#include <vector>

class ParsedData {};

class Importer {
public:
    virtual ~Importer() = default;
    void Import(const std::string& filename) {
        auto parsed = Parse(filename);
        ImportAccounts(parsed);
        // ..
    }

protected:
    virtual ParsedData Parse(const std::string& filename) = 0;
    virtual void ImportAccounts(const ParsedData&) = 0;
    virtual void ImportCategories(const ParsedData&) = 0;
    virtual void ImportOperations(const ParsedData&) = 0;
};

class CSVImporter : public Importer {};
