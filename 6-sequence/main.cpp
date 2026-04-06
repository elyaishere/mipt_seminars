#include "split_buffer.h"

int main() {
    GapBuffer buf(1);
    buf.insert("This is the way out");
    buf.move(16);
    buf.print_raw();
    buf.insert("the world start ");
    buf.print_raw();
    buf.insert("freaking ");
    buf.print_raw();
}
