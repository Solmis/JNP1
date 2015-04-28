#ifndef OPERATION_H_
#define OPERATION_H_
 
#include "ram.h"
#include "cpu.h"
#include "types.h"
#include <memory>
 
//==============================================================================
//  Operation
//==============================================================================
 
class Operation {
 
protected:
 
    std::shared_ptr <RAM> ram;
    std::shared_ptr <CPU> cpu;
 
public:
 
    Operation(std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram)
        : cpu(cpu), ram(ram) {}
    virtual ~Operation() {}
    virtual void do_operation() = 0;
 
};
 
//==============================================================================
// Set
//==============================================================================
 
class Set : public Operation {
 
private:
 
    register_type rnum;
    sys_type val;
 
public:
 
    Set(register_type rnum, sys_type val, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram);
    void do_operation();
   
};
 
//==============================================================================
// Load
//==============================================================================
 
class Load : public Operation {
 
private:
 
    register_type rnum;
    memory_type maddr;
 
public:
 
    Load(register_type rnum, memory_type maddr, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram);
    void do_operation();
   
};
 
//==============================================================================
// Store
//==============================================================================
 
class Store : public Operation {
 
private:
 
    memory_type maddr;
    register_type rnum;
 
public:
 
    Store(memory_type maddr, register_type rnum, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram);
    void do_operation();
   
};
 
//==============================================================================
// Add
//==============================================================================
 
class Add : public Operation {
 
private:
 
    register_type rnum1;
    register_type rnum2;
 
public:
 
    Add(register_type rnum1, register_type rnum2, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram);
    void do_operation();
   
};
 
//==============================================================================
// Sub
//==============================================================================
 
class Sub : public Operation {
 
private:
 
    register_type rnum1;
    register_type rnum2;
 
public:
 
    Sub(register_type rnum1, register_type rnum2, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram);
    void do_operation();
   
};
 
//==============================================================================
// Mul
//==============================================================================
 
class Mul : public Operation {
 
private:
 
    register_type rnum1;
    register_type rnum2;
 
public:
 
    Mul(register_type rnum1, register_type rnum2, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram);
    void do_operation();
   
};
 
//==============================================================================
// Div
//==============================================================================
 
class Div : public Operation {
 
private:
 
    register_type rnum1;
    register_type rnum2;
 
public:
 
    Div(register_type rnum1, register_type rnum2, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram);
    void do_operation();
   
};
 
//==============================================================================
// PrintLn
//==============================================================================
 
class PrintLn : public Operation {
 
private:
 
    register_type rnum;
 
public:
 
    PrintLn(register_type rnum, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram);
    void do_operation();
   
};
 
#endif