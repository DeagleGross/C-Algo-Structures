////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>

namespace xi {

//==============================================================================
// Free functions -- helpers
//==============================================================================

    /* Returns a result of operation according to its arity and values from stack
     *
     * \param _s IntStack& as a value (so it is changed as an object in this function) to use stack numbers
     * \param op IOperation* a pointer to the operation so we can recognize its arity and operation method
     * \param symb char symbol for operation (used in op->operation method)
     */
    int getResultOfOperation( IntStack& _s, IOperation* op, char symb)
    {
        // getting operations in a needed order and then sending them to operation-method
        if (op->getArity() == op->arUno)
        {
            int a = _s.pop();
            return op->operation(symb, a);
        }
        if (op->getArity() == op->arDue)
        {
            int b = _s.pop();
            int a = _s.pop();
            return op->operation(symb, a, b);
        }
        if (op->getArity() == op->arTre)
        {
            int c = _s.pop();
            int b = _s.pop();
            int a = _s.pop();
            return op->operation(symb, a, b, c);
        }
    }


    /* Returns a vector of std:string based on splitting a string by a space symbol
     *
     * \param str - a string to be splitted
     */
    std::vector<std::string> getTokensFromString(const std::string str)
    {
        int left = 0; // start of substring
        std::vector<std::string> arr;

        for (int i = 0; i < str.length(); ++i)
        {
            if (str[i] == ' ')
            {
                arr.push_back(str.substr(left, i - left));
                left = i+1;
            }
        }

        arr.push_back(str.substr(left, str.length()-left));

        return arr;
    }

//    /* Checks if a string can be converted to number
//     *
//     * \param str - a string to be checked
//     */
//    bool isNumber(std::string str)
//    {
//        for (int i = 0; i < str.length(); ++i)
//            if (!(str[i] >= '0' && str[i] <= '9'))
//                return false;
//        return true;
//    }

    /* Checks if a string can be converted to number
    *
    * \param str - a string to be checked
    *
    * Checks if string is a number by checking
    * every symbol to be either digit either '-'
    */
    bool isNumber(const std::string str)
    {
        if (str[0] != '-' && !std::isdigit(str[0]))
            return false;

        for(int i = 1; i < str.size(); i++)
            if(!std::isdigit(str[i]))
                return false;
        return true;
    }

//==============================================================================
// class PlusOp
//==============================================================================


int PlusOp::operation(char op, int a, int b, int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
{
    if(op != '+')
        throw std::logic_error("Operation other than Plus (+) are not supported");

    // here we just ignore unused operands
    return a + b;
}

IOperation::Arity PlusOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class AssignOP
//==============================================================================

int AssignOp::operation(char op, int a, int /*b*/, int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
{
    if(op != '=')
        throw std::logic_error("Operation other than Assign (=) are not supported");

    // here we just ignore unused operands
    return a;
}

IOperation::Arity AssignOp::getArity() const
{
    return arUno;
}

//==============================================================================
// class InverOp
//==============================================================================

int InverOp::operation(char op, int a, int /*b*/, int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
{
    if(op != '~')
        throw std::logic_error("Operation other than Inver (~) are not supported");

    // here we just ignore unused operands
    return (~a);
}

IOperation::Arity InverOp::getArity() const
{
    return arUno;
}


//==============================================================================
// class OrOp
//==============================================================================

int OrOp::operation(char op, int a, int b, int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
{
    if(op != '|')
        throw std::logic_error("Operation other than Or (|) are not supported");

    // here we just ignore unused operands
    return (a | b);
}

IOperation::Arity OrOp::getArity() const
{
    return arDue;
}


//==============================================================================
// class StackMachine
//==============================================================================

    /** Register an operation object for a given symbol.
     *
     *  If the symbol is already registered, throws an exception.
     *
     *  !The method implementation should be shred with students!
     */
    void StackMachine::registerOperation(char symb, xi::IOperation *oper)
    {
        SymbolToOperMapConstIter it = _opers.find(symb);
        if(it != _opers.end())
            throw std::logic_error("An operation ... is alr. reg...");

        _opers[symb] = oper;
    }

    /** For a given symb returns an operation object.
     *
     *  If the given symbol is not mapped to any operation, a nullptr is returned.
     */
    IOperation* StackMachine::getOperation(char symb)
    {
        // as in previous method finding
        SymbolToOperMapConstIter it = _opers.find(symb);
        // and if nothin is found
        if (it == _opers.end())
            return nullptr;

        return _opers[symb];
    }

    /** Calculates given expression using the shared stack and returns the value on its top.
     *
     *  \param clearStack determines if a stack should be clear before parsing the expression.
     *  If one prefer not to clear stack before parsing, the results of previous calculations
     *  can be used further.
     *
     *  \param expr contains a string-based expression contains interger operands and one-symbol operators
     *  If an unrecognized symbol (or substring) is found, throws an exception.
     *  If given expression is not valid (e.g., in the case of lack of operands or similar),
     *  an exception is thrown.
     */
    int StackMachine::calculate(const std::string &expr, bool clearStack)
    {
        // clearing stack with state
        if (clearStack)
            _s.clear();

        // works correctly SPLIT STRING
        std::vector<std::string> tokens = getTokensFromString(expr); // tested

        for (int i = 0; i < tokens.size(); ++i)
        {
            // checking if string is a number
            if (isNumber(tokens[i]))
            {
                _s.push(std::stoi(tokens[i])); // laying it down in the stack
            }
            else { // if it not a number we have to check an operation
                if(tokens[i].size() > 1)    // if operation is more than just 1 symbol
                    throw std::logic_error("That`s not an operation at all!!!");  // then we throw an exception
                IOperation* op = getOperation(tokens[i][0]);
                if (op == nullptr)
                    throw std::logic_error("No operation found in a bank.");

                // now calculated the result and pushed it back to stack
                _s.push(getResultOfOperation(_s, op, tokens[i][0]));
            }
        }

        return _s.top();
    }


} // namespace xi
