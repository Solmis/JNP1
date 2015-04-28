#include "cpu.h"
#include "exceptions.h"
 
void CPU::setCPU(register_type numOfRegisters)
{
    if (numOfRegisters <= 0)
        throw IllegalArgumentException();
    else
    {
        sizeRegisters = numOfRegisters;
        registers.reset(new sys_type[sizeRegisters + 1]);
    }
}
 
register_type CPU::size()
{
    return sizeRegisters;
}
 
sys_type CPU::read(register_type number)
{
    return registers[number];
}
 
void CPU::write(register_type number, sys_type value)
{
    registers[number] = value;
}