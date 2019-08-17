///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains pseudo-implementation part of bidirectional list structure 
/// template declared in the file's h-counterpart
///
/// © Sergey Shershakov 2015–2017.
///
/// This code is for educational purposes of the course "Algorithms and Data 
/// Structures" provided by the School of Software Engineering of the Faculty 
/// of Computer Science at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///////////////////////////////////////////////////////////////////////////////

#include <stdexcept>


//==============================================================================
// class BidiList<T>::Node
//==============================================================================

    /** \brief Internal implementation of insertAfter() w/o any checkings
             *
             *  <b style='color:orange'>Must be implemented by students</b>
             */
    template <typename T>
    typename BidiLinkedList<T>::Node*
        BidiLinkedList<T>::Node::insertAfterInternal(Node* insNode)
    {
        // here we use "this" keyword for enhancing the fact we deal with current node!
        Node* afterNode = this->_next;      // an element, which was after node

        this->_next = insNode;
        insNode->_prev = this;
        insNode->_next = afterNode;

        if (afterNode) // checking if afternode is not null and pointing to last
            afterNode->_prev = insNode;

        return insNode;
    }

//==============================================================================
// class BidiList<T>
//==============================================================================




    template <typename T>
    BidiLinkedList<T>::~BidiLinkedList()
    {
        // everything is deleted in clear
        clear();
    }

    /** \brief Copy-constuctor
     */
    template<typename T>
    BidiLinkedList<T>::BidiLinkedList(const BidiLinkedList &other)
    {
        // firstly we have to point to nullptr
        // because we can use a great method - insertNodeAfter
        // and in it head and tail have to be null for 1st element to be placed!
        _head = nullptr;
        _tail = nullptr;

        // Pointer to copied list
        Node* _otherHead = other.getHeadNode();

        while(_otherHead != nullptr)
        {
            // object to place in this list
            Node* tmp = new Node(_otherHead->getValue());

            // inserting it (actually just placing in the end)
            insertNodeAfter(nullptr, tmp);

            _otherHead = _otherHead->_next; // incrementing
        }
    }

    /** \brief operator =
     */
    template<typename T>
    BidiLinkedList<T> &BidiLinkedList<T>::operator=(const BidiLinkedList &other)
    {
        // not allowing to A = A
        if (this == &other)
            return *this;

        // making temporary object
        BidiLinkedList<T> tmp(other);

        // swapping values with it
        std::swap(this->_head, other._head);
        std::swap(this->_tail, other._tail);

        // returning this obj. tmp object will burrow bad values
        return *this;
    }

    /**
    * \brief Clears the list (deletes all elements and frees memory)
    *
    *  <b style='color:orange'>Must be implemented by students</b>
    */
    template <typename T>
    void BidiLinkedList<T>::clear()
    {
        // if it empty and we do nothing!
        if (!_head || !_tail)
            return;

        // for Iterators occasion (empty node after tail)
        if (_tail->_next)
        {
            delete _tail->_next;
            _tail->_next = nullptr;
        }

        // for reverse iterator occasion (empty node before head)
        if (_head->_prev)
        {
            delete _head->_prev;
            _head->_prev = nullptr;
        }

        // after iterators occasions
        // list has only usable variables
        // without any empty nodes

        while(_head->_next != nullptr)  // when head is last we delete _now out of while{}
        {
            Node* _toDelete = _head; // to delete THIS element
            _head = _head->_next;
            delete _toDelete;
        }

        delete _head; // dont forget to delete last element
        // in this case head == tail because we have deleted all other elements
    }

    /** \brief Returns a size of a list that is equal to a number of storing elements */
    template <typename T>
    size_t BidiLinkedList<T>::getSize()
    {
        if (_size == NO_SIZE)
            calculateSize();

        return _size;
    }

    /** \brief (Re)calculate size of the list
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    template <typename T>
    void BidiLinkedList<T>::calculateSize()
    {
        if (!_head || !_tail) // if list is empty
        {
            _size = 0;
            return;
        }

        // head is already 1st element
        Node* tmp = _head;
        std::size_t value = 1;

        while (tmp != _tail)
        {
            value++;
            tmp = tmp->_next; // incrementing
        }

        _size = value; // passing value to _size field
    }

    /** \brief Returns a pointer to a last node
     *
     *  If the list is empty, returns nullptr
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    template <typename T>
    typename BidiLinkedList<T>::Node*
        BidiLinkedList<T>::getLastNode() const
    {
        return _tail; // tail is nullptr if _now list is empty
    }

    /** \brief Appends a given element (to the end) and returns a pointer to a new Node
     *  \param val const ref to a value of a appended element
     *  \return a pointer to a newly created node containing appended element
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    template <typename T>
    typename BidiLinkedList<T>::Node*
        BidiLinkedList<T>::appendEl(const T& val)
    {
        Node* newNode = new Node(val);

        // NOTHING TO ADD !

        // inserts after last node, size is going to be invalidated there
        return insertNodeAfter(getLastNode(), newNode);
    }


    /** \brief Inserts a given new (free) node \a insNode after node \a node
     *  \param node a node after which \a insNode is inserted
     *  \param insNode inserted node
     *  \return inserted node
     *
     *  if \a node is nullptr, inserts \a insNode at the very end
     *  If \a insNode is nullptr, an expection is raised.
     *  If \a insNode has a previous or next sibling, an exception is thrown.
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     *
     *  Nothing changed in this method!!!!
     */
    template <typename T>
    typename BidiLinkedList<T>::Node*
        BidiLinkedList<T>::insertNodeAfter(Node* node, Node* insNode)
    {
        if (!insNode)
            throw std::invalid_argument("`insNode` is nullptr");

        // check if a node is alone
        if (insNode->_next || insNode->_prev)
            throw std::invalid_argument("`insNode` has siblings. It seems _now isn't free");


        if (!node)
            node = getLastNode();

        // if last node is nullptr itself, _now means that no elements in the list at all
        if (!node)
        {
            _head = insNode;
            _tail = insNode;
        }
        else
        {
            node->insertAfterInternal(insNode);
            // If there is no one on the right from the inserted, update _tail.
            if (!insNode->_next)
                _tail = insNode;
        }

        invalidateSize();

        return insNode;
    }

    /** \brief Inserts a free chain given by its begin and end node after the given node.
     *  \param beg begin node of the inserted chain
     *  \param end end node of the inserted chain
     *  \param node a node, after which the chain is inserted
     *
     *  If either \a beg or \a end is nullptr, an expection is thrown
     *
     *  If inserted nodes \a beg and \a end  has a previous or next sibling respectively,
     *  an exception is thrown. Since it is impossible to check whether [beg,end] belongs
     *  to another list, using such an forbidden operation can lead to a run-time error.
     *
     *  If \a node is nullptr, the chain is inserted in the very end of the list
     */
    template<typename T>
    void
    BidiLinkedList<T>::insertNodesAfter(BidiLinkedList::Node *node, BidiLinkedList::Node *beg, BidiLinkedList::Node *end)
    {
        // if no chain is passed
        if (!beg || !end)
            throw std::invalid_argument("Begin or End Nodes cant be nulls!");

        // as written in comments we cant pass subChain to this function
        if (beg->_prev != nullptr || end->_next != nullptr)
            throw std::invalid_argument("Cant check beg-end chain to be a part of other list!");

        if (!node)  // getting last element
            node = getLastNode();

        if (!node)  // if _now is still null -> list is empty
        {
            _head = beg;    // then list = this chain
            _tail = end;
        } else {
            // head is not changed here
            Node* afterNode = node->_next;

            node->_next = beg;  // redirect of START of chain
            beg->_prev = node;

            end->_next = afterNode; // redirect of END of chain
            if (afterNode)
            {
                afterNode->_prev = end; // redirect of END of chain
            } else {
                // if afterNode is nullptr! - we have to redirect _tail to end
                _tail = end;
            }
        }

        invalidateSize(); // remake size()!
    }


    // Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
    // макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
    #ifdef IWANNAGET10POINTS

    /** \brief Inserts a given new node \a insNode before node \a node
     *  \param node a node before which \a insNode is inserted
     *  \param insNode inserted node
     *  \return inserted node
     *
     *
     *  if \a node is nullptr, inserts \a insNode in the very begin (as the head)
     *  If \a insNode is nullptr, an expection is raised
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    template <typename T>
    typename BidiLinkedList<T>::Node*
        BidiLinkedList<T>::insertNodeBefore(Node* node, Node* insNode)
    {
        // exception if nullptr is passed
        if (!insNode)
            throw std::invalid_argument("Null argument is passed to a function!");

        // as in insertNodeSAfter checking near nodes
        if (insNode->_next || insNode->_prev)
            throw std::invalid_argument("Cant check if node is a part of some beg-end chain!");

        if (!node) // getting last element
            node = getHeadNode();

        if (!node)  // if _now is still null -> list is empty
        {
            _head = insNode;    // then list = this chain
            _tail = insNode;
        }
        else
        {
            // redirected everything
            Node* nodeBefore = node->_prev;
            insNode->_next = node;
            node->_prev = insNode;
            insNode->_prev = nodeBefore;

            // if insNode point to null on left -> it is head!
            if (insNode->_prev == nullptr)
                _head = insNode;
            else
                // adding pointer to insNode from left if it is not head
                insNode->_prev->_next = insNode;
        }

        invalidateSize();

        return insNode;
    }


    /** \brief Inserts a free chain given by its begin and end node before the given node.
     *  \param beg begin node of the inserted chain
     *  \param end end node of the inserted chain
     *  \param node a node, before which the chain is inserted
     *
     *  If either \a beg or \a end is nullptr, an expection is thrown
     *
     *  If inserted nodes \a beg and \a end  has a previous or next sibling respectively,
     *  an exception is thrown. Since it is impossible to check whether [beg,end] belongs
     *  to another list, using such an forbidden operation can lead to a run-time error.
     *
     *  If \a node is nullptr, the chain is inserted in the very begin of the list
     *  If \a insNode has a previous or next sibling, an exception is thrown.
     */
    template <typename T>
    void BidiLinkedList<T>::insertNodesBefore(Node* node, Node* beg, Node* end)
    {
        // if no chain is passed
        if (!beg || !end)
            throw std::invalid_argument("Begin or End Nodes cant be nulls!");

        // as written in comments we cant pass subChain to this function
        if (beg->_prev != nullptr || end->_next != nullptr)
            throw std::invalid_argument("Cant check beg-end chain to be a part of other list!");

        if (!node)  // getting first element
            node = getHeadNode();

        if (!node)  // if _now is still null -> list is empty
        {
            _head = beg;    // then list = this chain
            _tail = end;
        } else {
            // tail is not changed here
            Node* beforeNode = node->_prev;

            node->_prev = end;  // redirect of END of chain
            end->_next = node;


            beg->_prev = beforeNode; // point to start of chain
            if (beforeNode != nullptr)
            {
                beforeNode->_next = beg; // insert chain START
            } else _head = beg; // if beforeNode is null we make head = begin of chain
        }

        invalidateSize(); // remake size()!
    }

    #endif // IWANNAGET10POINTS


    /** \brief Cuts a chain of nodes determined by its begin and end node from the list
     *  \param beg begin node of the chain
     *  \param end end node of the chain
     *
     *  If either \a beg or \a end is nullptr, an expection is thrown
     *  A cutted chain should be a part of the list, otherwise unpredictable behavior
     *  is expected
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    template <typename T>
    void BidiLinkedList<T>::cutNodes(Node* beg, Node* end)
    {
        // if no chain is passed
        if (!beg || !end)
            throw std::invalid_argument("Either `beg` or `end` is nullptr");

        // getting pointers to before and after CHAIN
        Node* beforeChain = beg->_prev;
        Node* afterChain = end->_next;

        // redirecting BEFORE chain to AFTER chain
        // here we have a lot of checks on EXISTING an element
        if (afterChain)
            if (beforeChain)
                beforeChain->_next = afterChain;
            else {
                _head = afterChain; // redirecting head if nothing before chain is found
                if (_head) _head->_prev = nullptr; // and pointing it to nullptr on left
            }
        else {
            _tail = beforeChain; // redirecting tail if nothing after chain is found
            if (_tail) _tail->_next = nullptr; // and pointing it to nullptr on right
        }

        // redirecting AFTER chain to BEFORE chain
        // doin the same with chain but AFTER it
        if (beforeChain)
            if (afterChain)
                afterChain->_prev = beforeChain;
            else {
                _tail = beforeChain;
                if (_tail) _tail->_next = nullptr;
            }
        else {
            _head = afterChain;
            if (_head) _head->_prev = nullptr;
        }

        // NULLing the pointers of new chain
        beg->_prev = nullptr;
        end->_next = nullptr; // method is not for deleting them from memory!

        // not forget to invalidateSize();
        invalidateSize();
    }


    /** \brief Cuts a given node from the list
     *  \param node  node to be cut
     *  \returns cutted node
     *
     *  If \a node is nullptr, an expection is thrown
     *  A cutted node should be a part of the list, otherwise unpredictable behavior
     *  is expected
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    template <typename T>
    typename BidiLinkedList<T>::Node*
        BidiLinkedList<T>::cutNode(Node* node)
    {
        // if nullptr is passed
        if (!node)
            throw std::invalid_argument("Null node to be deleted! Error.");

        // checking is there a previous before node
        if (node->_prev != nullptr)
            node->_prev->_next = node->_next;
        else
            _head = node->_next;

        // checking if there a next after node
        if (node->_next != nullptr)
            node->_next->_prev = node->_prev;
        else
            _tail = node->_prev;

        invalidateSize(); // INVOKED AFTER STRUCTURE IS CHANGED!

        return node; // dont delete _now - just return _now (returns cutted node, not deletes)
    }


    /** \brief Finds first node carrying a given value \a val, starting from a given
     *  node \a startFrom, and returns it
     *  \param startFrom first node in a chain of all nodes algorithm starts searching from
     *  \param val value to search for
     *  \return a pointer to a node with found value; if no appropriate node is found,
     *  returns nullptr
     *
     *  Node \a startFrom is also tested for suitability of the search condition.
     *  If the given \a startFrom node is nullptr, returns nullptr immediately
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    template <typename T>
    typename BidiLinkedList<T>::Node*
        BidiLinkedList<T>::findFirst(Node* startFrom, const T& val)
    {
        // if nullptr is passed
        if (!startFrom)
            return nullptr;

        while (startFrom) // going next till startFrom is NULLPTR
        {
            if (startFrom->_val == val) // to return value
                return startFrom;

            startFrom = startFrom->_next;
        }

        return nullptr; // not found
    }



    /** \brief Find all occurences of a value \a val and returns a C-style array with
     *  non-free pointers to a nodes of **this list**.
     *  \param size *out* determines a size of returning array if the latter is not nullptr
     *  \return a newly created array of Node* pointers with nodes with value \a val
     *
     *  Input parameters are the same as in findFirst() method.
     *  Returned array should be freed by caller!
     *  If no matches are found, returns a nullptr
     *  If the given \a startFrom node is nullptr, returns nullptr immediately
     *
     *  Try not to use std:: containers while implementing the method!
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     *
     *  Method is working in such way:
     *  _realSize - actual amount of variables that were inserted in array
     *  size - amount of variables that can fit in array (at the moment) (that value can be changed)
     *  passing array when it is null or full to another function for incremeneting its size
     */
    template <typename T>
    typename BidiLinkedList<T>::Node**
        BidiLinkedList<T>::findAll(Node* startFrom, const T& val, int& size)
    {
        // firstly if nullptr is passed
        if (!startFrom)
            return nullptr;

        // try not to use any standard containers. create an array only when found a first occurence
        int _realSize = 0; // actual amount of inserted elements
        size = 0;   // amount to fit
        Node** res = nullptr; // array to fill

        // goin through all elements
        while (startFrom)
        {
            if (startFrom->_val == val) // comparing values
            {
                // if array is full or is nullptr - pass it for resize or
                // actual creation of array
                if (_realSize == size || !res)
                    resizeNodeArray(res, size);
                // and insert value
                res[_realSize++] = startFrom;
            }

            startFrom = startFrom->_next; // going forward
        }

        // we are reforcing size to = realsize
        // because size is a FULL size
        // realsize contains only used elements
        size = _realSize;
        return res;
    }

    /** \brief doubles size of dynamic Node** array
     *  \param res array to resize
     *  \param size current size of this array
     *
     *   If array is null - creates an empty array of 10 elements
     *   In other case makes it size bigger in 2 times!
     */
    template <typename T>
    void BidiLinkedList<T>::resizeNodeArray(Node** &res, int& size)
    {
        if (!res || size == 0) // just for creation of array from nullptr
        {
            res = new Node*[10];
            size = 10;
            return;
        }

        // here comes the real work in function - resize
        Node** _newArr = new Node*[size*2]; // creating new array with size*2
        for (int i = 0; i < size; ++i) // rewriting values down here
            _newArr[i] = res[i];

        // pointer under which to delete an array
        Node** _toDelete = res;
        delete[] _toDelete;

        // repoint res and newarr = null
        res = _newArr; _newArr = nullptr;
        size *= 2; // dont forget to remake size;
    }


    // Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
    // макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
    #ifdef IWANNAGET10POINTS

    /** \brief Cuts all nodes with value that is equal to \a val and returns an
    *  array of cutted nodes.
    *
    *  For parameters, return value and special behavior description, see findAll()
    *
    *  <b style='color:orange'>Must be implemented by students</b>
    */
    template <typename T>
    typename BidiLinkedList<T>::Node**
    BidiLinkedList<T>::cutAll(Node* startFrom, const T& val, int& size)
    {
        // checking nullptr is passed
        if (!startFrom)
            return nullptr;

        // finds all elements and stores it in array
        Node** _found = findAll(startFrom, val, size);

        // foreach node we just cut it individually from list
        for (int i = 0; i < size; ++i)
            cutNode(_found[i]);

        return _found; // returnd array of individual nodes (with prev and next = nullptr)!
    }

#endif // IWANNAGET10POINTS

#ifdef TEST_ITERATOR

    /** \brief Returns an iterator to the first element of the list
    *  If the list is empty - returns an iterator to the non existing element. (Like end() does.)
    */
    template<typename T>
    typename BidiLinkedList<T>::iterator BidiLinkedList<T>::begin()
    {
        if (_head)
            return MyIterator(_head);
        else {
            // if head stores nothing - passing nullptr object of Node*
            return MyIterator();
        }
    }

    /** \brief Returns an iterator to the non existing element after the end of the list.
    *  If we decrement the end() iterator, it points to the last element of the list. (If it exists.)
    */
    template<typename T>
    typename BidiLinkedList<T>::iterator BidiLinkedList<T>::end()
    {
        // if tail stores nothing - passing nullptr object
        if (!_tail)
        {
            return MyIterator();
        }

        // tail has to be smth or not to be end (we create 1 node after it in other case)
        if (_tail && !_tail->_next)
        {
            _tail->_next = new Node();
            _tail->_next->_prev = _tail;
            return MyIterator(_tail->_next);
        } else
            return MyIterator(_tail->_next);
    }

    /** \brief Returns an iterator to the first element of the list
     *  If the list is empty - returns an iterator to the non existing element. (Like end() does.)
     */
    template<typename T>
    typename BidiLinkedList<T>::const_iterator BidiLinkedList<T>::cbegin()
    {
        if (_head)
            return MyConstIterator(_head);
        else {
            // if head stores nothing - passing nullptr object
            return MyConstIterator();
        }
    }

    /** \brief Returns an iterator to the non existing element after the end of the list.
    *  If we decrement the end() iterator, it points to the last element of the list. (If it exists.)
    */
    template<typename T>
    typename BidiLinkedList<T>::const_iterator BidiLinkedList<T>::cend()
    {
        // if tail stores nothing - passing nullptr object of Node*
        if (!_tail)
        {
            return MyConstIterator();
        }

        // tail has to be smth or not to be end (we create 1 node after it in other case)
        if (_tail && !_tail->_next)
        {
            _tail->_next = new Node();
            _tail->_next->_prev = _tail;
            return MyConstIterator(_tail->_next);
        } else
            return MyConstIterator(_tail->_next);
    }

    /** \brief Returns an iterator to the last! element of the list
     *  If the list is empty - returns an iterator to the non existing element. (Like end() does.)
     */
    template<typename T>
    typename BidiLinkedList<T>::reverse_iterator BidiLinkedList<T>::rbegin()
    {
        // in reverse we have tail in rbegin
        if (_tail)
            return MyReverseIterator(_tail);
        else {
            return MyReverseIterator();
        }
    }

    /** \brief Returns an iterator to the non existing element after the head (before it) of the list.
    *  If we decrement the end() iterator, it points to the last element of the list. (If it exists.)
    */
    template<typename T>
    typename BidiLinkedList<T>::reverse_iterator BidiLinkedList<T>::rend()
    {
        // if stores nothing passing nullptr
        if (!_head)
        {
            return MyReverseIterator();
        }

        // if head has nothing before it we create a node (empty node)
        if (_head && !_head->_prev)
        {
            _head->_prev = new Node();
            _head->_prev->_next = _head;
            return MyReverseIterator(_head->_prev);
        } else
            return MyReverseIterator(_head->_prev);
    }

    /** \brief Returns an iterator to the last! element of the list
     *  If the list is empty - returns an iterator to the non existing element. (Like end() does.)
     */
    template<typename T>
    typename BidiLinkedList<T>::const_reverse_iterator BidiLinkedList<T>::crbegin()
    {
        // in reverse we have tail in rbegin
        if (_tail)
            return MyConstReverseIterator(_tail);
        else {
            return MyConstReverseIterator();
        }
    }

    /** \brief Returns an iterator to the non existing element after the head (before it) of the list.
    *  If we decrement the end() iterator, it points to the last element of the list. (If it exists.)
    */
    template<typename T>
    typename BidiLinkedList<T>::const_reverse_iterator BidiLinkedList<T>::crend()
    {
        // if stores nothing passing nullptr
        if (!_head)
        {
            return MyConstReverseIterator();
        }

        // if head has nothing before it we create a node (empty node)
        if (_head && !_head->_prev)
        {
            _head->_prev = new Node();
            _head->_prev->_next = _head;
            return MyConstReverseIterator(_head->_prev);
        } else
            return MyConstReverseIterator(_head->_prev);
    }

#endif // TEST_ITERATOR