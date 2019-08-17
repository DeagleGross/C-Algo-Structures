#include <algorithm>

#include "NiceQueue.h"

// FIELDS OF NICE_QUEUE
//        protected:
//        /// Входной стек.
//        NiceStack<T> _inStack;
//        /// Выходной стек.
//        NiceStack<T> _outStack;
//        /// Вместимость очереди.
//        size_t _capacity;

    /// Создать NiceQueue с вместимостью capacity.
    template<class T>
    NiceQueue<T>::NiceQueue(size_t capacity)
        : _inStack(capacity),
          _outStack(capacity)   // launching constructors for NiceStack<T>
    {
        _capacity = capacity;
    }

    /// Деструктор. Нужен ли тут деструктор?
    template<class T>
    NiceQueue<T>::~NiceQueue()
    {
        // again Nicestack are objects that will destruct themselves
        // we dont need to control it here
        // size_t is most-easy type variable
    }

    /// Возвращает число элементов в очереди.
    template<class T>
    size_t NiceQueue<T>::size() const
    {
        // returns amount of elements in IN stack and OUT stack
        return (_inStack.size() + _outStack.size());
    }

    /// Положить новый элемент в очередь.
    /// Возникает исключение out_of_range если очередь полна.
    template<class T>
    void NiceQueue<T>::enq(const T &newElement)
    {
        // putting element in IN stack
        _inStack.push(newElement); // exception is in NiceStack.push realization
    }

    /// Извлечь элемент из очереди.
    /// Возникает исключение out_of_range если очередь пуста.
    template<class T>
    T NiceQueue<T>::deq()
    {
        // first if out_stack is NOT empty - just pop an element
        if (_outStack.size() != 0)
            return _outStack.pop();

        // otherwise firstly we replace all elements from INSTACK to OUTSTACK
        // We POP element an PUSH it in another stack
        while (_inStack.size() != 1)
        {
            T tmp = _inStack.pop();
            _outStack.push(tmp);
        }

        // but we didnt pop the last element from instack in last for()
        // so we return poped element
        return _inStack.pop();
    }

    /// Возвращает копию минимального элемента в очереди.
    template<class T>
    T NiceQueue<T>::getMinimum()
    {
        // if no elements are in queue
        if (size() == 0)
            throw std::out_of_range("Queue is empty!");

        T minIn, minOut;

        // trying to get min of instack
        try { minIn = _inStack.getMinimum(); } // if error is here than return minimum
        catch (std::out_of_range) { return _outStack.getMinimum(); } // of OUTSTACK

        // trying to get min of OUTSTACK. Analog to smth vverhy
        try { minOut = _outStack.getMinimum(); }
        catch (std::out_of_range) { return _inStack.getMinimum(); }

        // if all went okay so return minimum of minIN and minOut
        return std::min(minIn, minOut);
    }

