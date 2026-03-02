#include "ControlUnit.h"

ControlUnit::ControlUnit() : currentState(FETCH) {
    stateNames[FETCH] = "FETCH";
    stateNames[DECODE] = "DECODE";
    stateNames[EXECUTE] = "EXECUTE";
    stateNames[HALTED] = "HALTED";
    stateNames[PAUSED] = "PAUSED";
}

void ControlUnit::setState(string state) {
    if (state == "FETCH") currentState = FETCH;
    else if (state == "DECODE") currentState = DECODE;
    else if (state == "EXECUTE") currentState = EXECUTE;
    else if (state == "HALTED") currentState = HALTED;
    else if (state == "PAUSED") currentState = PAUSED;
}

string ControlUnit::getState() const {
    return stateNames.at(currentState);
}

void ControlUnit::display() const {
    cout << "Control Unit (UC): " << getState() << endl;
}

bool ControlUnit::isHalted() const {
    return currentState == HALTED;
}

bool ControlUnit::isPaused() const {
    return currentState == PAUSED;
}

void ControlUnit::reset() {
    currentState = FETCH;
}
