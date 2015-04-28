#ifndef COMPUTER_H_
#define COMPUTER_H_

#include "os.h"
#include "scheduling_algorithm.h"
#include "cpu.h"
#include "ram.h"
#include "types.h"
#include <memory>

class Computer {

private:

    std::shared_ptr <RAM> ram;
    std::shared_ptr <CPU> cpu;
    bool installedOS;

public:

    Computer();
    void setCPU(register_type numOfRegisters);
    void setRAM(memory_type size);
    std::shared_ptr<OS> installOS(std::shared_ptr<SchedulingAlgorithm> alg);

};

#endif