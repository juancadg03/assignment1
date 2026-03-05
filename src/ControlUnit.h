#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include <string>
#include <map>

using namespace std;

class ControlUnit {
private:
    enum State {
        FETCH,
        DECODE,
        EXECUTE,
        HALTED
    };
    
    State currentState;
    map<int, string> stateNames;

public:
    ControlUnit();
    void setState(string state);
    string getState() const;
    bool isHalted() const;
    void reset();
};

#endif
