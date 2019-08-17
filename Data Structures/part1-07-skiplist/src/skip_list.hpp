////////////////////////////////////////////////////////////////////////////////
// Module Name:  skip_list.h/hpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      2.0.0
// Date:         28.10.2018
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

// !!! DO NOT include skip_list.h here, 'cause it leads to circular refs. !!!

#include <cstdlib>

//==============================================================================
// class NodeSkipList
//==============================================================================

template <class Value, class Key, int numLevels>
void NodeSkipList<Value, Key, numLevels>::clear(void)
{
    for (int i = 0; i < numLevels; ++i)
        Base::nextJump[i] = 0;

    Base::levelHighest = -1;
}

//------------------------------------------------------------------------------

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(void)
{
    clear();
}

//------------------------------------------------------------------------------

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(const Key& tkey)
{
    clear();

    Base::Base::key = tkey;
}

//------------------------------------------------------------------------------

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(const Key& tkey, const Value& val)
{
    clear();

    Base::Base::key = tkey;
    Base::Base::value = val;
}


//==============================================================================
// class SkipList
//==============================================================================

    /// \brief Constructor initializes with a probability.
    /// \param probability is the probability of each sparse level to appear.
    template <class Value, class Key, int numLevels>
    SkipList<Value, Key, numLevels>::SkipList(double probability)
    {
        _probability = probability;

        // Lets use m_pPreHead as a final sentinel element
        for (int i = 0; i < numLevels; ++i)
            Base::_preHead->nextJump[i] = Base::_preHead;

        Base::_preHead->levelHighest = numLevels - 1;
    }

    /// Virtual destructor: must take into account different levels!
    template <class Value, class Key, int numLevels>
    SkipList<Value, Key, numLevels>::~SkipList()
    {
//        // starting from head->next not to burrow _head immediately
//        Node* _head = Base::_preHead->next;
//
//        // going through all
//        while(_head->next != Base::_preHead)
//        {
//            // delete current and place head to next
//            Node* _delete = _head;
//            _head = _head->next; // ->next
//            delete _delete;
//        }
//
//        delete _head;
//        if (_head != Base::_preHead)
//            delete Base::_preHead;
    }

//    /// \brief Returns true if randomed number is
//    /// less than passed probability
//    bool checkProbabilityPlacement(double probability)
//    {
//        return ((double)rand()) / RAND_MAX <= probability;
//    }

    /// \brief Insert a new element into your list.
    ///
    /// Think very hard how will you guarantee thatnew element will be
    /// included in sparse levels correctly!
    ///
    /// Make different test. Check border cases - empty list, end of the list,
    /// et cetera ...
    template<class Value, class Key, int numLevels>
    void SkipList<Value, Key, numLevels>::insert(const Value &val, const Key &key)
    {
        srand(time(NULL)); // so random works correctly every time

        /*  Firstly we have to count amount of levels to place new Nodes
         *  from the very top of the list
         *  In other case we have to place node on bot and THEN
         *  we have to SEARCH again the position to insert nodes higher than 0 lvl
         */

        // -1 = identifier that there are no sparse levels
        int _levelAmount = -1;

        // if probability is 1 no need to random
        if (_probability == 1)
            _levelAmount = numLevels - 1;
        else if (_probability != 0) // the same with pr = 0
        {
            // If probability has to be counted
            // randomizing till its VERY TOP of levels
            while (_levelAmount < numLevels - 1 && (((double)rand()) / RAND_MAX <= _probability))
            {
                _levelAmount++;
            }

            // for testing
            // _levelAmount = 2;
        }

        // value of prehead that WILL NOT BE CHANGED in this method
        Node* _head = Base::_preHead;

        // object to place in skiplist
        Node* insertedNode = new Node(key, val);

        // making the field not null - placing the value of highest level
        insertedNode->levelHighest = _levelAmount;

        // searching the node to go through the list
        // it is the lowest level
        // prehead already has the value. So not going ->next
        Node* _finder = Base::_preHead;

        // going to the bot of skip-list
        while (_levelAmount > -1)
        {
            // searched the node of current level and went to right
            // because it is a prehead
            Node* _currentNode = _finder->nextJump[_levelAmount];

            // placing to the LEFT of element
            if (_currentNode == _head
                 || _currentNode->key > key)
            {
                // pointing new inserted[LEVEL] to next
                insertedNode->nextJump[_levelAmount] = _currentNode;
                // pointing to inserted[-1]
                _finder->nextJump[_levelAmount] = insertedNode;

                // decrementing level to place
                _levelAmount--;
            } else {
                // moving to the right!
                _finder = _currentNode;
            }
        }

        // now levelAmount is -1 -> so we are in the orderList
        // inserting node in the order list - simple inserting

        while (_finder->next != _head &&
                _finder->next->key <= key) // inserting after LAST =key so symbol "<="
            _finder = _finder->next;

        // redirecting new node next!
        insertedNode->next = _finder->next;
        _finder->next = insertedNode;
    }

    /// \brief Remove the node from the list and delete it from the memory.
    ///
    /// Check if an idiot called your function
    /// (i.e. don't delete pprehead occasionaly, and other cases)
    /// (Throw std::invalid_argument in such case.)
    ///
    /// Continue to think hard about sparse levels.
    /// Check different cases.
    template<class Value, class Key, int numLevels>
    void SkipList<Value, Key, numLevels>::removeNext(SkipList::Node *nodeBefore)
    {
        // headNode that will NOT be changed
        Node* _head = Base::_preHead;

        // first option in method - wrongly passed argument
        if(nodeBefore == nullptr || nodeBefore->next == nullptr || nodeBefore->next == _head)
            throw std::invalid_argument("Wrong nodeBefore argument in removeNext().");

        // node to go through list
        Node* _finder = _head;  // and its level
        int _currentLevel = _finder->levelHighest;

        while (_currentLevel > -1)
        {
            Node* _currentNode = _finder->nextJump[_currentLevel];

            // checking if keys are similar
            if (_currentNode->key == nodeBefore->next->key)
            {
                /* We have to find the last node in this lvl
                 * So we delete last Node with THAT key
                 *
                 * Going on this lvl till chain ends on head
                 * or keys start being bigger than THIS_KEY
                 */
                Node* _last = _finder;

                while(_last->nextJump[_currentLevel] != _head || // _HEAD check
                _last->nextJump[_currentLevel]->key > nodeBefore->next->key) // bigger KEYS CHECK
                {
                    // when reached the same pointer - just delete it
                    if(_last->nextJump[_currentLevel] == nodeBefore->next)
                    {
                        // replacing NEXT field
                        _last->nextJump[_currentLevel] = nodeBefore->next->nextJump[_currentLevel];

                        // i dont want to store notUsed Node* on this lvl of deleted node
                        // so i point it to nullptr. Done just for safety
                        nodeBefore->next->nextJump[_currentLevel] = nullptr;

                        // replacing finder to go to bot lvl from this node
                        _finder = _last;
                        break;
                    }

                    // moving ->
                    _last = _last->nextJump[_currentLevel];
                }

                // as in other methods going bot
                _currentLevel--;
            }
            else if (_currentNode == _head ||   // if chain has ended
                    _currentNode->key > nodeBefore->next->key)  // or key is already bigger
                // NO NEED TO GO TO RIGHT HERE. GOING BOT ALREADY
                _currentLevel--;
            else // always go to right if nothing happens
                _finder = _currentNode;
        }

        // have to remember deleting node
        // in other case we cant invoke [delete]
        Node* deleting = nodeBefore->next;

        nodeBefore->next = nodeBefore->next->next; // bot lvl redirect
        delete deleting;
    }

    /// \brief Find the last element with key strictly less than key.
    ///
    /// You have to do it in log(n) time,  i.e. you have to use sparse levels
    /// correctly from the highest to the lowest.
    ///
    /// If the key is less than the first element or the list is empty, returns _preHead.
    ///
    /// MADE BY ME::: if key is super big i'll return last element
    template<class Value, class Key, int numLevels>
    typename SkipList<Value, Key, numLevels>::Node *SkipList<Value, Key, numLevels>::findLastLessThan(const Key &key) const
    {
        // HEAD that is NOT changed
        Node* _head = Base::_preHead;

        // firstly getting prehead obviously
        Node* _finder = Base::_preHead;

        // checking last option of this method
        // if prehead points to itself
        if (_finder->next == _finder)
            return _finder;

        // if first VALUEABLE node has value <= key
        // returning head
        //TODO check >= or >
        if (_finder->next->key >= key)
            return _finder;

        // got the top node of prehead node
        Node* _currentNode;
        int _currentLevel = _finder->levelHighest;

        while (_currentLevel > -1)
        {
            // searched the node of current level and went to right
            // because it is a prehead
            _currentNode = _finder->nextJump[_currentLevel];

            // if no elements okay on this level we go to bot
            if (_currentNode == _head)
            {
                // reaching lowest lvl
                if (--_currentLevel == -1)
                    break;
                //_currentNode = _finder->nextJump[_currentLevel];
            }

            // placing to the LEFT of element
            if (_currentNode->key >= key)
            {
                _currentLevel--;
            } else {
                _finder = _currentNode;
            }
        }

        // searching on bot level
        // if it is end
        // or next-key bla-bla it is written below - the right statement
        while(_finder->next != Base::_preHead && _finder->next->key < key)
            _finder = _finder->next;

//        //TODO do we need to return head?
//        if(_finder->key >= key)
//            return _head;

        return _finder;
    }

    /// \brief Find the first element with key equal to key.
    ///
    /// You have to do it in log(n) time, i.e. you have to use sparse levels
    /// correctly from the highest to the lowest.
    ///
    /// If nothing was found, returns nullptr.
    template<class Value, class Key, int numLevels>
    typename SkipList<Value, Key, numLevels>::Node *SkipList<Value, Key, numLevels>::findFirst(const Key &key) const
    {
        // im not copycatting code!!!
        // so using findLastLessThan
        Node* before = findLastLessThan(key);

        // checking on last element or
        // the statement occasion
        if (before->next != Base::_preHead && before->next->key == key)
            return before->next;
        return nullptr;
    }