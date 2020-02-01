#include "muncorrectinput.h"



void MUncorrectInput::raise() const {
    throw *this;
}

MUncorrectInput *MUncorrectInput::clone() const {
    return new MUncorrectInput(*this);
}

const char *MUncorrectInput::what() {
    return "Uncorrent input";
}
