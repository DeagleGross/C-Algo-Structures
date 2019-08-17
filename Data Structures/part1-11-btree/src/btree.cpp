////////////////////////////////////////////////////////////////////////////////
// Module Name:  btree.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.1.0
// Date:         01.05.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "btree.h"

#include <stdexcept>        // std::invalid_argument
#include <cstring>          // memset
#include <iostream>


namespace xi {


//==============================================================================
// class BaseBTree
//==============================================================================



bool BaseBTree::Header::checkIntegrity()
{
    return (sign == VALID_SIGN) && (order >= 1) && (recSize > 0);
}



BaseBTree::BaseBTree(UShort order, UShort recSize, IComparator* comparator, std::iostream* stream)
    : _order(order), 
    _recSize(recSize), 
    _comparator(comparator),
    _stream(stream), 
    _lastPageNum(0),
    _rootPageNum(0)
    , _rootPage(this)
{
}


BaseBTree::BaseBTree(IComparator* comparator, std::iostream* stream):
    BaseBTree(
        0,      // порядок, 0 — д.б. прочитан из файла!
        0,      // размер ключа, 0 —  --//--
        comparator, stream)
{

}

BaseBTree::~BaseBTree()
{
}


void BaseBTree::resetBTree()
{
    _order = 0;
    _recSize = 0;
    _stream = nullptr;
    _comparator = nullptr;      // для порядку его тоже сбасываем, но это не очень обязательно
}




void BaseBTree::readPage(UInt pnum, Byte* dst)
{    
    checkForOpenStream();
    if (pnum == 0 || pnum > getLastPageNum())
        throw std::invalid_argument("Can't read a non-existing page");

    readPageInternal(pnum, dst);
}


void BaseBTree::writePage(UInt pnum, const Byte* dst)
{
    checkForOpenStream();

    if (pnum == 0 || pnum > getLastPageNum())
        throw std::invalid_argument("Can't write a non-existing page");

    writePageInternal(pnum, dst);

}


bool BaseBTree::checkKeysNumber(UShort keysNum, bool isRoot)
{
    if (keysNum > getMaxKeys())
        return false;                       // превышение по максимуму

    // NOTE: для корня пока даже 0 допустим, потом уточним, надо ли до 1 сокращать
    if (isRoot)
    //if (nt == nRoot)
        return true;

    return (keysNum >= getMinKeys());        
}


void BaseBTree::checkKeysNumberExc(UShort keysNum, bool isRoot)
{
    if (!checkKeysNumber(keysNum,  isRoot))
        throw std::invalid_argument("Invalid number of keys for a node");
}


UInt BaseBTree::allocPage(PageWrapper& pw, UShort keysNum, bool isLeaf /*= false*/)
{
    checkForOpenStream();
    checkKeysNumberExc(keysNum, pw.isRoot());  // nt);

    return allocPageInternal(pw, keysNum, pw.isRoot(),  isLeaf);
}


xi::UInt BaseBTree::allocNewRootPage(PageWrapper& pw)
{
    checkForOpenStream();
    return allocPageInternal(pw, 0, true, false);
}



/** \brief Для заданного ключа \c k ищет первое его вхождение в дерево по принципу эквивалентности.
 *  Если ключ найден, возвращает указатель на подлежащий массив, иначе nullptr.
 */
Byte* BaseBTree::search(const Byte* toInsert)
{
    UInt rightRootPageNumer = _rootPage.getPageNum();

    UShort recordSize = this->_recSize;
    bool _searching = true;
    PageWrapper* _parent = &_rootPage;

    Byte* result = nullptr;

    while (_searching)
    {
        // here we have to search page to go below
        for (UShort i = 0; i < _parent->getKeysNum()+1; ++i)
        {
            Byte* currBytes = _parent->getKey(i);

            // going away if found
            if (currBytes && _comparator->isEqual(toInsert, currBytes, recordSize))
            {
                result = new Byte(*currBytes); //new Byte(currBytes);
                _searching = false;
                break;
            }


            // going to bot if not found
            if (!currBytes || _comparator->compare(toInsert, currBytes, recordSize) || i == _parent->getKeysNum())
            {
                // if we go bot but it is just the end - nullptr
                if (_parent->isLeaf())
                {
                    _searching = false;
                    break;
                }

                _parent->readPageFromChild(*_parent, i);
                break;
            }
        }
    }

    _rootPage.readPage(rightRootPageNumer);
    return result;
}

/** ADDED BY MYSELF - дополнительная функция для рекурсивного поиска
 * \brief Для заданного ключа \c k ищет все его его вхождения в дерево по принципу эквивалентности.
 *  Каждый найденный ключ добавляется в переданный список ключей \c keys.
 *  Также в параметре передается ссылка на страницу - с нее начинается поиск
 *  \returns число найденных элементов
 */
int BaseBTree::searchAllFromPosition(BaseBTree::PageWrapper *p, const Byte *toInsert, std::list<Byte *> &keys)
{
    // POSITION SEARCH ALL

    UShort recordSize = this->_recSize;
    bool _searching = true;
    PageWrapper* _parent = p;
    PageWrapper _child(this);
    UInt parNum;

    int result = 0;

    while (_searching)
    {
        // here we have to search page to go below
        for (UShort i = 0; i < _parent->getKeysNum()+1; ++i)
        {
            Byte* currBytes = _parent->getKey(i);

            // going away if found
            if (currBytes && _comparator->isEqual(toInsert, currBytes, recordSize))
            {
                keys.push_back(new Byte(*currBytes)); //new Byte(currBytes);
                result++;

                parNum = _parent->getPageNum();
                // found - we need to address to left child from here
                if (!_parent->isLeaf())
                {
                    _child.readPageFromChild(*_parent, i);
                    result += searchAllFromPosition(&_child, toInsert, keys);
                }

                _parent->readPage(parNum);

                // and we dont break - we can find value to right also
                continue;
                // _searching = false;
                // break;
            }


            // going to bot if not found
            if (!currBytes || _comparator->compare(toInsert, currBytes, recordSize) || i == _parent->getKeysNum())
            {
                // if we go bot but it is just the end - nullptr
                if (_parent->isLeaf())
                {
                    _searching = false;
                    break;
                }

                _parent->readPageFromChild(*_parent, i);
                break;
            }
        }
    }

    return result;
}

/** \brief Для заданного ключа \c k ищет все его его вхождения в дерево по принципу эквивалентности.
 *  Каждый найденный ключ добавляется в переданный список ключей \c keys.
 *
 *  \returns число найденных элементов
 */
int BaseBTree::searchAll(const Byte* toInsert, std::list<Byte*>& keys)
{
    // TODO SEARCH ALL

    UInt rightRootPageNumer = _rootPage.getPageNum();

    UShort recordSize = this->_recSize;
    bool _searching = true;
    PageWrapper* _parent = &_rootPage;
    PageWrapper _child(this);
    UInt parNum;

    int result = 0;

    while (_searching)
    {
        // here we have to search page to go below
        for (UShort i = 0; i < _parent->getKeysNum()+1; ++i)
        {
            Byte* currBytes = _parent->getKey(i);

            // going away if found
            if (currBytes && _comparator->isEqual(toInsert, currBytes, recordSize))
            {
                keys.push_back(new Byte(*currBytes));//new Byte(currBytes);
                result++;

                parNum = _parent->getPageNum();

                // found - we need to address to left child from here
                if (!_parent->isLeaf())
                {
                    _child.readPageFromChild(*_parent, i);
                    result += searchAllFromPosition(&_child, toInsert, keys);
                }

                _parent->readPage(parNum);

                // and we dont break - we can find value to right also
                continue;
                // _searching = false;
                // break;
            }

//            if (!currBytes && _comparator->isEqual(toInsert, currBytes, recordSize))
//            {
//                if (!_parent->isLeaf())
//                {
//                    _child.readPageFromChild(*_parent, i);
//                    result += searchAllFromPosition(&_child, toInsert, keys);
//                }
//            }

            // going to bot if not found
            if (!currBytes || _comparator->compare(toInsert, currBytes, recordSize) || i == _parent->getKeysNum())
            {
                // if we go bot but it is just the end - nullptr
                if (_parent->isLeaf())
                {
                    _searching = false;
                    break;
                }

                _parent->readPageFromChild(*_parent, i);
                break;
            }
        }
    }

    _rootPage.readPage(rightRootPageNumer);
    return result;
}

//UInt BaseBTree::allocPageInternal(UShort keysNum, NodeType nt, PageWrapper& pw)
UInt BaseBTree::allocPageInternal(PageWrapper& pw, UShort keysNum, bool isRoot, bool isLeaf)
{
    // подготовим страничку для вывода
    pw.clear();
    pw.setKeyNumLeaf(keysNum, isRoot, isLeaf);    // nt);

    // пока что просто позиционируемся в конец, считая, что так и будет, но держать под контролем
    _stream->seekg(0, std::ios_base::end);    
    _stream->write((const char*)pw.getData(), getNodePageSize());

    ++_lastPageNum;
    writePageCounter();


    //  flush-им на диск сразу?!
    //_stream->flush();

    return _lastPageNum;
}



void BaseBTree::readPageInternal(UInt pnum, Byte* dst)
{
    // позиционируемся и читаем
    gotoPage(pnum);
    _stream->read((char*)dst, getNodePageSize());
}


void BaseBTree::writePageInternal(UInt pnum, const Byte* dst)
{
    // позиционируемся и пишем
    gotoPage(pnum);
    _stream->write((const char*)dst, getNodePageSize());
}


void BaseBTree::gotoPage(UInt pnum)
{
    // рассчитаем смещение до нужной страницы
    UInt pageOfs = FIRST_PAGE_OFS + getNodePageSize() * (pnum - 1);     // т.к. нумеруются с единицы
    _stream->seekg(pageOfs, std::ios_base::beg);
}


void BaseBTree::loadTree()
{
    // _stream->seekg(0, std::ios_base::beg);       // пока загружаем с текущего места в потоке!
    // читаем заголовок
    
    Header hdr;
    readHeader(hdr);

    // если при чтении случилась пичалька
    if (_stream->fail())
    {
        //_stream->close();
        throw std::runtime_error("Can't read header");
    }

    // проверяет заголовок на корректность
    if (!hdr.checkIntegrity())
    {
        //_stream->close();
        throw std::runtime_error("Stream is not a valid xi B-tree file");
    }

    // задаем порядок и т.д.
    setOrder(hdr.order, hdr.recSize);

    // далее без проверки читаем два следующих поля
    readPageCounter();             // номер текущей свободной страницы
    readRootPageNum();             // номер корневой страницы

    // если при чтении случилась пичалька
    if (_stream->fail())
    {
        //_fileStream.close();
        throw std::runtime_error("Can't read necessary fields. File corrupted");
    }

    // загрузить корневую страницу
    loadRootPage();

}


void BaseBTree::loadRootPage()  //PageWrapper& pw)
{
    if (getRootPageNum() == 0)
        throw std::runtime_error("Root page is not defined");

    _rootPage.readPage(getRootPageNum());
    _rootPage.setAsRoot(false);               // в файл номер страницы не пишем, т.к. только что прочитали оттуда его

}


void BaseBTree::createTree(UShort order, UShort recSize)
{
    setOrder(order, recSize);

    writeHeader();                  // записываем заголовок файла
    writePageCounter();             // и номер текущей свободной страницы
    writeRootPageNum();             // и номер корневой страницы


    // создать корневую страницу
    createRootPage();
}


void BaseBTree::createRootPage()
{
    _rootPage.allocPage(0, true);
    _rootPage.setAsRoot();
}


void BaseBTree::checkForOpenStream()
{
    if (!isOpen())
        throw std::runtime_error("Stream is not ready");

}


void BaseBTree::writeHeader()
{    
    Header hdr(_order, _recSize);    
    _stream->write((const char*)(void*)&hdr, HEADER_SIZE);

}

void BaseBTree::readHeader(Header& hdr)
{
    _stream->seekg(HEADER_OFS, std::ios_base::beg);
    _stream->read((char*)&hdr, HEADER_SIZE);

}



void BaseBTree::writePageCounter() //UInt pc)
{
    _stream->seekg(PAGE_COUNTER_OFS, std::ios_base::beg);
    _stream->write((const char*)&_lastPageNum, PAGE_COUNTER_SZ);
}



//xi::UInt 
void BaseBTree::readPageCounter()
{
    _stream->seekg(PAGE_COUNTER_OFS, std::ios_base::beg);    
    _stream->read((char*)&_lastPageNum, PAGE_COUNTER_SZ);
}



void BaseBTree::writeRootPageNum() //UInt rpn)
{
    _stream->seekg(ROOT_PAGE_NUM_OFS, std::ios_base::beg);
    _stream->write((const char*)&_rootPageNum, ROOT_PAGE_NUM_SZ);

}



//xi::UInt 
void BaseBTree::readRootPageNum()
{
    _stream->seekg(ROOT_PAGE_NUM_OFS, std::ios_base::beg);
    _stream->read((char*)&_rootPageNum, ROOT_PAGE_NUM_SZ);
}



void BaseBTree::setRootPageNum(UInt pnum, bool writeFlag /*= true*/)
{
    _rootPageNum = pnum;
    if (writeFlag)
        writeRootPageNum();
}



void BaseBTree::setOrder(UShort order, UShort recSize)
{
    // метод закрытый, корректность параметров должно проверять в вызывающих методах

    _order = order;
    _recSize = recSize;

    _minKeys = order - 1;
    _maxKeys = 2 * order - 1;

    // проверим максимальное число ключей
    if (_maxKeys > MAX_KEYS_NUM)
        throw std::invalid_argument("For a given B-tree order, there is an excess of the maximum number of keys");

    _keysSize = _recSize * _maxKeys;                // область памяти под ключи
    _cursorsOfs = _keysSize + KEYS_OFS;             // смещение области курсоров на дочерние
    _nodePageSize = _cursorsOfs + CURSOR_SZ * (2 * order);  // размер узла целиком, опр. концом области страницы

    // Q: номер текущей корневой надо устанавливать?

    // пока-что распределяем память под рабочую страницу/узел здесь, но это сомнительно
    reallocWorkPages();
}


void BaseBTree::reallocWorkPages()
{
    _rootPage.reallocData(_nodePageSize);
}


/** \brief Вставляет в дерево ключ k с учетом порядка.
 *
 */
void BaseBTree::insert(const Byte *toInsert)
{
    // MAIN INSERT

    // we have to split root page if it is full
    if (_rootPage.isFull())
    {
        /* ASKED IN SLACK HOW TO DO IT
         * SHERSHAKOV EXPLANATION (russian comments)
         */

        PageWrapper _formerRoot(this);
        UInt _formerNum = _rootPage.getPageNum();

        // 1) Создаю wrapper Для нового рута !!! что за "флаг корневой страницы"? !!!
        PageWrapper newRoot(this);
        // 2) аллоцирую новую страницу через wrapper!
        newRoot.allocNewRootPage();
        // 3) задаю левый потомок в старый корень
        newRoot.setCursor(0, _formerNum);
        // 4) записываю новую страниц на диск
        newRoot.writePage();
        // 5) получаю ее номер геттером wрепеpa
        UInt numOfNewRoot = newRoot.getPageNum();
        // 6) записываю новым номером корневой страницы этот номер
        _rootPage.readPage(numOfNewRoot);
        // 7) перезагружаю корневую страницу с диска
        _formerRoot.readPage(_formerNum);
        // split! :)
        _rootPage.splitChild(0);
    }

    // simply if root is only page and it is not full
    if (_rootPage.isLeaf() && !_rootPage.isFull())
    {
        _rootPage.insertNonFull(toInsert);
        return;
    }

    // if root is not leaf we go below and do smth
    //_rootPage.writePage();
    UInt rightRootPageNumer = _rootPage.getPageNum();

    UShort recordSize = this->_recSize;
    bool _searching = true;
    PageWrapper* _parent = &_rootPage;
//    PageWrapper _parent(this);
//    _parent.readPage(_rootPage.getPageNum());
    PageWrapper _child(this);
//    PageWrapper* _child;

    while (_searching)
    {
        // here we have to search page to go below
        for (UShort i = 0; i < _parent->getKeysNum()+1; ++i)
        {
            Byte* currBytes = _parent->getKey(i);
            if (i == _parent->getKeysNum()
                || _comparator->compare(toInsert, currBytes, recordSize)
                || _comparator->isEqual(toInsert, currBytes, recordSize))
            {
                //_child->readPageFromChild(*_parent, _parent->getCursor(i));
                _child.readPageFromChild(*_parent, i);

                // child is full -> we don't even care it is leaf or not
                // we just split it and check the same cursor but from another value of element
                if (_child.isFull())
                {
                    _parent->splitChild(i);
                    // checking the same position cursor again but with
                    i--;
                    continue;
                }
                else
                {
                    // HERE CODE FOR NOT FULL CHILD
                    // very easy if it is leaf & not Full -> just do insertNonFull
                    if (_child.isLeaf())
                    {
                        _child.insertNonFull(toInsert);
                        _searching = false;
                        break;
                    }
                    else // here it is not leaf and not full - we just go down and nothing more
                    {
//                         _parent = &_child;
                        _parent->readPage(_child.getPageNum());
                        break; // and doin search again from parent
                    }
                }
            }
        }
    }

    // SUPER IMPORTANT - we can miss rootChange when _parent->readPage(child->num)
    // in the loop
    // so we reforce root to right statement - that is working!
    _rootPage.readPage(rightRootPageNumer);
    return;
}


//==============================================================================
// class BaseBTree::PageWrapper
//==============================================================================



BaseBTree::PageWrapper::PageWrapper(BaseBTree* tr) :
    _data(nullptr)
    , _tree(tr)
    , _pageNum(0)
{
    // если к моменту создания странички дерево уже в работе (открыто), надо
    // сразу распределить память!
    if (_tree->isOpen())
        reallocData(_tree->getNodePageSize());

}


BaseBTree::PageWrapper::~PageWrapper()
{
    reallocData(0);
}


void BaseBTree::PageWrapper::reallocData(UInt sz)
{
    if (_data)
        delete[] _data;

    if (sz)
        _data = new Byte[sz];
        
}

void BaseBTree::PageWrapper::clear()
{
    if (!_data)
        return;

    // работая с сырыми блоками данных единственно и можно применять низкоуровневые C-функции
    memset(_data, 0, _tree->getNodePageSize());
}



void BaseBTree::PageWrapper::setKeyNumLeaf(UShort keysNum, bool isRoot, bool isLeaf) //NodeType nt)
{
    _tree->checkKeysNumberExc(keysNum, isRoot);

    // логически приплюсовываем
    if (isLeaf)
        keysNum |= LEAF_NODE_MASK; // 0x8000;

    // способ записи типизированного объекта, начиная с адреса [0]
    *((UShort*)&_data[0]) = keysNum;
}



void BaseBTree::PageWrapper::setKeyNum(UShort keysNum, bool isRoot) //NodeType nt)
{
    _tree->checkKeysNumberExc(keysNum, isRoot);


    UShort kldata = *((UShort*)&_data[0]);      // взяли сущ. значение
    kldata &= LEAF_NODE_MASK;                   // оставили от него только флаг "лист"
    kldata |= keysNum;                          // приилили число ключей (там точно не будет 1 в старшем)

    *((UShort*)&_data[0]) = kldata;             // записали
}



void BaseBTree::PageWrapper::setLeaf(bool isLeaf)
{
    UShort kldata = *((UShort*)&_data[0]);      // взяли сущ. значение
    kldata &= ~LEAF_NODE_MASK;                  // оставили от него только часть с числом ключей
    if (isLeaf)
        kldata |= LEAF_NODE_MASK;   // 0x8000;  // приилили флаг, если надо

    *((UShort*)&_data[0]) = kldata;             // записали
}



bool BaseBTree::PageWrapper::isLeaf() const
{
    UShort info = *((UShort*)&_data[0]);

    return (info & LEAF_NODE_MASK) != 0;
}

/** \brief Возвращает число ключей в ноде. */
UShort BaseBTree::PageWrapper::getKeysNum() const
{
    UShort info = *((UShort*)&_data[0]);

    return (info & ~LEAF_NODE_MASK);
}



Byte* BaseBTree::PageWrapper::getKey(UShort num)
{
    // рассчитываем смещение
    //UInt kofst = KEYS_OFS + _tree->getRecSize() * num;
    int kofst = getKeyOfs(num);
    if (kofst == -1)
        return nullptr;

    return (_data + kofst);
}


const Byte* BaseBTree::PageWrapper::getKey(UShort num) const
{
    int kofst = getKeyOfs(num);
    if (kofst == -1)
        return nullptr;

    return (_data + kofst);
}


void BaseBTree::PageWrapper::copyKey(Byte* dst, const Byte* src)
{
    memcpy(
        dst,                        // куда
        src,                        // откуда
        _tree->getRecSize());       // размер ключа
}

void BaseBTree::PageWrapper::copyKeys(Byte* dst, const Byte* src, UShort num)
{
    memcpy(
        dst,                        // куда
        src,                        // откуда
        _tree->getRecSize() * num   // размер: размер записи на число элементов
        );

}

void BaseBTree::PageWrapper::copyCursors(Byte* dst, const Byte* src, UShort num)
{
    memcpy(
        dst,                        // куда
        src,                        // откуда
        num * CURSOR_SZ             // размер
        );
}

UInt BaseBTree::PageWrapper::getCursor(UShort cnum)
{
    //if (cnum > getKeysNum())
    int curOfs = getCursorOfs(cnum);
    if (curOfs == -1)
        throw std::invalid_argument("Wrong cursor number");

    return *((const UInt*)(_data + curOfs));
}


Byte* BaseBTree::PageWrapper::getCursorPtr(UShort cnum)
{
    int curOfs = getCursorOfs(cnum);
    if (curOfs == -1)
        throw std::invalid_argument("Wrong cursor number");

    return (_data + curOfs);

}

void BaseBTree::PageWrapper::setCursor(UShort cnum, UInt cval)
{
    int curOfs = getCursorOfs(cnum);
    if (curOfs == -1)
        throw std::invalid_argument("Wrong cursor number");

    *((UInt*)(_data + curOfs)) = cval;
}


int BaseBTree::PageWrapper::getCursorOfs(UShort cnum) const
{
    if (cnum > getKeysNum())
        return -1;

    // рассчитываем смещением
    return _tree->getCursorsOfs() + CURSOR_SZ * cnum;
}

int BaseBTree::PageWrapper::getKeyOfs(UShort num) const
{
    if (num >= getKeysNum())
        return -1;

    // рассчитываем смещение
    return KEYS_OFS + _tree->getRecSize() * num;
}


void BaseBTree::PageWrapper::setAsRoot(bool writeFlag /*= true*/)
{
    _tree->_rootPageNum = _pageNum;         // ид корень по номеру страницы в памяти

    if (!writeFlag)
        return;

    // если же надо записать в файл сразу...
    if (_pageNum == 0)
        throw std::runtime_error("Can't set a page as root until allocate a page in a file");

    // если же под страницу есть номер, запишем его в файл
    _tree->setRootPageNum(_pageNum, true);
}



void BaseBTree::PageWrapper::readPageFromChild(PageWrapper& pw, UShort chNum)
{
    UInt cur = pw.getCursor(chNum);
    if (cur == 0)
        throw std::invalid_argument("Cursor does not point to a existing node/page");
    
    readPage(cur);
}


void BaseBTree::PageWrapper::writePage()
{
    if (getPageNum() == 0)
        throw std::runtime_error("Page number not set. Can't write");

    _tree->writePage(getPageNum(), _data);
}


/** \brief Для не полностью заполненного текущего узла разделяет напополам его
 *  полностью заполненного ребенка, определяемого курсором номер \c iChild на два нода/страницы.
 *
 *  Параметр \c iChild представляет индекс курсора, который не может быть 0, что означает
 *  нарушение целостности (нет страницы с таким ребенком).
 *  Т.к. в процессе сплита один из ключей ребенка уйдет в этот родительский нод,
 *  данный нод должен иметь хотя бы один свободный слот под этот ключ. Если это не так,
 *  полетит исключительная ситуация.
 *  Для того, чтобы не было неопределенности по поводу индексов, заполненности и проч.
 *  в соответствующем ребенке, подразумеваем, что он полностью заполнен. Если это не так,
 *  кидаем искл. ситуацию.
 */
void BaseBTree::PageWrapper::splitChild(UShort iChild)
{
    if (isFull())
        throw std::domain_error("A parent node is full, so its child can't be splitted");

    if (iChild > getKeysNum())
        throw std::invalid_argument("Cursor not exists");

    // creating new object to take half of child in it (left part)
    PageWrapper* currentChild = new PageWrapper(_tree);
    currentChild->readPageFromChild(*this, iChild);

    // mid pos + mid value
    UShort mid = currentChild->getKeysNum() / 2;
    Byte* midElement = currentChild->getKey(mid);

    /* As we know current child is full - we split it
     * if it is full -> it has odd amount of nodes (2*t-1)
     * it is indexed from 0 so last is even
     * ---> getKeysNum() / 2 gives exact middle element
     * so creating newAddedChild as a container for
     * haft of child (right part)
     */
    PageWrapper* newAddedChild = new PageWrapper(_tree);
    newAddedChild->allocPage(mid, true);
    newAddedChild->setKeyNum(mid);

    // here very important thing
    // we go through current child and we have to think is it leaf or not
    // we have to setup if current child and newAdded child is leaf
    // in other case insert will not work okay
    if (currentChild->isLeaf())
        newAddedChild->setLeaf(true);
    else
        newAddedChild->setLeaf(false);

    UShort k = 0;
    // Копируем в newAddedChild ключи начиная после центрального элемента из currentChild
    for(UShort i = mid + 1; i < currentChild->getKeysNum(); i++)
    {
        newAddedChild->copyKey(newAddedChild->getKey(k), currentChild->getKey(i));
        newAddedChild->copyCursors(newAddedChild->getCursorPtr(k),
                currentChild->getCursorPtr(i), CURSOR_SZ);
        k++;
    }

    // inserting element to this->page
    // and resetting currChild-keysNum
    insertNonFull(midElement);
    currentChild->setKeyNum(mid);

    // and we need to place mid->right cursor
    UShort mid_position;
    for(mid_position = 0; mid_position < getKeysNum(); mid_position++)
    {
        // Если ключ равен вставленому, то позиция найдена
        if(_tree->_comparator->isEqual(getKey(mid_position), midElement, _tree->getRecSize()))
            break;
    }

    // Устанавливаем значение правого курсора вставленной вершины на newAddedChild
    setCursor(mid_position + 1, newAddedChild->getPageNum());

    // JUST TO TEST
    writePage();
    currentChild->writePage();
    newAddedChild->writePage();
}

/** \brief Вставляет в не полностью заполненный узел ключ k с учетом порядка.
 *
 *  Если узел полный, кидает исключение.
 *  Если для дерева не задан компаратор, кидает исключение.
 */
void BaseBTree::PageWrapper::insertNonFull(const Byte* toInsert)
{
    if (isFull())
        throw std::domain_error("Node is full. Can't insert");

    IComparator* c = _tree->getComparator();
    if (!c)
       throw std::runtime_error("Comparator not set. Can't insert");

    // going from 0 - this node keys
    UShort current_i = 0;
    bool foundPlace = false;
    UShort recordSize = this->_tree->_recSize;

    // Finding place to put in
    for (UShort i = 0; i < getKeysNum(); i++)
    {
        // bytes of current getKey
        Byte* _curr = this->getKey(i);
        // compare do we need to stop here
        if (!c->compare(_curr,toInsert,recordSize))
        {
            current_i = i;
            foundPlace = true;
            break;
        }
        // if we put a big number we find out last checked was not 0, but now it is 0
        // so we insert value
        if (i>0 && *getKey(i-1) != 0 && *_curr == 0)
        {
            current_i = i;
            foundPlace = true;
            break;
        }
    }

    // have to make more keysNum
    if (!foundPlace || *(this->getKey(this->getKeysNum()-1)) != 0)
    {
        if (!foundPlace)
            current_i = getKeysNum();
        this->setKeyNum(this->getKeysNum()+1);
    }

    // copy after placement elements
    UShort lastElement = this->getKeysNum()-1;
    while (lastElement > current_i)
    {
        Byte* a = getKey(lastElement-1);
        Byte* b = getKey(lastElement);
        this->copyKey(b, a);
        lastElement--;
    }

    // also we need to move all cursors to right on 1 position
    // element is putted in X
    // so we move X->RightCursor to X+1->LeftCursor and etc
    UShort lastElPos = getKeysNum() - 1;
    if(this->getKeysNum()-1 > current_i)
        copyCursors(getCursorPtr(current_i + 2), getCursorPtr(current_i + 1), CURSOR_SZ);
    // cursor of putted node doesnt point to anything -> we place 0 here
    setCursor(current_i + 1, 0);

    // inserting the value in the very end of method
    this->copyKey(getKey(current_i), toInsert);

    // FOR TESTING
    this->writePage();
}


//==============================================================================
// class FileBaseBTree
//==============================================================================

FileBaseBTree::FileBaseBTree()
    : BaseBTree(0, 0, nullptr, nullptr)
{
}

/** \brief Конструирует новое B-дерево со структурой, определяемой переданными параметрами.
     *
     *  Создает новое дерево и записывает его в файл \c fileName. Если файл существует,
     *  он перезаписывается. Если файл не может быть открыт, генерируется исключительная ситуация.
     *
     *  Конструктор эквивалентен созданию объекта с параметрами по умолчанию с последующим
     *  открытием методом open().
     */
FileBaseBTree::FileBaseBTree(UShort order, UShort recSize, IComparator* comparator, 
    const std::string& fileName)
    : FileBaseBTree()
{
    _comparator = comparator;

    checkTreeParams(order, recSize);
    createInternal(order, recSize, fileName);
}


FileBaseBTree::FileBaseBTree(const std::string& fileName, IComparator* comparator)
    : FileBaseBTree()
{
    _comparator = comparator;
    loadInternal(fileName); // , comparator);
}

FileBaseBTree::~FileBaseBTree()
{
    close();            // именно для удобства такого использования не кидаем внутри искл. ситуацию!
}



void FileBaseBTree::create(UShort order, UShort recSize, //IComparator* comparator,
    const std::string& fileName)
{
    if (isOpen())
        throw std::runtime_error("B-tree file is already open");

    checkTreeParams(order, recSize);
    createInternal(order, recSize, fileName);
}


void FileBaseBTree::createInternal(UShort order, UShort recSize, // IComparator* comparator,
    const std::string& fileName)
{
    _fileStream.open(fileName, 
        std::fstream::in | std::fstream::out |      // чтение запись
        std::fstream::trunc |                       // обязательно грохнуть имеющееся (если вдруг) содержимое
        std::fstream::binary);                      // бинарничек

    // если открыть не удалось
    if (_fileStream.fail())
    {
        // пытаемся закрыть и уходим
        _fileStream.close();
        throw std::runtime_error("Can't open file for writing");
    }

    // если же все ок, сохраняем параметры и двигаемся дальше
    //_comparator = comparator;
    _fileName = fileName;
    _stream = &_fileStream;                         // привязываем к потоку

    createTree(order, recSize);                     // в базовом дереве
}


void FileBaseBTree::open(const std::string& fileName) //, IComparator* comparator)
{
    if (isOpen())
        throw std::runtime_error("B-tree file is already open");

    loadInternal(fileName); // , comparator);
}


void FileBaseBTree::loadInternal(const std::string& fileName) // , IComparator* comparator)
{
    _fileStream.open(fileName,
        std::fstream::in | std::fstream::out |      // чтение запись
                                                    //  здесь не должно быть trunc, чтобы сущ. не убить
        std::fstream::binary);                      // бинарничек

    // если открыть не удалось
    if (_fileStream.fail())
    {
        // пытаемся закрыть и уходим
        _fileStream.close();
        throw std::runtime_error("Can't open file for reading");
    }

    // если же все ок, сохраняем параметры и двигаемся дальше
    //_comparator = comparator;
    _fileName = fileName;
    _stream = &_fileStream;         // привязываем к потоку


    try {
        loadTree();
    }
    catch (std::exception& e)
    {
        _fileStream.close();
        throw e;
    }
    catch (...)                     // для левых исключений
    {
        _fileStream.close();
        throw std::runtime_error("Error when loading btree");
    }
}


void FileBaseBTree::close()
{
    if (!isOpen())
        return;

    closeInternal();
}


void FileBaseBTree::closeInternal()
{
    // NOTE: возможно, перед закрытием надо что-то записать в файл? — иметь в виду!
    _fileStream.close();

    // переводим объект в состояние сконструированного БЕЗ параметров
    resetBTree();
}

void FileBaseBTree::checkTreeParams(UShort order, UShort recSize)
{
    if (order < 1 || recSize == 0)
        throw std::invalid_argument("B-tree order can't be less than 1 and record siaze can't be 0");

}

bool FileBaseBTree::isOpen() const
{
    return (_fileStream.is_open()); // && _fileStream.good());
}




} // namespace xi

