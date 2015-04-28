#ifndef CPU_H_
#define CPU_H_
 
#include "types.h"
#include <memory>
 
class CPU {
 
private:
 
    register_type sizeRegisters;
    std::unique_ptr <sys_type[]> registers;
 
public:
 
    CPU() : sizeRegisters(0) {}
    void setCPU(register_type numOfRegisters);
    register_type size();
    sys_type read(register_type number);
    void write(register_type number, sys_type value);
   
};
 
#endif