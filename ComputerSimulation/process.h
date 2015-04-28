#ifndef PROCESS_H_
#define PROCESS_H_

#include <list>
#include <sstream>
#include <iostream>
#include <memory>
#include "ram.h"
#include "cpu.h"
#include "operation.h"

class Process {

private:

    std::shared_ptr <RAM> ram;
    std::shared_ptr <CPU> cpu;
    std::list<std::shared_ptr <Operation> > operations;
    std::list<std::shared_ptr <Operation> >::iterator itrOperations;

    std::shared_ptr <Operation> parse(std::string operation);

public:

    Process() {}
    Process(std::string process, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram);
    int size() const;
    void begin();
    std::shared_ptr <Operation> next();
    bool hasNext();

};

#endif
