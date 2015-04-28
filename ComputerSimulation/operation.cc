#include "operation.h"
#include "exceptions.h"
#include <iostream>
 
 
const memory_type LOWEST_MADDR = 0;
const register_type LOWEST_RNUM = 1;
 
Set::Set(register_type rnum, sys_type val, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram)
    : Operation(cpu, ram)
{  
    if (rnum < LOWEST_RNUM || rnum > cpu->size())
        throw IllegalArgumentException();
 
    this->rnum = rnum;
    this->val = val;
}
 
void Set::do_operation()
{
    cpu->write(rnum, val);
}
 
Load::Load(register_type rnum, memory_type maddr, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram)
    : Operation(cpu, ram)
{
    if (rnum < LOWEST_RNUM || rnum > cpu->size() || maddr < LOWEST_MADDR || maddr > ram->size())
        throw IllegalArgumentException();
 
    this->rnum = rnum;
    this->maddr = maddr;
}
 
void Load::do_operation()
{
    cpu->write(rnum, ram->read(maddr));
}
 
Store::Store(memory_type maddr, register_type rnum, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram)
    : Operation(cpu, ram)
{
    if (rnum < LOWEST_RNUM || rnum > cpu->size() || maddr < LOWEST_MADDR || maddr > ram->size())
        throw IllegalArgumentException();
 
    this->rnum = rnum;
    this->maddr = maddr;
}
 
void Store::do_operation()
{
    ram->write(maddr, cpu->read(rnum));
}
 
Add::Add(register_type rnum1, register_type rnum2, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram)
    : Operation(cpu, ram)
{
    if (rnum1 < LOWEST_RNUM || rnum1 > cpu->size() || rnum2 < LOWEST_RNUM || rnum2 > cpu->size())
        throw IllegalArgumentException();
 
    this->rnum1 = rnum1;
    this->rnum2 = rnum2;
}
 
void Add::do_operation()
{
    sys_type tmp = cpu->read(rnum1) + cpu->read(rnum2);
    cpu->write(rnum1, tmp);
}
 
Sub::Sub(register_type rnum1, register_type rnum2, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram)
    : Operation(cpu, ram)
{
    if (rnum1 < LOWEST_RNUM || rnum1 > cpu->size() || rnum2 < LOWEST_RNUM || rnum2 > cpu->size())
        throw IllegalArgumentException();
 
    this->rnum1 = rnum1;
    this->rnum2 = rnum2;
}
 
void Sub::do_operation()
{
    sys_type tmp = cpu->read(rnum1) - cpu->read(rnum2);
    cpu->write(rnum1, tmp);
}
 
Mul::Mul(register_type rnum1, register_type rnum2, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram)
    : Operation(cpu, ram)
{
    if (rnum1 < LOWEST_RNUM || rnum1 > cpu->size() || rnum2 < LOWEST_RNUM || rnum2 > cpu->size())
        throw IllegalArgumentException();
 
    this->rnum1 = rnum1;
    this->rnum2 = rnum2;
}
 
void Mul::do_operation()
{
    sys_type tmp = cpu->read(rnum1) * cpu->read(rnum2);
    cpu->write(rnum1, tmp);
}
 
Div::Div(register_type rnum1, register_type rnum2, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram)
    : Operation(cpu, ram)
{
    if (rnum1 < LOWEST_RNUM || rnum1 > cpu->size() || rnum2 < LOWEST_RNUM || rnum2 > cpu->size())
        throw IllegalArgumentException();
 
    if (cpu->read(rnum2) == 0)
        throw DivisionByZeroException();
 
    this->rnum1 = rnum1;
    this->rnum2 = rnum2;
}
 
void Div::do_operation()
{
    sys_type tmp = cpu->read(rnum1) / cpu->read(rnum2);
    cpu->write(rnum1, tmp);
}
 
PrintLn::PrintLn(register_type rnum, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram)
    : Operation(cpu, ram)
{
    if (rnum < LOWEST_RNUM || rnum > cpu->size())
        throw IllegalArgumentException();
 
    this->rnum = rnum;
}
 
void PrintLn::do_operation()
{
    std::cout << cpu->read(rnum) << std::endl;
}