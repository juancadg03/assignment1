#include "Register.h"

Register::Register() : value(0) {}

void Register::setValue(int val) {
    value = val;
}

int Register::getValue() const {
    return value;
}

void Register::reset() {
    value = 0;
}

void ProgramCounter::increment() {
    value++;
}