#include "os.h"
#include "operation.h"
#include <iostream>

void OS::executePrograms(std::list<std::string> const& programs) const
{
    alg->install(programs, cpu, ram);
    while (alg->hasNext())
        (alg->next())->do_operation();
}