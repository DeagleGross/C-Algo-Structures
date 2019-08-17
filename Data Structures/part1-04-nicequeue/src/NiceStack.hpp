

#include "NiceStack.h"
//     FIELDS OF NICE_STACK
//            protected:
//            std::vector<TypeElementStack> _storage;         ///< Вектор элементов стека.
//            size_t _iHead;                                  ///< Индекс головы стека.
//            size_t _capacity;                               ///< Вместимость стека.

//    /// Определение типа элементов стека - пара <значение, минимум-среди-всех-элементов-ниже>
//    typedef std::pair<T, T> TypeElementStack;

    /// Создает NiceStack с вместимостью capacity. Конструктор объявлен "для явного вызова".
    template<class T>
    NiceStack<T>::NiceStack(size_t capacity)
    {
        if (capacity == 0)
        {
            _capacity = 0;
        } else {
            _capacity = capacity;
            _storage = std::vector<TypeElementStack>(_capacity);
        }

        _iHead = -1;
    }

    /// Нельзя создавать NiceStack по умолчанию. Только с помощью другого конструктора с параметром.
    template<class T>
    NiceStack<T>::~NiceStack()
    {
        // we dont need to delete size_t because it is most-easy variable
        // std::vector is an object - this destructor will launch destructor of vector.
        // vector will kill himself without my actions
    }

    // Возвращает число элементов, реально находящихся в стеке.
    template<class T>
    size_t NiceStack<T>::size() const
    {
        // as always returning NOW element + 1
        return _iHead + 1;
    }

    /// Положить новый элемент, передаваемый по ссылке, чтобы избежать копирования.
    /// Возникает исключение out_of_range если стек полный.
    template<class T>
    void NiceStack<T>::push(const T &newelement)
    {
        // if full (full or its capacity = 0)
        if (_iHead + 1 == _capacity || _capacity == 0)
            throw std::out_of_range("Stack is already full.");

        _storage[++_iHead].first = newelement; // storing the new element

        if (_iHead == 0) // if it is the first element in stack
            _storage[_iHead].second = newelement;   // we put it as a minimun
        else // in another case we compare THIS element with MIN of previous
            _storage[_iHead].second = (newelement < _storage[_iHead-1].second) ? newelement : _storage[_iHead-1].second;
    }

    /// Извлечь вершину стека.
    /// Возвращается значение верхнего элемента стека и верхний элемент удаляется из стека.
    /// По этой причине возвращаем его по значению — т.е. происходит копирование элемента.
    /// Возникает исключение out_of_range, если стек пустой.
    template<class T>
    T NiceStack<T>::pop()
    {
        if (_iHead == -1)   // if empty
            throw std::out_of_range("Stack is empty!");

        return _storage[_iHead--].first;   // just returning the top element
    }

    /// Показать вершину стека.
    /// Возвращается ссылка на верхний элемент стека, который остается в стеке.
    /// Возвращаемая ссылка действительна до первого вызова pop.
    /// Возникает исключение out_of_range, если стек пустой.
    template<class T>
    const T &NiceStack<T>::top() const
    {
        if (_iHead == -1)   // if empty!
            throw std::out_of_range("Stack is empty!");

        return _storage[_iHead].first;   // just returning the top element
    }

    /// Возвращает значение минимального элемента в стеке.
    /// Т.е. соответствующая область памяти остается на своем месте (элемент стека), имеем
    /// возможность вместо копии вернуть константную ссылку на объект, что в случае с любыми
    /// объектами, чуть более сложными, чем POD-типы, будет стоить дешевле.
    /// NB: с примитивными типами возврат по значению обычно дешевле. Поэтому в "профессиональных"
    /// контейнерах с помощью т.н. traits-классов определяется RVal тип: по значению (копия) —
    /// используется для примитивов, либо по const & — для сложных типов. Т.е. в результате
    /// для любого типа шаблона получаем наиболее оптимальную реализацию.
    template<class T>
    const T &NiceStack<T>::getMinimum() const
    {
        if (_iHead == -1)
            throw std::out_of_range("Can not return minimum from empty stack!");
        // its nicestack so just minimum of top element
        return _storage[_iHead].second;
    }
