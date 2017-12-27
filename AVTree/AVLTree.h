
#include <cmath>
#include <fstream>
#include <iostream>

#include <algorithm>
#include <cassert>

class CAVLTree {

public:

    CAVLTree()  { root= nullptr; }

    bool Has( int key );
    void Add( std::pair<int,int> param  );
    bool Remove( int key );
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
    static bool has( CAVLTreeNode* node, int key );
    static CAVLTreeNode* rem(CAVLTreeNode* node, int key );
    static void print(std::ostream &outputstream, CAVLTreeNode *node);
};
