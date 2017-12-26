#include "SkipList.h"//



skiplist_node::skiplist_node(int searchKey) {

    data.first=searchKey;

    for ( int i=1; i<=MAXLEVEL; i++ ) { forwards[i] = nullptr; }

}


skiplist_node::skiplist_node(std::pair<int,int>newdata):data(newdata) {

    for ( int i=1; i<=MAXLEVEL; i++ ) { forwards[i] = nullptr; }

}

skiplist::skiplist( int minKey, int maxKey):m_pHeader(nullptr),m_pTail(nullptr),
                                  max_curr_level(1),max_level(MAXLEVEL),
                                  m_minKey(minKey),m_maxKey(maxKey) {

    m_pHeader = new skiplist_node(m_minKey);
    m_pTail = new skiplist_node(m_maxKey);

    for ( int i=1; i<=MAXLEVEL; i++ ) { m_pHeader->forwards[i] = m_pTail; }

}

virtual skiplist::~skiplist() {

    skiplist_node* currNode = m_pHeader->forwards[1];

    while ( currNode != m_pTail ) {

        skiplist_node* tempNode = currNode;
        currNode = currNode->forwards[1];

        delete tempNode;
    }

    delete m_pHeader;

    delete m_pTail;
}

void skiplist::Add(std::pair<int, int> newdata) {

    skiplist_node* update[MAXLEVEL];
    skiplist_node* currNode = m_pHeader;

    for(int level=max_curr_level; level >=1; level--) {

        while ( currNode->forwards[level]->data.first < newdata.first ) { currNode = currNode->forwards[level]; }

        update[level] = currNode;

    }

    currNode = currNode->forwards[1];

    if ( currNode->data.first == newdata.first ) { currNode->data.second = newdata.second; }

    else {

        int newlevel = randomLevel();

        if ( newlevel > max_curr_level ) {

            for ( int level = max_curr_level+1; level <= newlevel; level++ ) { update[level] = m_pHeader; }

            max_curr_level = newlevel;

        }

        currNode = new skiplist_node(newdata);

        for ( int lv=1; lv<=max_curr_level; lv++ ) {

            currNode->forwards[lv] = update[lv]->forwards[lv];
            update[lv]->forwards[lv] = currNode;

        }
    }
}


bool skiplist::Remove(int searchKey) {

    if (!Has(searchKey)){ return false; }

    skiplist_node* update[MAXLEVEL];
    skiplist_node* currNode = m_pHeader;

    for(int level=max_curr_level; level >=1; level--) {

        while ( currNode->forwards[level]->data.first < searchKey ) { currNode = currNode->forwards[level]; }

        update[level] = currNode;

    }

    currNode = currNode->forwards[1];

    if ( currNode->data.first == searchKey ) {

        for ( int lv = 1; lv <= max_curr_level; lv++ ) {

            if ( update[lv]->forwards[lv] != currNode ) { break; }

            update[lv]->forwards[lv] = currNode->forwards[lv];

        }

        delete currNode;


        while ( max_curr_level > 1 && m_pHeader->forwards[max_curr_level] == nullptr ) { max_curr_level--; }

    }

    return true;
}


bool skiplist::Has(int searchKey) {

    skiplist_node* currNode = m_pHeader;

    for(int level=max_curr_level; level >=1; level--) {

        while ( currNode->forwards[level]->data.first < searchKey ) { currNode = currNode->forwards[level]; }

    }

    currNode = currNode->forwards[1];

    return currNode->data.first == searchKey;

}


int skiplist::randomLevel() {

    int level = 1;
    double p = 0.5;

    while ( uniformRandom() < p && level < MAXLEVEL ) { level++; }

    return level;

}

void skiplist::printList(std::ostream &outputstream) {

    skiplist_node* currNode = m_pHeader->forwards[1];

    while ( currNode != m_pTail ) {

        outputstream << currNode->data.second << " " << std::endl;
        currNode = currNode->forwards[1];

    }
}

int skiplist::Max() {

    int max = -1;
    skiplist_node* currNode = m_pHeader;

    for(int level=max_curr_level; level >=1; level--) {

        while ( currNode->forwards[level] ) {

            if ( currNode->data.second > max ){ max = currNode->data.second; }
        }
    }

    return max;

};

int skiplist::Min() {

    int min = INT_MAX;
    skiplist_node* currNode = m_pHeader;

    for(int level=max_curr_level; level >=1; level--) {

        while ( currNode->forwards[level] ) {

            if ( currNode->data.second < min ){ min = currNode->data.second; }
        }
    }

    return  min;

};

int skiplist::Min(){};
