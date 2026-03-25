#include <iostream>

// NVI non virtual interface
class B {
public:
    void mf(int a = 100) {
        mf_impl(a);
    }

private:
    virtual void mf_impl(int a) {
        std::cout << "B::mf() " << a << std::endl;
    }
};
class D : public B {
private:
    virtual void mf_impl(int a) {
        std::cout << "D::mf() " << a << std::endl;
    }
};

int main() {
    D x;
    D *pD = &x;
    B *pB = &x;
    pB->mf();
    pD->mf(100);
}
