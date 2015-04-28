#include "exceptions.h"
#include "ram.h"
 
void RAM::setRAM(memory_type size)
{
    if (size <= 0)
        throw IllegalArgumentException();
    else
    {
        sizeMemory = size;
        memory.reset(new sys_type[size]);
    }
}
 
memory_type RAM::size()
{
    return sizeMemory;
}
 
sys_type RAM::read(memory_type number)
{
    return memory[number];
}
 
void RAM::write(memory_type number, sys_type value)
{
    memory[number] = value;
}