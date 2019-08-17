#include  "hashset.h"

using namespace std;

template<class key_type, class hash_func, class key_equal>
const int HashSet<key_type,hash_func,key_equal>::num_primes = 25;


template<class key_type, class hash_func, class key_equal>
const unsigned long HashSet<key_type,hash_func,key_equal>::prime_list[] = 
        {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
         196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
         50331653, 100663319, 201326611, 402653189, 805306457};


template<class key_type, class hash_func, class key_equal>
bool HashSet<key_type,hash_func,key_equal>::search(const key_type& k)
{
    // tmp to get size
    unsigned long tmpSize = this->table_size();
    unsigned long p = hf(k) % tmpSize;
    unsigned long firstValue = p;

    // going only through USED values
    while (!(*ht)[p].used || !eq((*ht)[p].key, k)) {
        //cout << (*ht)[p].key << endl;
        // not forgetting to take MODULAR value
        p = (p+1) % tmpSize;

        // we have found first value from which we were searching
        // so returning false
        if (p == firstValue)
            return false;
    }

    return true;
}

template<class key_type, class hash_func, class key_equal>
void HashSet<key_type,hash_func,key_equal>::remove(const key_type& key)
{
    // tmp to get size
    unsigned long tmpSize = this->table_size();
    // we take a modular value
    unsigned long index = hf(key) % tmpSize;
    // remember the first index
    unsigned long firstValue = index;
    // trying to find out is there a value in [index]
    Entry tmp = (*ht)[index];

    // while values are not the same
    while (!tmp.used || !eq(tmp.key, key)) //tmp.key != key)
    {
        index = (index+1) % tmpSize;

        if (index == firstValue)
            throw std::invalid_argument("Nothing found");

        tmp = (*ht)[index];
    }

    // deleting by just remaking @used@ field
    tmp.used = false;
    (*ht)[index] = tmp;
    // it is updating - checked
    //Entry tmp1 = (*ht)[index];

    // not forgeting to update number of entries
    this->entries--;
}


template<class key_type, class hash_func, class key_equal>
void HashSet<key_type,hash_func,key_equal>::insert(const key_type& key)
{

    if (load_factor() > .7) {
        resize();
    }

    // tmp to get size
    unsigned long tmpSize = this->table_size();
    // we take a modular value
    unsigned long index = hf(key) % tmpSize;
    // trying to find out is there a value in [index]
    Entry tmp = (*ht)[index];

    // while place is already used - going forward to find it
    while (tmp.used)
    {
        index = (index+1) % tmpSize;
        tmp = (*ht)[index];
    }

    // found a place to store
    // inserting
    tmp.key = key;
    tmp.used = true;
    (*ht)[index] = tmp;
    // it is updating - checked
    //Entry tmp1 = (*ht)[index];

    // not forgeting to update number of entries
    this->entries++;
}

template<class key_type, class hash_func, class key_equal>
int HashSet<key_type,hash_func,key_equal>::resize() {

    if (prime == num_primes - 1) {
        cerr << "maximal table size reached, aborting ... " << endl;
        exit(2);
    }

    unsigned long mm = prime_list[prime];
    prime++;
    unsigned long m = prime_list[prime];
    vector<Entry>* ptr = new vector<Entry>(m);

    // swapping values - so in ht there is NEW VECTOR without any used Entries
    // and in ptr there is former ht with used values
    vector<Entry>* formerVector = ht;
    ht = ptr;
    ptr = formerVector;

    Entry tmp;
    // now in ptr there is new vector<Entry>* without any values
    // we have to put them in new vector down here
    for (unsigned long i = 0; i < ptr->size(); ++i)
    {
        tmp = (*ptr)[i];
        if (tmp.used)
            insert(tmp.key);
    }

    // and reassign former vector to new one
    //ht = ptr;

    return 0;
}
