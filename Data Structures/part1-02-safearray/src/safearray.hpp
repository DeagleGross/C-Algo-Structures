////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Safearray class methods definition
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      30.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// This file contains templates of the method of the class Safearray.
/// This file is not going to be used w/o its main counterpart, safearray.h.
/// Since the file is used only through safearray.h, which has its own "include 
/// watcher", we add no addition "watcher" here.
///
////////////////////////////////////////////////////////////////////////////////

// #ifndef    // No need to have a watcher here!


// we have to indicate that methods of the class Safearray are also inside the namespace xi
namespace xi {

    /** \brief Конструктор инициализации размером (число объектов) массива.
         *
         *  Распределяет память соответствующего размера, устанавливает значение емкости массива.
         * \param[in] cap Размер (емкость) массива.
         */
    template <typename T>
    SafeArray<T>::SafeArray(size_t cap)
    {
        _capacity = cap;
        _storage = new T[cap];
    }

    /** \brief Деструктор.
     *
     *  Освобождает занимаемую массивом память.
     */
    template <typename T>
    SafeArray<T>::~SafeArray()
    {
        _capacity = 0;
        delete[] _storage;
        _storage = nullptr;
    }

    /**
     * \brief Конструктор копирования
     *
     * \param other Объект для копирования
     */
    template <typename T>
    SafeArray<T>::SafeArray(const SafeArray<T>& other)
    {
        if (this != &other) // not allowing to recreate object into itself
        {
            // created new fields with filled values
            _capacity = other.getCapacity();
            _storage = new T[_capacity];

            // copying values from other.pointer to THIS _storage object
            const T* pointer = other.getRawPtr();
            for (int i = 0; i < _capacity; ++i)
                _storage[i] = pointer[i];
        }
    }

    /**
     * \brief Оператор присваивания
     *
     * \param other Объект в качестве r-value
     */
    template <typename T>
    SafeArray<T>& SafeArray<T>::operator =(const SafeArray<T>& other)
    {
        if (this != &other) // not allowing to recreate object into itself
        {
            // deleted THIS object fields
            delete[] _storage;
            _storage = nullptr;

            // now ready to copy object
            _capacity = other.getCapacity();
            _storage = new T[_capacity];
            const T* objPointer = other.getRawPtr();
            for (int i = 0; i < _capacity; ++i)
                _storage[i] = objPointer[i];
        }
    }

    /** \brief Оператор индексирования.
     *
     *  Выполняет «защищенное» обращение к индивидуальным элементам массива.
     * Элемент возвращается по ссылке, и, таким образом, может находиться как в позиции \a rhv, так и в
     * позиции \a lhv.
     * \param[in] k — индекс элемента. Если указанный индекс находится вне диапазона распределенной памяти,
     * генерируется исключительная ситуация \c std::out_of_range.
     * \return Возвращает ссылку на \a k -тый элемент массива.
     */
    template <typename T>
    T& SafeArray<T>::operator[] (size_t k)
    {
        checkBounds(k); // checked bound and threw exception if needed
        T& p = _storage[k];
        return p;
    }

    /** \brief Константная перегруженная версия метода Safearray::operator[].
     *
     *  Возвращает константную ссылку на элемент, которая может находиться только в позиции \a rhv.
     */
     template <typename T>
     const T& SafeArray<T>::operator[] (size_t k) const
     {
         checkBounds(k);
         const T& p = _storage[k]; // pointer couldnt be changed
         return p;            // however object under the pointer could be
     }

     /// Возвращает актуальный размер массива.
     template <typename T>
     size_t SafeArray<T>::getCapacity() const
     {
         return _capacity;
     }

    /// Вспомогательный метод, проверяющий, что заданный индекс \a index не выходит за границу
    /// распределенной под массив памяти. Если индекс вне диапазона, генерирует
    /// исключительную ситуацию \c std::out_of_range.
    template <typename T>
    void SafeArray<T>::checkBounds(size_t index) const
    {
        if ((index < 0) || (index >= _capacity) || (_capacity == 0))
            throw std::out_of_range("Index is out of range");
    }

} // namespace xi
