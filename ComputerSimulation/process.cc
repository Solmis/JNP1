#include "process.h"
#include "exceptions.h"
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <string>

using namespace std;
using namespace boost;
using namespace boost::algorithm;

const string WHITE_PAT = "(\\s)*";
const string RNUM_PAT = WHITE_PAT + "R(-?([0-9])+)";
const string VAL_PAT = WHITE_PAT + "(-?([0-9])+)";
const string MADDR_PAT = WHITE_PAT + "M(-?([0-9])+)";
const string SET_PAT = WHITE_PAT + "SET " + RNUM_PAT + " " + VAL_PAT + WHITE_PAT + "$";
const string LOAD_PAT = WHITE_PAT + "LOAD " + RNUM_PAT + " " + MADDR_PAT + WHITE_PAT + "$";
const string STORE_PAT = WHITE_PAT + "STORE " + MADDR_PAT + " " + RNUM_PAT + WHITE_PAT + "$";
const string ADD_PAT = WHITE_PAT + "ADD " + RNUM_PAT + " " + RNUM_PAT + WHITE_PAT + "$";
const string SUB_PAT = WHITE_PAT + "SUB " + RNUM_PAT + " " + RNUM_PAT + WHITE_PAT + "$";
const string MUL_PAT = WHITE_PAT + "MUL " + RNUM_PAT + " " + RNUM_PAT + WHITE_PAT + "$";
const string DIV_PAT = WHITE_PAT + "DIV " + RNUM_PAT + " " + RNUM_PAT + WHITE_PAT + "$";
const string PRINTLN_PAT = WHITE_PAT + "PRINTLN " + RNUM_PAT + WHITE_PAT + "$";


Process::Process(std::string process, std::shared_ptr <CPU> cpu, std::shared_ptr <RAM> ram)
{
    this->cpu = cpu;
    this->ram = ram;
    stringstream sprocess;
    sprocess << process;
    string operation;
    smatch res;
    regex whiteReg(WHITE_PAT);

    while(std::getline(sprocess, operation))
    {
        if (operation != "" && !regex_match(operation, res, whiteReg))
            operations.push_back(parse(operation));
    }
}

int Process::size() const
{
    return operations.size();
}

void Process::begin()
{
    itrOperations = operations.begin();
}

std::shared_ptr <Operation> Process::next()
{
    return *(itrOperations++);
}

bool Process::hasNext() 
{
    return (itrOperations != operations.end());
}

std::shared_ptr <Operation> Process::parse(string operation)
{
    smatch res;
    regex setReg(SET_PAT);
    regex loadReg(LOAD_PAT);
    regex storeReg(STORE_PAT);
    regex addReg(ADD_PAT);
    regex subReg(SUB_PAT);
    regex mulReg(MUL_PAT);
    regex divReg(DIV_PAT);
    regex printlnReg(PRINTLN_PAT);

    if (regex_match(operation, res, setReg))
    {
        register_type rnum = stoll(res[3]);
        sys_type val = stoi(res[6]);

        return std::shared_ptr <Operation> (new Set(rnum, val, cpu, ram));
    }
    else if (regex_match(operation, res, loadReg))
    {
        register_type rnum = stoll(res[3]);
        memory_type maddr = stoll(res[6]);

        return std::shared_ptr <Operation> (new Load(rnum, maddr, cpu, ram));
    }
    else if (regex_match(operation, res, storeReg))
    {
        memory_type maddr = stoll(res[3]);
        register_type rnum = stoll(res[6]);

        return std::shared_ptr <Operation> (new Store(maddr, rnum, cpu, ram));
    }
    else if (regex_match(operation, res, addReg))
    {
        register_type rnum1 = stoll(res[3]);
        register_type rnum2 = stoll(res[6]);

        return std::shared_ptr <Operation> (new Add(rnum1, rnum2, cpu, ram));
    }
    else if (regex_match(operation, res, subReg))
    {
        register_type rnum1 = stoll(res[3]);
        register_type rnum2 = stoll(res[6]);

        return std::shared_ptr <Operation> (new Sub(rnum1, rnum2, cpu, ram));
    }
    else if (regex_match(operation, res, mulReg))
    {
        register_type rnum1 = stoll(res[3]);
        register_type rnum2 = stoll(res[6]);

        return std::shared_ptr <Operation> (new Mul(rnum1, rnum2, cpu, ram));
    }
    else if (regex_match(operation, res, divReg))
    {
        register_type rnum1 = stoll(res[3]);
        register_type rnum2 = stoll(res[6]);

        return std::shared_ptr <Operation> (new Div(rnum1, rnum2, cpu, ram));
    }
    else if (regex_match(operation, res, printlnReg))
    {
        register_type rnum = stoll(res[3]);

        return std::shared_ptr <Operation> (new PrintLn(rnum, cpu, ram));
    }
    else
        throw InvalidInstructionException();
}