#ifndef SCHEDULING_ALGORITHM_H_
#define SCHEDULING_ALGORITHM_H_


#include <list>
#include <memory>
#include "process.h"
#include "operation.h"
#include "cpu.h"
#include "ram.h"
#include "types.h"

//==============================================================================
//  SchedulingAlgorithm
//==============================================================================

class SchedulingAlgorithm {

private:

    std::list<Process> program;
    std::list<Process>::iterator itrProgram;

protected:

    Process process;

    void setProgram(std::list<Process> &p);
    void beginProcess();
    Process nextProcess();
    Process previousProcess();
    bool hasNextProcess();

    virtual std::list<Process>& sortProcess(std::list<Process> &p) = 0;

public:

    virtual ~SchedulingAlgorithm() {}

    virtual void install(std::list<std::string> const& programs,
                         std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram);
    virtual void begin();
    virtual std::shared_ptr <Operation> next();
    bool hasNextPom();
    virtual bool hasNext();

};

//==============================================================================
//  FCFSScheduling
//==============================================================================

class FCFSScheduling : public SchedulingAlgorithm {

protected:
    
    std::list<Process>& sortProcess(std::list<Process> &p);

};

//==============================================================================
//  RRScheduling
//==============================================================================

class RRScheduling : public SchedulingAlgorithm {

private:

    time_type quantum;
    long int numberOfOperations;

protected:
    
    std::list<Process>& sortProcess(std::list<Process> &p);

public:

    RRScheduling(time_type quantum) : quantum(quantum), numberOfOperations(0) {}

    virtual bool hasNext();
    virtual std::shared_ptr <Operation> next();

};

//==============================================================================
//  SJFScheduling
//==============================================================================

class SJFScheduling : public SchedulingAlgorithm {

private:

    static bool compareSJFS (const Process &first, const Process &second);

protected:
    
    std::list<Process>& sortProcess(std::list<Process> &p);

};

//==============================================================================

std::shared_ptr<SchedulingAlgorithm> createFCFSScheduling();
std::shared_ptr<SchedulingAlgorithm> createRRScheduling(time_type quantum);
std::shared_ptr<SchedulingAlgorithm> createSJFScheduling();

#endif