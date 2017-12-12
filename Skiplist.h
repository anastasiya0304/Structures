//
// Created by Vipolion on 12.12.2017.
//

#ifndef AVL_SKIP_SKIPLIST_H
#define AVL_SKIP_SKIPLIST_H

#endif //AVL_SKIP_SKIPLIST_H

#include <cstring>
#include <cstdlib>
#include <iostream>


class Node
{
public:
    int key;
    Node **forward;
    Node(int, int);
};

Node::Node(int key, int level)
{
    this->key = key;
    forward = new Node*[level+1];
    std::memset(forward, 0, sizeof(Node*)*(level+1));
};


class SkipList
{

    int MAXLVL;
    float P;

    int level;

    Node *header;
public:
    SkipList(int, float);
    int randomLevel();
    Node* createNode(int, int);
    void insertElement(int);
    bool deleteElement(int);
    bool searchElement(int);
    void displayList(std::ostream&);
};

SkipList::SkipList(int MAXLVL, float P)
{
    this->MAXLVL = MAXLVL;
    this->P = P;
    level = 0;


    header = new Node(-1, MAXLVL);
};


int SkipList::randomLevel()
{
    float r = (float)::random()/RAND_MAX;
    int lvl = 0;
    while(r < P && lvl < MAXLVL)
    {
        lvl++;
        r = (float)random()/RAND_MAX;
    }
    return lvl;
};


Node* SkipList::createNode(int key, int level)
{
    Node *n = new Node(key, level);
    return n;
};


void SkipList::insertElement(int key)
{
    Node *current = header;

    Node *update[MAXLVL+1];
    memset(update, 0, sizeof(Node*)*(MAXLVL+1));

    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] != nullptr &&
              current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }

    current = current->forward[0];

    if (current == nullptr || current->key != key)
    {
        int rlevel = randomLevel();

        if(rlevel > level)
        {
            for(int i=level+1;i<rlevel+1;i++)
                update[i] = header;

            level = rlevel;
        }

        Node* n = createNode(key, rlevel);

        for(int i=0;i<=rlevel;i++)
        {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
        std::cout<<"Successfully Inserted key "<<key<<"\n";
    }
};


bool SkipList::deleteElement(int key)
{
    Node *current = header;

    Node *update[MAXLVL+1];
    memset(update, 0, sizeof(Node*)*(MAXLVL+1));

    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] != nullptr  &&
              current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }

    current = current->forward[0];

    if(current != nullptr and current->key == key)
    {

        for(int i=0;i<=level;i++)
        {

            if(update[i]->forward[i] != current)
                break;

            update[i]->forward[i] = current->forward[i];
        }

        while(level>0 &&
              header->forward[level] == 0)
            level--;
        return true;
    }
    return false;
};


bool SkipList::searchElement(int key)
{
    Node *current = header;

    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] &&
              current->forward[i]->key < key)
            current = current->forward[i];

    }

    current = current->forward[0];

    if(current and current->key == key)
        return true;
    else return false;
};

void SkipList::displayList(std::ostream &outputstream)
{

    for (int i=0;i<=level;i++)
    {
        Node *node = header->forward[i];
        outputstream <<  "Level " << i << ": ";
        while (node != nullptr)
        {
            outputstream << node->key<<" ";
            node = node->forward[i];
        }
        outputstream << "\n";
    }
};
