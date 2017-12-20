//
// Created by Vipolion on 20.12.2017.
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
}


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