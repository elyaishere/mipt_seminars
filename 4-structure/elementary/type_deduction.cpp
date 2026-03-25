#include <iostream>
#include <string>

template <typename T>
void printV(T arg) {
}

template <typename T>
void printR(const T &arg) {
}

template <typename T>
void outR(T &arg) {
}

template <typename T>
void passR(T &&arg) {
}

int main() {
    {
        std::string returnString();
        std::string s = "hi";
        /*
        void printV (std::string arg) { }
        */
        printV(s);
        printV(std::string("hi"));
        printV(returnString());
        printV(std::move(s));
        /* ------------------------------ */
        std::string const c = "hi";
        printV(c);
        printV("hi");
        int arr[4];
        printV(arr);
    }
    {
        std::string returnString();
        std::string s = "hi";
        /*
            void printR(const std::string &arg) { }
        */
        printR(s);
        printR(std::string("hi"));
        printR(returnString());
        printR(std::move(s));
        /* ------------------------------ */
        std::string const c = "hi";
        printR(c);
        printR("hi");
        int arr[4];
        printR(arr);
    }
    {
        std::string returnString();
        std::string const returnConstString();
        std::string s = "hi";
        std::string const c = "hi";
        // outR(s);
        // outR(c);
        // outR(std::string("hi"));
        // outR(returnString());
        // outR(returnConstString());
        // outR(std::move(s));
        // outR(std::move(c));
        // outR("hi");
    }
    {
        std::string s = "hi";
        std::string returnString();
        // passR(s);
        passR(std::string("hi"));
        passR(returnString());
        passR(std::move(s));
        int arr[4];
        passR(arr);

        std::string const c = "hi";
        passR(c);
        passR("hi");
    }
}
