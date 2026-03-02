#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
#include <string>

using namespace std;

// ==================== REGISTRO BASE ====================
class Register {
protected:
    int value;
    string name;

public:
    Register(string name = "REG");
    virtual void setValue(int val);
    virtual int getValue() const;
    virtual void display() const;
    virtual void reset();
    string getName() const;
};

// ==================== REGISTROS ESPECIALIZADOS ====================
class Accumulator : public Register {
public:
    Accumulator();
    void display() const override;
};

class ProgramCounter : public Register {
public:
    ProgramCounter();
    void increment();
    void display() const override;
};

class InstructionRegister : public Register {
public:
    InstructionRegister();
    void display() const override;
};

class MemoryAddressRegister : public Register {
public:
    MemoryAddressRegister();
    void display() const override;
};

class MemoryDataRegister : public Register {
public:
    MemoryDataRegister();
    void display() const override;
};

#endif
