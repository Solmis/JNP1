#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>

class InvalidInstructionException : public std::exception
{
    public:
        virtual const char* what() const throw()
        {
            return "InvalidInstruction: Program has attempted to execute an invalid instruction.";
        }
};

class IllegalArgumentException : public std::exception
{
    public:
        virtual const char* what() const throw()
        {
            return "IllegalArgument: Argument passed to function is illegal.";
        }
};

class NoCPUException : public std::exception
{
    public:
        virtual const char* what() const throw()
        {
            return "NoCPU: No CPU present.";
        }
};

class NoRAMException : public std::exception
{
    public:
        virtual const char* what() const throw()
        {
            return "NoRAM: No RAM present.";
        }
};

class DivisionByZeroException : public std::exception
{
    public:
        virtual const char* what() const throw()
        {
            return "DivisionByZero: Dividing by zero is undefined.";
        }
};

class HardwareViolationException : public std::exception
{
    public:
        virtual const char* what() const throw()
        {
            return "HardwareViolation: Operating system already installed. Unable to change hardware.";
        }
};

#endif