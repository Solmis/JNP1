#ifndef OS_H_
#define OS_H_

#include <string>
#include <list>
#include "scheduling_algorithm.h"
#include "cpu.h"
#include "ram.h"


class OS {

private:

    std::shared_ptr<SchedulingAlgorithm> alg;
    std::shared_ptr<CPU> cpu;
    std::shared_ptr<RAM> ram;

public:

    OS(std::shared_ptr<CPU> cpu, 
       std::shared_ptr<RAM> ram, 
       std::shared_ptr<SchedulingAlgorithm> alg) : cpu(cpu), ram(ram), alg(alg) {}

    void executePrograms(std::list<std::string> const& programs) const;
    
};

#endif