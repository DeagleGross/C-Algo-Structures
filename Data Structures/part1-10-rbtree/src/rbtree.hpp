////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Реализация классов красно-черного дерева
/// \author    Sergey Shershakov
/// \version   0.1.0
/// \date      01.05.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// "Реализация" (шаблонов) методов, описанных в файле rbtree.h
///
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>        // std::invalid_argument


namespace xi {


//==============================================================================
// class RBTree::node
//==============================================================================

///< Деструктор нода гарантированно грохнет всех потомков.
template <typename Element, typename Compar >
RBTree<Element, Compar>::Node::~Node()
{
    if (_left)
        delete _left;
    if (_right)
        delete _right;
}

/** \brief Устанавливает левого потомка в \c lf. Если потомок не ноль, делает
 *  для него текущий нод родителем, а у его предка отключает дочернюю связь.
 */
template <typename Element, typename Compar>
typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::Node::setLeft(Node* lf)
{
    // предупреждаем повторное присвоение
    if (_left == lf)
        return nullptr;

    // если новый левый — действительный элемент
    if (lf)
    {
        // если у него был родитель
        if (lf->_parent)
        {
            // ищем у родителя, кем был этот элемент, и вместо него ставим бублик
            if (lf->_parent->_left == lf)
                lf->_parent->_left = nullptr;
            else                                    // доп. не проверяем, что он был правым, иначе нарушение целостности
                lf->_parent->_right = nullptr;      
        }

        // задаем нового родителя
        lf->_parent = this;
    }

    // если у текущего уже был один левый — отменяем его родительскую связь и вернем его
    Node* prevLeft = _left;
    _left = lf;

    if (prevLeft)
        prevLeft->_parent = nullptr;

    return prevLeft;
}

/** \brief Устанавливает правого потомка в \c rg. Если потомок не ноль, делает
 *  для него текущий нод родителем, а у его предка отключает дочернюю связь.
 */
template <typename Element, typename Compar>
typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::Node::setRight(Node* rg)
{
    // предупреждаем повторное присвоение
    if (_right == rg)
        return nullptr;

    // если новый правый — действительный элемент
    if (rg)
    {
        // если у него был родитель
        if (rg->_parent)
        {
            // ищем у родителя, кем был этот элемент, и вместо него ставим бублик
            if (rg->_parent->_left == rg)
                rg->_parent->_left = nullptr;
            else                                    // доп. не проверяем, что он был правым, иначе нарушение целостности
                rg->_parent->_right = nullptr;
        }

        // задаем нового родителя
        rg->_parent = this;
    }

    // если у текущего уже был один левый — отменяем его родительскую связь и вернем его
    Node* prevRight = _right;
    _right = rg;

    if (prevRight)
        prevRight->_parent = nullptr;

    return prevRight;
}


//==============================================================================
// class RBTree
//==============================================================================

///< Конструктор по умолчанию.
template <typename Element, typename Compar >
RBTree<Element, Compar>::RBTree()
{
    _root = nullptr;
    _dumper = nullptr;
}

///< Деструктор.
template <typename Element, typename Compar >
RBTree<Element, Compar>::~RBTree()
{
    // грохаем пока что всех через корень
    if (_root)
        delete _root;
}

/** \brief Удаляет нод со всеми его потомками, освобождая память из-под них. */
template <typename Element, typename Compar >
void RBTree<Element, Compar>::deleteNode(Node* nd)
{
    // если переданный узел не существует, просто ничего не делаем, т.к. в вызывающем проверок нет
    if (nd == nullptr)
        return;

    // потомков убьет в деструкторе
    delete nd;
}

/** \brief Вставляет элемент \c key в дерево.
 *
 *
 *  <b style='color:orange'>Для реализации студентами.</b>
 *
 *  Т.к. дубликаты не допустимы, элемента с ключом \c key в дереве быть не должно. Если
 *  же такой элемент уже существует, генерируется исключительная ситуация \c std::invalid_argument.
 */
template <typename Element, typename Compar >
void RBTree<Element, Compar>::insert(const Element& key)
{
    // этот метод можно оставить студентам целиком
    Node* newNode = insertNewBstEl(key);

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_BST_INS, this, newNode);

    rebalance(newNode);

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_INSERT, this, newNode);

}

/** \brief Ищет элемент \c key в дереве и возвращает соответствующий ему узел.
 *
 *  <b style='color:orange'>Для реализации студентами.</b>
 *
 *  \returns узел элемента \c key, если он есть в дереве, иначе \c nullptr.
 */
template <typename Element, typename Compar>
const typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::find(const Element& key)
{
    /*
     * IDE показывает ошибку с использованием компаратора
     * функции оставлены в закомментаренном виде
     * Сравнение прописано через обычные знаки <, >, !=, ==
     */

    // if something wrong was passed
    if (!key)
        return nullptr;

    // tree is Empty -> so we return nullptr
    if (!_root)
        return nullptr;

    // making a pointer to root
    Node* _rootCopy = _root;

    // while we have not the same value
    while
     // (_compar(_rootCopy->_key, key) || _compar(key, _rootCopy->_key))
     (_rootCopy->_key != key)
    {
        // if this value is less -> going to right
        if
         // (_compar(_rootCopy->_key, key))
         (_rootCopy->_key < key)
        {
            // if child exists
            if (_rootCopy->_right)
            {
                _rootCopy = _rootCopy->_right;
                continue;
            }
        }

        // if this value is more -> going to left
        if
         //(!_compar(key, _rootCopy->_key) && !(!_compar(_rootCopy->_key, key) && !_compar(key, _rootCopy->_key)))
         (_rootCopy->_key > key)
        {
            // if child exists
            if (_rootCopy->_left)
            {
                _rootCopy = _rootCopy->_left;
                continue;
            }
        }

        // if no "if" cases worked out -> nothing could be found - return nullptr
        // setting node* as nullptr and going to return
        _rootCopy = nullptr;
        break;
    }

    return _rootCopy;
}

/** ADDED BY ME - NOT CONST
 *
 * \brief Ищет элемент \c key в дереве и возвращает соответствующий ему узел.
 *
 *  <b style='color:orange'>Для реализации студентами.</b>
 *
 *  \returns узел элемента \c key, если он есть в дереве, иначе \c nullptr.
 */
template <typename Element, typename Compar>
typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::findReal(const Element& key)
{
    /*
     * IDE показывает ошибку с использованием компаратора
     * функции оставлены в закомментаренном виде
     * Сравнение прописано через обычные знаки <, >, !=, ==
     */

    // if something wrong was passed
    if (!key)
        return nullptr;

    // tree is Empty -> so we return nullptr
    if (!_root)
        return nullptr;

    // making a pointer to root
    Node* _rootCopy = _root;

    // while we have not the same value
    while
        // (_compar(_rootCopy->_key, key) || _compar(key, _rootCopy->_key))
            (_rootCopy->_key != key)
    {
        // if this value is less -> going to right
        if
            // (_compar(_rootCopy->_key, key))
                (_rootCopy->_key < key)
        {
            // if child exists
            if (_rootCopy->_right)
            {
                _rootCopy = _rootCopy->_right;
                continue;
            }
        }

        // if this value is more -> going to left
        if
            //(!_compar(key, _rootCopy->_key) && !(!_compar(_rootCopy->_key, key) && !_compar(key, _rootCopy->_key)))
                (_rootCopy->_key > key)
        {
            // if child exists
            if (_rootCopy->_left)
            {
                _rootCopy = _rootCopy->_left;
                continue;
            }
        }

        // if no "if" cases worked out -> nothing could be found - return nullptr
        // setting node* as nullptr and going to return
        _rootCopy = nullptr;
        break;
    }

    return _rootCopy;
}


/** \brief Добавляет новый узел в дерево, как в обычном BST.
 *
 *  <b style='color:orange'>Для реализации студентами.</b>
 *
 *  Т.к. дубликаты не допустимы, элемента с ключом \c key в дереве быть не должно. Если
 *  же такой элемент уже существует, генерируется исключительная ситуация \c std::invalid_argument.
 *
 *  Дубликаты не разрешены, исключение то же, что и у \c insert().
 *  \return Указатель на новодобавленный элемент.
 */
template <typename Element, typename Compar >
typename RBTree<Element, Compar>::Node* 
        RBTree<Element, Compar>::insertNewBstEl(const Element& key)
{
    /*
     * IDE показывает ошибку с использованием компаратора
     * функции оставлены в закомментаренном виде
     * Сравнение прописано через обычные знаки <, >, !=, ==
     */

    // firstly checking if the element with this key exists
    if (find(key))
        throw std::invalid_argument("Node with the same value already exists");

    /*  created a new node with params
     * LEFT = null
     * RIGHT = null
     * PARENT = null
     * KEY = key
     * COLOR = RED - because in RBT all inserted nodes are RED
     */
    Node* _added = new Node(key, nullptr, nullptr, nullptr, RED);

    // if there is no root - so we add the first element in the tree
    if (!_root)
    {
        _added->_color = BLACK; // root has to have BLACK color - we can easily do it here
        _root = _added;
        return _added;
    }

    // and doing the same as in find - going from root
    Node* _rootCopy = _root;

    // while added has no parent = it is not inserted
    while (!_added->_parent)
    {
        // if now value is lower - going to right
        if
         // (_compar(_rootCopy->_key, key))
         (_rootCopy->_key < key)
        {
            // if child exists - repointing rootCopy
            if (_rootCopy->_right)
            {
                _rootCopy = _rootCopy->_right;
                continue;
            }
            else // we found a place to put new node
            {
                _rootCopy->_right = _added;
                _added->_parent = _rootCopy;
                continue;
            }
        }

        // if now value is higher - going to left
        if
         //(!_compar(key, _rootCopy->_key) && !(!_compar(_rootCopy->_key, key) && !_compar(key, _rootCopy->_key)))
         (_rootCopy->_key > key)
        {
            // if child exists - repointing rootCopy
            if (_rootCopy->_left)
            {
                _rootCopy = _rootCopy->_left;
                continue;
            }
            else // we found a place to put new node
            {
                _rootCopy->_left = _added;
                _added->_parent = _rootCopy;
                continue;
            }
        }

        // if no "if" cases worked - something bad happended
        // throwing an exception
        throw std::invalid_argument("Node cant be inserted properly");
    }

    return _added;
}


/** \brief Выполняет перебалансировку локальных предков узла \c nd: папы, дяди и дедушки.
 *
 *  <b style='color:orange'>Метод может быть реализован студентами в порядке декомпозиции.</b>
 *
 *  \returns Новый актуальный узел, для которого могут нарушаться правила.
 */
template <typename Element, typename Compar >
typename RBTree<Element, Compar>::Node* 
    RBTree<Element, Compar>::rebalanceDUG(Node* nd)
{
    // TODO: этот метод студенты могут оставить и реализовать при декомпозиции балансировки дерева
    // В методе оставлены некоторые важные комментарии/snippet-ы


    // попадание в этот метод уже означает, что папа есть (а вот про дедушку пока не известно)
    //...

//    Node* uncle = ...; // для левого случая нужен правый дядя и наоборот.

    // если дядя такой же красный, как сам нод и его папа...
//    if (... uncle->isRed() ...)
    {
        // дядю и папу красим в черное
        // а дедушку — в коммунистические цвета

        // отладочное событие
        if (_dumper)
            _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR1, this, nd);

        // теперь чередование цветов "узел-папа-дедушка-дядя" — К-Ч-К-Ч, но надо разобраться, что там
        // с дедушкой и его предками, поэтому продолжим с дедушкой
        //..
    }

    // дядя черный
    // смотрим, является ли узел "правильно-правым" у папочки
//    if (...)                                        // для левого случая нужен правый узел, поэтом отрицание
    {                                               // CASE2 в действии

        // ... при вращении будет вызвано отладочное событие 
        // ...

    }


    // ...

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3D, this, nd);


    // деда в красный

    // ...

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3G, this, nd);

    // ...


    return nd;
}


/** \brief Выполняет перебалансировку дерева после добавления нового элемента в узел \c nd.
 *
 *  <b style='color:orange'>Для реализации студентами.</b>
 */
template <typename Element, typename Compar >
void RBTree<Element, Compar>::rebalance(Node* nd)
{
    // it is root!
    if (!nd->_parent)
    {
        // doing nothing after painting black
        nd->_color = BLACK;
        return;
    }

    // if parent exists and he is black
    // we do nothing! ooh it was easy
    if (nd->_parent)
        if (nd->_parent->_color == BLACK)
            return;

    // doing repaint all the time - while we reach root
    while (nd && nd != _root && nd->isDaddyRed() && nd->_color == RED)
    {
        // TODO LEFT SIDE
        // if parent exists and he is left daddy
        if (!nd->isDadRightParent())
        {
            Node* uncle = nullptr;

            if (nd->_parent->_parent)
                uncle = nd->_parent->_parent->_right;

            if (uncle && uncle->_color == RED)
            {
                /* changing color of <what-to>:
                 * //nd - same
                 * //nd->parent - black
                 * //nd->grandparent - red - becomes new nd
                 * nd->uncle black
                 */

                // PARENT -> BLACK
                nd->_parent->_color = BLACK;
                // UNCLE -> BLACK
                uncle->_color = BLACK;
                // GRANDPA -> RED
                nd->_parent->_parent->_color = RED;
                // REPLACE ND to GRANDPA
                nd = nd->_parent->_parent;
                // going to recursive of new ND
                continue;
            }
            else if (nd->isRightChild())
            {
                /*
                 * LEFTY - CASE - 2
                 * THEN LEFTY - CASE - 3
                 */

                this->rotLeft(nd->_parent);
                this->rotRight(nd->_parent);

                    // and painting
                    nd->_color = BLACK;
                    nd->_right->_color = RED;

                nd = nd->_parent;
                continue;
            } else
            {
                /*
                 * LEFTY - CASE - 3
                 */

                this->rotRight(nd->_parent->_parent);

                    // and painting
                    nd->_parent->_color = BLACK;
                    nd->_parent->_right->_color = RED;

                nd = nd->_parent;
                continue;
            }
        }


        // TODO RIGHT SIDE
        // if parent exists and he is right daddy
        if (nd->isDadRightParent())
        {
            Node* uncle = nullptr;

            if (nd->_parent->_parent)
                uncle = nd->_parent->_parent->_left;

            if (uncle && uncle->_color == RED)
            {
                /* changing color of <what-to>:
                 * //nd - same
                 * //nd->parent - black
                 * //nd->grandparent - red - becomes new nd
                 * nd->uncle black
                 */

                // PARENT -> BLACK
                nd->_parent->_color = BLACK;
                // UNCLE -> BLACK
                uncle->_color = BLACK;
                // GRANDPA -> RED
                nd->_parent->_parent->_color = RED;
                // REPLACE ND to GRANDPA
                nd = nd->_parent->_parent;
                // going to recursive of new ND
                continue;
            }
            else if (nd->isRightChild())
            {
                /*
                 * RIGHTY - CASE - 3
                 */

                this->rotLeft(nd->_parent->_parent);

                    // and painting
                    nd->_parent->_color = BLACK;
                    nd->_parent->_left->_color = RED;

                nd = nd->_parent;
                continue;
            } else
            {
                /*
                 * RIGHTY - CASE - 2
                 * THEN RIGHTY - CASE - 3
                 */

                this->rotRight(nd->_parent);
                this->rotLeft(nd->_parent);

                    // and painting
                    nd->_color = BLACK;
                    nd->_left->_color = RED;

                nd = nd->_parent;
                continue;
            }
        }
    }

    if (_root->_color == RED)
        _root->_color = BLACK;
}

/** \brief Ищет узел, соответствующий ключу \c key, и удаляет узел из дерева
 *  с последующей перебалансировкой.
 *
 *  <b style='color:orange'>Для реализации студентами.</b>
 *
 *  Если соответствующего ключа нет в дереве, генерирует исключительную ситуацию \c std::invalid_argument.
 */
template<typename Element, typename Compar>
void RBTree<Element, Compar>::remove(const Element &key)
{
    // using WikiKonspekti as doc to write this

    // using custom Find to get changeable node - found node to delete
    Node* z = this->findReal(key);

//    // firstly - if node has no children
//    if (node->isLeaf())
//    {
//        if (node->_parent)
//            if (node->isRightChild())
//                node->_parent->_right = nullptr;
//            else
//                node->_parent->_left = nullptr;
//        else
//            this->_root = nullptr;
//        // making root of tree = null if no parent and is leaf
//    }
//
//    // here if there is 1 child
//    if (node->_left && !node->_right)
//        this->replace(node, node->_left);
//    else if (!node->_left && node->_right)
//        this->replace(node, node->_right);
//
//
//    if (node->_left && node->_right)
//    {
//        // first finding min in right Subtree
//        Node* min = findMinInSubTree(node->_right);
//        if (min->_right)
//            min->_right->_parent = min->_parent;
//        if (min == _root)
//            this->_root = min->_right;
//        else
//        {
//            if (min->isRightChild())
//                min->_parent->_right = min->_right;
//            else
//                min->_parent->_left = min->_right;
//        }
//    }

    Node* y = z;
    Node* x;
    Color originalColor = y->_color;

    if (!z->_left)
    {
        x = z->_right;
        replace(z, z->_right);
    } else if (!z->_right)
    {
        x = z->_left;
        replace(z, z->_left);
    } else
    {
        y = findMinInSubTree(z->_right);
        originalColor = y->_color;
        x = y->_right;
        if (y->_parent == z)
            x->_parent = y;
        else
        {
            replace(y, y->_right);
            y->_right = z->_right;
            y->_right->_parent = y;
        }

        replace(z, y);
        y->_left = z->_left;
        y->_left->_parent = y;
        y->_color = z->_color;
    }

    if (originalColor == BLACK)
        deleteFix(x);
}

template<typename Element, typename Compar>
void RBTree<Element, Compar>::deleteFix(RBTree::Node* x)
{
    Node* w;

    while (x != this->_root && x->_color == BLACK)
    {
        if (x->isLeftChild())
        {
            w = x->_parent->_right;

            // TODO CASE 1
            if (w->_color == RED)
            {
                w->_color = BLACK;
                x->_parent->_color = RED;
                rotLeft(x->_parent);
                w = x->_parent->_right;
            }

            // TODO CASE 2
            if (w->_left->_color == BLACK and w->_right->_color == BLACK)
            {
                w->_color = RED;
                x = x->_parent;
            }

            // TODO CASE 3 - 4
            else
            {
                if (w->_right->_color == BLACK)
                {
                    w->_left->_color = BLACK;
                    w->_color = RED;
                    rotRight(w);
                    w = x->_parent->_right;
                }

                w->_color = x->_parent->_color;
                x->_parent->_color = BLACK;
                w->_right->_color = BLACK;
                rotLeft(x->_parent);
                x = this->_root; // ???????
            }
        }
        else
        {
            w = x->_parent->_left;
            if (w->_color == RED)
            {
                w->_color = BLACK;
                x->_parent->_color = RED;

            }
        }
    }
}


/** \brief Вращает поддерево относительно узла \c nd влево.
 *
 *  <b style='color:orange'>Для реализации студентами.</b>
 *
 *  Требование: правый ребенок узла \c nd не должен быть null, иначе генерируется
 *  исключительная ситуация \c std::invalid_argument.
 */
template <typename Element, typename Compar>
void RBTree<Element, Compar>::rotLeft(typename RBTree<Element, Compar>::Node* nd)
{
    /* I dont know why i wrote comments in russian
     * Этот метод ПЕРЕТАСКИВАЕТ условно выполняет поворот
     * LEFT-CASE 2 или RIGHT-CASE 3
     * -----------------------------
     * Перекраска осуществляется в зависимости от текущего case'а
     *
     * nd - папа P вершины N
     * nd->right - потомок-вершина N
     * nd->parent - дедушка G вершины N
     */

    Node* Child = nd->_right;
        // immediately checking on exception
        if (!Child)
            throw std::invalid_argument("Can't rotate left since the right child is nil");

    Node* parent = nd->_parent;

    // understanding what case we are using in here
    // doing the painting immeadiately - it will not affect movement of nodes
    bool case3 = Child->isRightChild();

    if (parent)
    {
        if (parent->_right == nd)
            parent->_right = Child;
        else
            parent->_left = Child;
    }

    // setting parents of new nodes
    Child->_parent = parent;
    nd->_parent = Child;


    // setting children of moved nodes
    Node* leftChildOfN = Child->_left;
    Child->_left = nd;
    nd->_right = leftChildOfN;
        // not forgetting to reassign parent of leftChildOfN
        if (leftChildOfN)
            leftChildOfN->_parent = nd;

    // we need to check if root of tree was moved
    // root is pointing to the former top node - it was nd
    // so if root == nd -> we move it to nd->rightChild
    if (_root == nd)
        _root = Child;

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_LROT, this, nd);
}


/** \brief Вращает поддерево относительно узла \c nd вправо. Условия и ограничения
  * аналогичны (симметрично) левому вращению.
  *
  *  <b style='color:orange'>Для реализации студентами.</b>
  */
template <typename Element, typename Compar>
void RBTree<Element, Compar>::rotRight(typename RBTree<Element, Compar>::Node* nd)
{
    /* I dont know why i wrote comments in russian
    * Этот метод ПЕРЕТАСКИВАЕТ условно выполняет поворот
    * LEFT-CASE 2 или RIGHT-CASE 3
    * -----------------------------
    * Перекраска осуществляется в зависимости от текущего case'а
    *
    * nd - папа P вершины N
    * nd->left - потомок-вершина N
    * nd->parent - дедушка G вершины N
    */

    Node* Child = nd->_left;
    // immediately checking on exception
    if (!Child)
        throw std::invalid_argument("Can't rotate left since the right child is nil");

    Node* parent = nd->_parent;

    // understanding what case we are using in here
    // doing the painting immeadiately - it will not affect movement of nodes
    bool case2 = Child->isRightChild();

    if (parent)
    {
        if (parent->_right == nd)
            parent->_right = Child;
        else
            parent->_left = Child;
    }

    // setting parents of new nodes
    Child->_parent = parent;
    nd->_parent = Child;

    // setting children of moved nodes
    Node* rightChildOfN = Child->_right;
    Child->_right = nd;
    nd->_left = rightChildOfN;
    // not forgetting to reassign parent of leftChildOfN
    if (rightChildOfN)
        rightChildOfN->_parent = nd;

    // we need to check if root of tree was moved
    // root is pointing to the former top node - it was nd
    // so if root == nd -> we move it to nd->rightChild
    if (_root == nd)
        _root = Child;

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RROT, this, nd);
}



} // namespace xi