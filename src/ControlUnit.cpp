#include "ControlUnit.h"
#include <iostream>

using namespace std;

ControlUnit::ControlUnit() : currentState(FETCH) {
    stateNames[FETCH] = "FETCH";
    stateNames[DECODE] = "DECODE";
    stateNames[EXECUTE] = "EXECUTE";
    stateNames[HALTED] = "HALTED";
}

void ControlUnit::setState(string state) {
    if (state == "FETCH") currentState = FETCH;
    else if (state == "DECODE") currentState = DECODE;
    else if (state == "EXECUTE") currentState = EXECUTE;
    else if (state == "HALTED") currentState = HALTED;
}

string ControlUnit::getState() const {
    return stateNames.at(currentState);
}

bool ControlUnit::isHalted() const {
    return currentState == HALTED;
}

void ControlUnit::reset() {
    currentState = FETCH;
}
