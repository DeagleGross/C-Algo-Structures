////////////////////////////////////////////////////////////////////////////////
// Module Name:  ordered_list.h/hpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      2.0.0
// Date:         28.10.2018
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

// !!! DO NOT include ordered_list.h here, 'cause it leads to circular refs. !!!


//=============================================================================
// class NodeSkipList
//=============================================================================


template <class Value, class Key, class Node>
OrderedList<Value, Key, Node>::OrderedList()
{
    _preHead = new Node;
    _preHead->next = _preHead;
}

//-----------------------------------------------------------------------------

    /// DESTRUCTOR
    template<class Value, class Key, class Node>
    OrderedList<Value, Key, Node>::~OrderedList()
    {
        // starting from head->next not to burrow _head immediately
        Node* tmp = _preHead->next;

        // going through all
        while (tmp->next != _preHead)
        {
            // delete current and place head to next
            Node* n = tmp;
            tmp = n->next; // --> nxt
            delete n;
        }

        delete _preHead;
    }

//-----------------------------------------------------------------------------

    /// Inserts a new node with the given (value == val) and (key == tkey).
    template <class Value, class Key, class Node >
    void OrderedList<Value,Key,Node>::insert(const Value& val, const Key& tkey)
    {
        // ищем "последний" элемент в цепочке
        Node* run = _preHead;
        while (run->next != _preHead)
            run = run->next;


        Node* tmp = new Node;
        tmp->next = run->next;
        tmp->key = tkey;
        tmp->value = val;

        run->next = tmp;
    }

//-----------------------------------------------------------------------------

template <class Value, class Key, class Node >
void OrderedList<Value,Key,Node>::removeNext(Node* nodeBefore)
{
    if (nodeBefore == nullptr
        || nodeBefore->next == nullptr
        || nodeBefore->next == _preHead)
    {
        return;
    }

    Node* tmp = nodeBefore->next;
    nodeBefore->next = tmp->next;
    delete tmp;
}

//-----------------------------------------------------------------------------


template <class Value, class Key, class Node >
Node* OrderedList<Value,Key,Node>::findLastLessThan(const Key& key) const
{
    Node* run = _preHead;
    while(run->next != _preHead && run->next->key < key)
        run = run->next;

    return run;
}

//-----------------------------------------------------------------------------

template <class Value, class Key, class Node >
Node* OrderedList<Value,Key,Node>::findFirst(const Key& key) const
{
    Node* run = _preHead;
    while (run->next != _preHead)
    {
        run = run->next;
        if (run->key == key)
            return run;
    }

    return nullptr;
}

//-----------------------------------------------------------------------------

// Returns the sentinel node
template <class Value, class Key, class Node>
Node* OrderedList<Value, Key, Node>::getPreHead() const
{
    return _preHead;
}

//-----------------------------------------------------------------------------

