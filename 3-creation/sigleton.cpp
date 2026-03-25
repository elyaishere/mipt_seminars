class Database {
public:
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    static Database& Create() {
        static Database base;
        return base;
    }

private:
    Database() = default;
};
