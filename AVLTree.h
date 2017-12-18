
#pragma once
#include <cmath>
#include <fstream>
#include <iostream>

#include <algorithm>
#include <cassert>


// АВЛ-дерево с целочисленными ключами.
class CAVLTree {
public:
    CAVLTree()  {
        root= nullptr;
    }
    bool Has( int key );
    void Add( int key );
    bool Remove( int key );
    void Print(std::ostream&);
    int Min();
    int Max();

//private:
    
    struct CAVLTreeNode {
        int Key;
        int Height;
        CAVLTreeNode* Left;
        CAVLTreeNode* Right;

    };

    CAVLTreeNode* root;

    static void fixupBalance( CAVLTreeNode*& node );
    static int height( const CAVLTreeNode* node ) { return node == nullptr ? 0 : node->Height; }
    static int balance( const CAVLTreeNode* node );
    static void fixHeight( CAVLTreeNode* node );
    static void rotateLeft( CAVLTreeNode* node );
    static void rotateRight( CAVLTreeNode* node );
    static int max( CAVLTreeNode* node );
    static int min( CAVLTreeNode* node );
    static bool has( CAVLTreeNode* node, int key );
    static CAVLTreeNode* rem(CAVLTreeNode* node, int key);
    static void print(std::ostream &outputstream, CAVLTreeNode *node);
};

void  CAVLTree::rotateLeft( CAVLTreeNode* node )
{
    if (!node->Left){
        return;
    }
    CAVLTreeNode *p = node->Left;
    node->Left = p->Right;
    p->Right = node;
    fixHeight(node);
    fixHeight(p);

}

void CAVLTree::rotateRight( CAVLTreeNode *node ) {

    if (!node->Right){
    return;
    }

    CAVLTreeNode *p = node->Right;
    node->Right = p->Left;
    p->Left= node;
    fixHeight(node);
    fixHeight(p);

}


void CAVLTree::Add( int key )
{
    CAVLTreeNode* node=root;

    if( root== nullptr ) {
        root = new CAVLTreeNode;
        root->Key=key;
        root->Right= nullptr;
        root->Left= nullptr;
        root->Height=1;

        return;
    }

    while (true){
        if(key>node->Key){
            if (node->Right == nullptr){

                CAVLTreeNode* inode = new CAVLTreeNode;
                inode->Key=key;
                inode->Right= nullptr;
                inode->Left= nullptr;
                inode->Height=1;
                node->Right=inode;
                fixupBalance( root );
                return;

            }
             node=node->Right;

        } else {

            if (node->Left == nullptr){

                CAVLTreeNode* inode = new CAVLTreeNode;
                inode->Key=key;
                inode->Right= nullptr;
                inode->Left= nullptr;
                inode->Height=1;
                node->Left=inode;
                fixupBalance( root );
                return;

            }
            node=node->Left;


        }
    }
}



int CAVLTree::balance( const CAVLTreeNode* node )
{
    assert( node != nullptr );
    return height( node->Left ) - height( node->Right );
}

void CAVLTree::fixupBalance( CAVLTreeNode*& node )
{
    assert( node != nullptr );

    if( balance( node ) == 2 ) {
        if( balance( node->Left ) == -1 ) {
            rotateLeft( node->Left );
        }
        rotateRight( node );
    } else if( height( node->Left ) - height( node->Right ) == -2 ) {
        if( balance( node->Right ) == 1 ) {
            rotateRight( node->Right );
        }
        rotateLeft( node );
    } else {
        fixHeight( node );
    }
}

void CAVLTree::fixHeight( CAVLTreeNode* node )
{
    node->Height = std::max( height( node->Left ), height( node->Right ) ) + 1;
}

int CAVLTree::Max(){

    return max(root);

}


int CAVLTree::max( CAVLTreeNode* node ) {
    assert( node != nullptr );
    while (node->Right != nullptr) {
        node = node->Right;
    }
    return node->Key;
}

int CAVLTree::Min(){

    return min(root);

}

int CAVLTree::min( CAVLTreeNode* node ) {
    assert( node != nullptr );
    while (node->Left != nullptr) {
        node = node->Left;
    }
    return node->Key;
}

bool CAVLTree::Has( int key ) {

    return has(root,key);

}

bool CAVLTree::has( CAVLTreeNode* node, int key ){

    if (node == nullptr) return false;

    if (node->Key == key) {
        return true;
    }

    if (key < node->Key) {
        return has(node->Left, key);
    } else {
        return has(node->Right, key);
    }
}

bool CAVLTree::Remove( int key ){

   if (CAVLTree::Has(key)) {
       rem(root, key);
       return true;
   } else return false;

}


CAVLTree::CAVLTreeNode* CAVLTree::rem(CAVLTreeNode* node, int key){
    assert( node != nullptr );

    CAVLTreeNode *p;
    if (node->Key == key) {
        if (node->Left == nullptr || node->Right == nullptr) {
            if (node->Left == nullptr) {
                p = node->Right;
            } else {
                p = node->Left;
            }
            delete node;
            return p;
        } else {
            for (p = node->Right; p->Left != nullptr; p = p->Left);
            node->Key = p->Key;
            node->Right = rem(node->Right, p->Key);
            fixupBalance(node);
            return node;
        }
    }

    if (key < node->Key) {
        node->Left = rem(node->Left, key);
    } else {
        node->Right = rem(node->Right, key);
    }

    fixupBalance(node);
    return node;
}
void CAVLTree::Print(std::ostream &outputstream){
    print( outputstream, root );
}
void CAVLTree::print(std::ostream &outputstream, CAVLTreeNode *node) {

    if (node == nullptr) {
        return;
    }

        outputstream << node->Key << " ";

        print(outputstream, node->Right);

        print(outputstream, node->Left);



}
// АВЛ-дерево с целочисленными ключами.
class CAVLTree {
public:
    CAVLTree()  {
        root= nullptr;
    }
    bool Has( int key );
    void Add( int key );
    bool Remove( int key );
    void Print(std::ostream&);
    int Min();
    int Max();

//private:
    // Узел дерева. Пока без Count.
    struct CAVLTreeNode {
        int Key;
        int Height;
        CAVLTreeNode* Left;
        CAVLTreeNode* Right;

    };

    CAVLTreeNode* root;

    static void add( CAVLTreeNode** node, int key );
    static void fixupBalance( CAVLTreeNode*& node );
    static int height( const CAVLTreeNode* node ) { return node == nullptr ? 0 : node->Height; }
    static int balance( const CAVLTreeNode* node );
    static void fixHeight( CAVLTreeNode* node );
    static void rotateLeft( CAVLTreeNode* node );
    static void rotateRight( CAVLTreeNode* node );
    static int max( CAVLTreeNode* node );
    static int min( CAVLTreeNode* node );
    static bool has( CAVLTreeNode* node, int key );
    static CAVLTreeNode* rem(CAVLTreeNode* node, int key);
    static void print(std::ostream &outputstream, CAVLTreeNode *node);
};

void  CAVLTree::rotateLeft( CAVLTreeNode* node )
{
    if (!node->Left){
        return;
    }
    CAVLTreeNode *p = node->Left;
    node->Left = p->Right;
    p->Right = node;
    fixHeight(node);
    fixHeight(p);

}

void CAVLTree::rotateRight( CAVLTreeNode *node ) {

    if (!node->Right){
    return;
    }

    CAVLTreeNode *p = node->Right;
    node->Right = p->Left;
    p->Left= node;
    fixHeight(node);
    fixHeight(p);

}


void CAVLTree::Add( int key )
{
    CAVLTreeNode* node=root;

    if( root== nullptr ) {
        root = new CAVLTreeNode;
        root->Key=key;
        root->Right= nullptr;
        root->Left= nullptr;
        root->Height=1;

        return;
    }

    while (1){
        if(key>node->Key){
            if (node->Right == nullptr){

                CAVLTreeNode* inode = new CAVLTreeNode;
                inode->Key=key;
                inode->Right= nullptr;
                inode->Left= nullptr;
                inode->Height=1;
                node->Right=inode;
                fixupBalance( root );
                return;

            }
             node=node->Right;

        } else {

            if (node->Left == nullptr){

                CAVLTreeNode* inode = new CAVLTreeNode;
                inode->Key=key;
                inode->Right= nullptr;
                inode->Left= nullptr;
                inode->Height=1;
                node->Left=inode;
                fixupBalance( root );
                return;

            }
            node=node->Left;


        }
    }
}



int CAVLTree::balance( const CAVLTreeNode* node )
{
    assert( node != nullptr );
    return height( node->Left ) - height( node->Right );
}

void CAVLTree::fixupBalance( CAVLTreeNode*& node )
{
    assert( node != nullptr );

    if( balance( node ) == 2 ) {
        if( balance( node->Left ) == -1 ) {
            rotateLeft( node->Left );
        }
        rotateRight( node );
    } else if( height( node->Left ) - height( node->Right ) == -2 ) {
        if( balance( node->Right ) == 1 ) {
            rotateRight( node->Right );
        }
        rotateLeft( node );
    } else {
        fixHeight( node );
    }
}

void CAVLTree::fixHeight( CAVLTreeNode* node )
{
    node->Height = std::max( height( node->Left ), height( node->Right ) ) + 1;
}

int CAVLTree::Max(){

    return max(root);

}


int CAVLTree::max( CAVLTreeNode* node ) {
    assert( node != nullptr );
    while (node->Right != nullptr) {
        node = node->Right;
    }
    return node->Key;
}

int CAVLTree::Min(){

    return min(root);

}

int CAVLTree::min( CAVLTreeNode* node ) {
    assert( node != nullptr );
    while (node->Left != nullptr) {
        node = node->Left;
    }
    return node->Key;
}

bool CAVLTree::Has( int key ) {

    return has(root,key);

}

bool CAVLTree::has( CAVLTreeNode* node, int key ){

    if (node == nullptr) return false;

    if (node->Key == key) {
        return true;
    }

    if (key < node->Key) {
        return has(node->Left, key);
    } else {
        return has(node->Right, key);
    }
}

bool CAVLTree::Remove( int key ){

   if (CAVLTree::Has(key)) {
       rem(root, key);
       return true;
   } else return false;

}


CAVLTree::CAVLTreeNode* CAVLTree::rem(CAVLTreeNode* node, int key){
    assert( node != nullptr );

    CAVLTreeNode *p;
    if (node->Key == key) {
        if (node->Left == nullptr || node->Right == nullptr) {
            if (node->Left == nullptr) {
                p = node->Right;
            } else {
                p = node->Left;
            }
            delete node;
            return p;
        } else {
            for (p = node->Right; p->Left != nullptr; p = p->Left);
            node->Key = p->Key;
            node->Right = rem(node->Right, p->Key);
            fixupBalance(node);
            return node;
        }
    }

    if (key < node->Key) {
        node->Left = rem(node->Left, key);
    } else {
        node->Right = rem(node->Right, key);
    }

    fixupBalance(node);
    return node;
}
void CAVLTree::Print(std::ostream &outputstream){
    print( outputstream, root );
}
void CAVLTree::print(std::ostream &outputstream, CAVLTreeNode *node) {

    if (node == nullptr) {
        return;
    }

        outputstream << node->Key << " ";

        print(outputstream, node->Right);

        print(outputstream, node->Left);



}
