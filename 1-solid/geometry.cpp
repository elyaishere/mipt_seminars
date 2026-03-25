#include <cassert>
// square "is-a" rectangle [?]

class Rectangle {
public:
    Rectangle(int height = 0, int width = 0);
    virtual void setHeight(int newHeight);
    virtual void setWidth(int newWidth);
    virtual int height() const;
    virtual int width() const;

private:
    int height_{};
    int width_{};
};

class Square : public Rectangle {
public:
    Square(int side = 0);
};

void makeBigger(Rectangle& r) {
    int oldHeight = r.height();
    r.setWidth(r.width() + 10);
    assert(r.height() == oldHeight);
}

int main() {
    Square s;
    assert(s.width() == s.height());
    makeBigger(s);
    assert(s.width() == s.height());  // ??
}
