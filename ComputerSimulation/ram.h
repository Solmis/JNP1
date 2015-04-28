#ifndef RAM_H_
#define RAM_H_
 
#include <memory>
#include "types.h"
 
class RAM {
 
private:
 
    memory_type sizeMemory;
    std::unique_ptr <sys_type[]> memory;
 
public:
 
    RAM() : sizeMemory(0) {}
    void setRAM(memory_type size);
    memory_type size();
    sys_type read(memory_type number);
    void write(memory_type number, sys_type value);
};
 
#endif