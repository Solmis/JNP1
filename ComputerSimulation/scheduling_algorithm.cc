#include "scheduling_algorithm.h"
#include "exceptions.h"
#include <iostream>


void SchedulingAlgorithm::setProgram(std::list<Process> &p)
{
    program = p;
}

void SchedulingAlgorithm::beginProcess()
{
    itrProgram = program.begin();
}

Process SchedulingAlgorithm::nextProcess()
{
    return *(itrProgram++);
}

Process SchedulingAlgorithm::previousProcess()
{
    --itrProgram;
    return *(itrProgram);
}

bool SchedulingAlgorithm::hasNextProcess()
{
    return (itrProgram != program.end());
}

void SchedulingAlgorithm::install(std::list<std::string> const& programs,
                                          std::shared_ptr <CPU> cpu,
                                          std::shared_ptr <RAM> ram)
{ 
    std::list<Process> newProgram;

    for (auto itrString : programs)
    {
        Process pro = Process(itrString, cpu, ram);
        if (pro.size() != 0)
            newProgram.push_back(pro);
    }

    setProgram(sortProcess(newProgram));
    begin();
}

void SchedulingAlgorithm::begin()
{
    beginProcess();

    if (hasNextProcess())
        process = nextProcess();
    
    process.begin();
}

std::shared_ptr <Operation> SchedulingAlgorithm::next()
{
    if (!process.hasNext())
    {
        process = nextProcess();
        process.begin();
    }
    return process.next();
}

bool SchedulingAlgorithm::hasNextPom()
{
    bool solution;
    solution = process.hasNext();
    if (!solution)
    {
        if (hasNextProcess())
        {
            Process p = nextProcess();
            p.begin();
            solution = p.hasNext();
            previousProcess();
        }
    }
    return solution;
}

bool SchedulingAlgorithm::hasNext()
{
    return hasNextPom();
}
 
std::list<Process>& FCFSScheduling::sortProcess(std::list<Process> &p)
{
    return p;
}

std::list<Process>& RRScheduling::sortProcess(std::list<Process> &p)
{
    return p;
}

bool RRScheduling::hasNext()
{
    bool solution = false; 
    if (quantum > numberOfOperations)
        solution = hasNextPom();
    else
    {
        if (hasNextProcess())
        {
            Process p = nextProcess();
            p.begin();
            solution = p.hasNext();
            previousProcess();
        } 
    }
    return solution;
}

std::shared_ptr <Operation> RRScheduling::next()
{
    if (!process.hasNext() || (quantum == numberOfOperations))
    {
        process = nextProcess();
        process.begin();
        numberOfOperations = 0;
    }
    ++numberOfOperations;
    return process.next();
}

bool SJFScheduling::compareSJFS (const Process &first, const Process &second)
{
    return (first.size() < second.size());
}

std::list<Process>& SJFScheduling::sortProcess(std::list<Process> &p)
{
    p.sort(compareSJFS);
    return p;
}

std::shared_ptr<SchedulingAlgorithm> createFCFSScheduling()
{
    return std::make_shared<FCFSScheduling>();
}

std::shared_ptr<SchedulingAlgorithm> createRRScheduling(time_type quantum)
{
    if (quantum <= 0)
        throw IllegalArgumentException();
    else
        return std::make_shared<RRScheduling>(quantum);
}

std::shared_ptr<SchedulingAlgorithm> createSJFScheduling()
{
    return std::make_shared<SJFScheduling>();
}