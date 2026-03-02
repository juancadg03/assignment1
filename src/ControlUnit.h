#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

// ==================== UNIDAD DE CONTROL ====================
class ControlUnit {
private:
    enum State {
        FETCH,
        DECODE,
        EXECUTE,
        HALTED,
        PAUSED
    };
    
    State currentState;
    map<int, string> stateNames;

public:
    ControlUnit();
    void setState(string state);
    string getState() const;
    void display() const;
    bool isHalted() const;
    bool isPaused() const;
    void reset();
};

#endif
