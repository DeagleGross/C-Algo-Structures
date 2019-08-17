////////////////////////////////////////////////////////////////////////////////
// Module Name:  int_stack.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

/*
 * varianti: 5 9 7
 * Korolev Dmitry
 */


#include <stdexcept>
#include "int_stack.h"

// added headers
#define ASSIGN_OP     // variant 5
#define INVER_OP      // variant 7
#define OR_OP         // variant 9

namespace xi {

    /// constructor receiving size of stack and initializing fields
    IntStack::IntStack(size_t sz){
        if (sz <= 0)
        {
            _stack = nullptr;
            _ssize = 0;
        }
        else {
            if (sz > 1024)
                sz = STACK_SIZE;
            _stack = new int[sz];
            _ssize = sz;
        }

        // starting position of head
        _head = -1;
    }

    /// standart destructor to delete int* field and point it to nullptr
    IntStack::~IntStack()
    {
        delete[] _stack;
//        _ssize = 0;   // we dont need a ssize and head to be changed
//        _head = -1;   // because these value-types will be soon dead
        _stack = nullptr;
    }

    /** Pushes a given element onto the stack.
     *
     *  If no more elements can be placed onto the stack due to its overflow an std::logic_error is thrown.
     *
     *  Storing head in the LAST pushed element. if no elements are in stack, then _head = -1;
     */
     void IntStack::push(int el)
     {
         // checking if stack is full
         if (isFull())
             throw std::logic_error("Stack overflow occured!");

         // check if stack is not nullptr. in other case nothin is done
         if (_stack != nullptr)
            _stack[++_head] = el;
     }

    /** Pops an element from the stack and returns its value.
    *
    *  If no elements stored in the stack, a std::logic_error is thrown.
    */
    int IntStack::pop()
    {
        if (isEmpty())
            throw std::logic_error("No elements are in the stack. Nothing to pop.");

        return _stack[_head--];
    }

    /** Looks up an element from the top of the stack and returns its value.
     *
     *  If no elements stored in the stack, a std::logic_error is thrown.
     */
     int IntStack::top()
     {
        if (isEmpty())
            throw std::logic_error("No elements are in the stack. Nothing to top.");

        return _stack[_head];
     }

    /** Clears the stack and makes it empty.
    *
    *  Often named as makeEmpty or similar
    */
    void IntStack::clear()
    {
        // stack capacity is not changed in this method
        // so we just force head to look at the start.
        // size remains the same. _stack is not deleted.
        _head = -1; // because object is not killed, only values are not valid. But size has to be the same
    }

    /** Returns true if the stack is empty, false otherwise */
    bool IntStack::isEmpty() const
    {
        return _head == -1;
    }

    /** Returns true if the stack is full, false otherwise */
    bool IntStack::isFull() const
    {
        // head is 1 index before size
        // and stack is not empty
        if ((_head == _ssize - 1) && (_head != -1))
            return true;
        return false;
    }

} // namespace xi

