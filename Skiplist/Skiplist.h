

#include <cstdlib>
#include <utility>
#include <fstream>
#include <iostream>

const int MAXLEVEL = 16;

class skiplist_node {

public:

    explicit skiplist_node(int searchKey);
    explicit skiplist_node(std::pair<int,int>newdata);
    ~skiplist_node() {};

    std::pair<int,int>data;
    skiplist_node* forwards[MAXLEVEL+1];

};



class skiplist {

public:

    skiplist( int minKey, int maxKey );
    ~skiplist();

    void Add(std::pair<int, int>newdata);
    bool Remove(int searchKey);
    bool Has(int searchKey);
    int Max();
    int Min();
    void printList(std::ostream &outputstream);

    const int max_level;

protected:

    double uniformRandom() { return rand() / double(RAND_MAX); }

    int randomLevel();
    int m_minKey;
    int m_maxKey;
    int max_curr_level;
    skiplist_node* m_pHeader;
    skiplist_node* m_pTail;
};
