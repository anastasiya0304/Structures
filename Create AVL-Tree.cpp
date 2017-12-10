#ifndef NAST_AVLTREE_H
#define NAST_AVLTREE_H

#endif //NAST_AVLTREE_H
#include <cmath>
#include <fstream>
#include <iostream>

#include <algorithm>
#include <assert.h>
#include <iostream>

// АВЛ-дерево с целочисленными ключами.
class CAVLTree {
public:
    CAVLTree() : root( nullptr ) {}
    bool Has( int key );
    void Add( int key );
    void Remove( int key );
    void Print(std::ostream &outputstream);

private:
    // Узел дерева. Пока без Count.
    struct CAVLTreeNode {
        int Key;
        int Height;
        CAVLTreeNode* Left;
        CAVLTreeNode* Right;
        CAVLTreeNode( int key ) : Key( key ), Height( 1 ), Left( nullptr ), Right( nullptr ) {}
    };

    CAVLTreeNode* root;

    static void add( CAVLTreeNode*& node, int key );
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
    CAVLTreeNode *p = node->Left;
    node->Left = p->Right;
    p->Right = node;
    fixHeight(node);
    fixHeight(p);

}

void CAVLTree::rotateRight( CAVLTreeNode *node ) {

    CAVLTreeNode *p = node->Right;
    node->Right = p->Right;
    p->Left= node;
    fixHeight(node);
    fixHeight(p);

}


void CAVLTree::Add( int key )
{
    add( root, key );
}

// Рекурсивное добавление узла в поддерево.
// node передается по ссылке, чтобы обновить указатель в случае поворота или добавления нового узла.
void CAVLTree::add( CAVLTreeNode*& node, int key )
{
    if( node == nullptr ) {
        node = new CAVLTreeNode( key );
        return;
    }
    // Рекурсивно добавляем узел.
    if( node->Key < key ) {
        add( node->Right, key );
    } else {
        add( node->Left, key );
    }
    // Восстановим баланс текущего узла.
    fixupBalance( node );
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

int CAVLTree::max( CAVLTreeNode* node ) {
    assert( node != nullptr );
    while (node->Right != NULL) {
        node = node->Right;
    }
    return node->Key;
}


int CAVLTree::min( CAVLTreeNode* node ) {
    assert( node != nullptr );
    while (node->Left != NULL) {
        node = node->Left;
    }
    return node->Key;
}

bool CAVLTree::Has( int key ) {

    has(root,key);
}

bool CAVLTree::has( CAVLTreeNode* node, int key ){

    assert( node != nullptr );

    if (node->Key == key) {
        return true;
    }

    if (key < node->Key) {
        return has(node->Left, key);
    } else {
        return has(node->Right, key);
    }
}

void CAVLTree::Remove( int key ){

    rem(root,key);
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
    assert(node != nullptr);
    print(outputstream, node->Left);
    outputstream << node->Key << " ";
    print(outputstream, node->Right);
}
