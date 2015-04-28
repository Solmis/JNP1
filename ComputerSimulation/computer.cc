#include "computer.h"
#include "exceptions.h"

Computer::Computer()
{
    ram = std::shared_ptr<RAM>(new RAM());
    cpu = std::shared_ptr<CPU>(new CPU());
    installedOS = false;
}

void Computer::setCPU(register_type numOfRegisters)
{    
    if (installedOS)
        throw HardwareViolationException();

    cpu->setCPU(numOfRegisters);
}

void Computer::setRAM(memory_type size)
{    
    if (installedOS)
        throw HardwareViolationException();

    ram->setRAM(size);
}

std::shared_ptr<OS> Computer::installOS(std::shared_ptr<SchedulingAlgorithm> alg)
{
    if (cpu->size() <= 0)
        throw NoCPUException();

    if (ram->size() <= 0)
        throw NoRAMException();

    installedOS = true;

    return std::shared_ptr<OS>(new OS(cpu, ram, alg));
}