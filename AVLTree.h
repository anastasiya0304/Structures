//
// Created by Vipolion on 20.12.2017.
//

#ifndef AVL_SKIP_AVLTREE_H
#define AVL_SKIP_AVLTREE_H

#endif //AVL_SKIP_AVLTREE_H

#include <cmath>
#include <fstream>
#include <iostream>

#include <algorithm>
#include <cassert>

class CAVLTree {
public:
    CAVLTree()  {

        root= nullptr;
    }

    bool Has( std::pair<int,int> param );
    void Add( std::pair<int,int> param  );
    bool Remove( std::pair<int,int> param );
    void Print(std::ostream&);
    int Min();
    int Max();

private:

    struct CAVLTreeNode {

        std::pair<int,int> pair;
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
    static bool has( CAVLTreeNode* node, std::pair<int,int> param );
    static CAVLTreeNode* rem(CAVLTreeNode* node, std::pair<int,int> param );
    static void print(std::ostream &outputstream, CAVLTreeNode *node);
};


