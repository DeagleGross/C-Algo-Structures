////////////////////////////////////////////////////////////////////////////////
// Module Name:  linked_list.h/cpp
// Authors:      Sergey Shershakov, Leonid Dworzanski
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
//
// Отделенная часть заголовка шаблона класса "Связанный список"
//
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>

//        Единственный элемент в линкед листе
//        /// Вспомогательный элемент — псевдонулевой элемент списка.
//        /// Тип \c T должен поддерживать конструктор по умолчанию.
//        Node<T>* _preHead;
//        // Вспомогательный элемент


namespace xi {

    /// Конструктор по умолчанию
    template <class T>
    LinkedList<T>::LinkedList()
    {
        //Creation of the dummy/sentinel element
        _preHead = new Node<T>;
        _preHead->next = nullptr;
        // all values of _preHead are assigned
    }

    /// Деструктор (PraviloBolshoiTroiki)
    template <class T>
    LinkedList<T>::~LinkedList()
    {
        deleteNodes(_preHead, getTailNode()); // deleted [prehead+1, tail]
        delete _preHead; // deleted[prehead]
    }

    /// Constructor for copy (PraviloBolshoiTroiki)
    template<class T>
    LinkedList<T>::LinkedList(const LinkedList& other)
    {
        _preHead = new Node<T>;

        // pointers to look at heads
        Node<T>* this_preHead = _preHead;
        Node<T>* other_preHead = other.getPreHead();

        while (other_preHead->next != nullptr)
        {
            this_preHead->next = new Node<T>; // creating node
            // NOT just pointing to existing memory

            // moving forward
            this_preHead = this_preHead->next;
            other_preHead = other_preHead->next;

            // launching T constructor (for "hard" objs)
            this_preHead->value = T(other_preHead->value);
        }
    }

    /// operator = (PraviloBolshoiTroiki)
    template<class T>
    LinkedList<T> &LinkedList<T>::operator=(const LinkedList& other)
    {
        // not allowing to A = A
        if (this == &other)
            return *this;

        // making temporary object
        LinkedList<T> tmp(other);

        // swapping values with it
        std::swap(this->_preHead, tmp._preHead);

        // returning this obj. tmp object will burrow bad values
        return *this;
    }


    /// Возвращаем псевдо-нулевой элемент PreHead
    template<class T>
    Node <T> *LinkedList<T>::getPreHead() const
    {
        return _preHead;
    }

    /// Возвращает элемент по индексу. Операция дорогая, сложность — O(i)
    template<class T>
    T &LinkedList<T>::operator[](int i)
    {
        if (i < 0 && i >= size())
            throw std::out_of_range("Index cant be < zero and > size!");

        if (_preHead->next == nullptr)
            throw std::out_of_range("No nodes are stored in this list!");

        // implementing function to return OBJECT by index, not just T value
        try
        {
            return getNodeByIndex(i)->value;
        } catch (std::out_of_range exception) {
            throw exception;
        }
    }

    /// Возвращает размер списка (число элементов). Операция дорогая - O(n), n = size of object
    template<class T>
    int LinkedList<T>::size()
    {
        if (_preHead->next == nullptr) // firstly checking if list is empty
            return 0;

        int amount = 0; // amount = 0 is compared to next of prehead (tmp)
        Node<T>* tmp = _preHead->next;

        while (tmp->next != nullptr)
        {
            amount++;
            tmp = tmp->next;
        }

        tmp = nullptr; // again "freeING" the pointer
        return amount + 1; // cause its counted from 0
    }

    /// Создает и добавляет новый узел, несущий значение \c value, в конец текущего списка.
    template<class T>
    void LinkedList<T>::addElementToEnd(T &value)
    {
        Node<T>* tmp = getTailNode();
        // after this WHILE tmp points at last element in the list

        Node<T>* added = new Node<T>(); // created an element to put in list
        added->value = value;
        //  added.next = nullptr; // we dont need this because in constructor of element
                                // next is already assigned nullptr

        tmp->next = added; // pointed last element to new one
        added = nullptr; // pointer used is now pointing to null
        tmp = nullptr; // pointer used is now pointing to null
    }

    /// Удаляет все узлы в диапазоне \c pNodeBefore->next ... \с pNodeLast (включительно).
    template<class T>
    void LinkedList<T>::deleteNodes(Node <T> *pNodeBefore, Node <T> *pNodeLast)
    {
        // if 1 of pointers is null we cant do anything
        if (pNodeBefore == nullptr || pNodeLast == nullptr)
            return;

        // if no elements are in OTHER list after pNodeBefore
        if (pNodeBefore->next == nullptr)
            return;

        // following pattern: moving element to next after pnodebefore
        // while pnodelast is not there and remove it
        while(pNodeBefore->next != pNodeLast)
        {
            if (pNodeBefore->next == nullptr) // just in case
            {   // there are no elements more in the list ???
                return; // we just escape this method
            }

            deleteNextNode(pNodeBefore);
            // in the method repointing to NEXT after destroyed element
            // is made.
        }

        // after this while pnodebefore is pointing to last pnode
        // so delete it!
        deleteNextNode(pNodeBefore); // deleting the pNodeLast
    }

    /// Удаляет узел \c pNodeBefore->next.
    template<class T>
    void LinkedList<T>::deleteNextNode(Node <T> *pNodeBefore)
    {
        // if pointer is null we cant do anything
        if (pNodeBefore == nullptr)
            return;

        // if no elements are in OTHER list after pNodeBefore
        if (pNodeBefore->next == nullptr)
            return;


        Node<T>* tmp = pNodeBefore->next; // making a pointer every time

        if (tmp->next == nullptr) // if it is the last element
        {
            delete tmp; // just destroy this element
            pNodeBefore->next = nullptr; // pnodebefore is the last now so it has to point to null
            return;
        }

        // in other case we have to repoint pNodeBefore
        pNodeBefore->next = tmp->next;
        // and delete tmp object
        delete tmp;
    }

    /// Перемещает узлы \c pNodeBefore->next ... \c pNodeLast другого списка в конец текущего списка.
    /// Из другого списка узлы pNodeBefore->next...pNodeLast исчезают.
    template<class T>
    void LinkedList<T>::moveNodesToEnd(Node <T> *pNodeBefore, Node <T> *pNodeLast)
    {
        // if 1 of pointers is null we cant do anything
        if (pNodeBefore == nullptr || pNodeLast == nullptr)
            return;

        // if in other list pnodebefore is just last element
        if (pNodeBefore->next == nullptr)
            return;

        Node<T>* tail = getTailNode(); // getting the last element in THIS list
        tail->next = pNodeBefore->next; // pointing after tail to the first moved node
        pNodeBefore->next = pNodeLast->next; // in OTHER list pointing far away after pnodeLast
        pNodeLast->next = nullptr; // making new tail in THIS list point to null (cause its in the end)
    }

    /// Перемещает узел pNodeBefore->next из другого списка в конец текущего списка.
    /// После перемещения из другого списка этот узел исключается.
    template<class T>
    void LinkedList<T>::moveNodeToEnd(Node <T> *pNodeBefore)
    {
        // if pointer is null we cant do anything
        if (pNodeBefore == nullptr)
            return;

        Node<T>* tail = getTailNode(); // getting the last element in THIS list
        tail->next = pNodeBefore->next; // pointing after tail to the moved node

        if (pNodeBefore->next->next == nullptr) // if moved was last element
            pNodeBefore->next = nullptr;    // point to null
        else
            pNodeBefore->next = pNodeBefore->next->next; // in other case point to element

        // and in THIS list finish with end->nullptr
        tail->next->next = nullptr;
    }

    /// Перемещает узлы \c pNodeBefore->next ... \c pNodeLast другого списка в текущий список
    /// после узла \c pNode.
    /// Из другого списка узлы pNodeBefore->next...pNodeLast исчезают.
    template<class T>
    void LinkedList<T>::moveNodesAfter(Node <T> *pNode, Node <T> *pNodeBefore, Node <T> *pNodeLast)
    {
        // if 1 of pointers is null we cant do anything
        if (pNodeBefore == nullptr || pNodeLast == nullptr || pNode == nullptr)
            return;

        // if chain is empty
        if (pNodeBefore->next == nullptr)
            return;

        // We have remembered the node we have to point pNodeLast
        Node<T>* afterPnode = pNode->next;

        pNode->next = pNodeBefore->next;
        pNodeBefore->next = pNodeLast->next; // finished with OTHER list
        pNodeLast->next = afterPnode; // and repointed last to THIS list
    }

    /// Перемещает узел pNodeBefore->next из другого списка в текущий список после узла pNode.
    /// После перемещения из другого списка этот узел исключается.
    template<class T>
    void LinkedList<T>::moveNodeAfter(Node <T> *pNode, Node <T> *pNodeBefore)
    {
        // if 1 of pointers is null we cant do anything
        if (pNodeBefore == nullptr || pNode == nullptr)
            return;

        // using only pointer remaking in this method
        Node<T>* pNodeNxt = pNode->next; // saving next to pnode
        pNode->next = pNodeBefore->next; // and pointing to the moved element
        pNodeBefore->next = pNodeBefore->next->next; // now before we lost the element we finish
                            // work with otherList
        pNode->next->next = pNodeNxt; // and finishing with rejoining

        pNodeNxt = nullptr;     // remember to nullptr used pointer
    }

    /// gets the pointer to last node in THIS list
    template <class T>
    Node<T>* LinkedList<T>::getTailNode()
    {
        Node<T>* tmp = LinkedList<T>::getPreHead();
        while (tmp->next != nullptr)
            tmp = tmp->next;

        return tmp;
    }

    /// Gets Node<T>* pointer (not T& as does operator[]) by index
    /// used for tests mostly (and is a useful function as well)
    template<class T>
    Node<T>* LinkedList<T>::getNodeByIndex(int i) {
        int index = 0; // pointing to 1st el
        Node<T>* tmp = _preHead->next; // doin it with pointer as well

        while(tmp->next != nullptr){
            if (index >= i)
                break;

            tmp = tmp->next;
            index++;
        }

        if(index == i) // checking on equality
            return tmp;
        throw std::out_of_range("Object is not reachable!");
    }
} // namespace xi