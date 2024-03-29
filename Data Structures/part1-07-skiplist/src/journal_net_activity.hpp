////////////////////////////////////////////////////////////////////////////////
// Module Name:  journal_net_activity.h/hpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      2.0.0
// Date:         28.10.2018
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

// !!! DO NOT include journal_net_activity.h here, 'cause it leads to circular refs. !!!

#include <fstream>

//==============================================================================
// class JournalNetActivity
//==============================================================================

template <int numLevels>
void JournalNetActivity<numLevels>::parseLog(const std::string& fullpath)
{
    // пытаемся открыть файл для чтения
    std::ifstream fin(fullpath);    // opens the file
    if (!fin)
        throw std::logic_error("Couldn't open file " + fullpath);
    
    parseLogFromStream(fin);
}

template <int numLevels>
void JournalNetActivity<numLevels>::parseLogFromStream(std::istream& in)
{
    TimeStamp timestamp;            // dummy
    NetActivity netactivity;        // dummy

    while (in)
    {
        in >> timestamp;
        if (!in)
            break;

        in >> netactivity.user;
        if (!in)
            break;

        in >> netactivity.host;
        if (!in)
            break;

        _journal.insert(netactivity, timestamp);
    }
}

//------------------------------------------------------------------------------

/// Just dumps the whole journal to the \a out stream.
template <int numLevels>
void JournalNetActivity<numLevels>::dumpJournal(std::ostream& out)
{
    typename NetActivityList::Node* prehead = _journal.getPreHead();
    typename NetActivityList::Node* run = prehead;

    // prehead is placed before the first and after the last element
    // So it serves two roles.
    while (run->next != prehead)
    {
        run = run->next;
        out << run->key;
        out << " ";
        out << run->value;
    }
}

//------------------------------------------------------------------------------

    /// Outputs all net activity between \a from and \a to (including borders).
    /// Uses given ostream for output!!!
    ///
    /// If `from` > `to` throws std::invalid_argument
    ///
    /// Output format should be like this: (one space between key and value)
    /// 2015.07.10 10:33:02 user126 e-maxx.ru
    /// 2015.07.10 10:34:02 user127 e-maxx.ru
    ///
    /// The last line should end with a new line.
    /// Line separator should be std::endl.
    /// Empty output is "" without new line.
    ///
    /// Net Activities with equal TimeStamps should go in the same order as they were in the journal.
    template <int numLevels>
    void JournalNetActivity<numLevels>::outputSuspiciousActivities(
            const std::string& hostSuspicious,
            const TimeStamp& timeFrom,
            const TimeStamp& timeTo,
            std::ostream& out) const
    {
        // first option in method
        if (timeFrom > timeTo)
            throw std::invalid_argument("Wrong times are passed.");

        /* We have to use findLastLessThan
         * if we use findFirst we will not get the SAME key node (maybe)
         * So using firstBefore->next to search
         */
        typename SkipList<NetActivity, TimeStamp, numLevels>::Node* firstBefore = _journal.findLastLessThan(timeFrom);

        // nothin found
        if (firstBefore == nullptr)
            return;

        while (firstBefore->next != _journal.getPreHead() // if found last in chain
                && firstBefore->next->key <= timeTo)    // if key is okay
        {
            if (firstBefore->next->value.host == hostSuspicious) // if verisicret!
            {
                out << firstBefore->next->key << " ";   // output
                out << firstBefore->next->value << std::endl;   // output
            }

            firstBefore = firstBefore->next; // -->>
        }
    }