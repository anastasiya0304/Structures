#include "stdafx.h"
#include <queue>
#include <iostream>
#include "AVLTree.h"

void  CAVLTree::rotateLeft( CAVLTreeNode* node ) {

    if (!node->Left) { return; }

    CAVLTreeNode *p = node->Left;
    node->Left = p->Right;
    p->Right = node;
    fixHeight(node);
    fixHeight(p);

}

void CAVLTree::rotateRight( CAVLTreeNode *node ) {

    if (!node->Right) { return; }

    CAVLTreeNode *p = node->Right;
    node->Right = p->Left;
    p->Left= node;
    fixHeight(node);
    fixHeight(p);

}


void CAVLTree::Add ( std::pair<int,int> param ) {

    CAVLTreeNode* node=root;

    if ( root== nullptr ) {

        root = new CAVLTreeNode;
        root->pair=param;
        root->Right= nullptr;
        root->Left= nullptr;
        root->Height=1;

        return;
    }

    while (true) {

        if(param.first>node->pair.first){

            if (node->Right == nullptr){

                CAVLTreeNode* inode = new CAVLTreeNode;
                inode->pair=param;
                inode->Right= nullptr;
                inode->Left= nullptr;
                inode->Height=1;
                node->Right=inode;
                fixupBalance( root );
                return;

            }

            node=node->Right;

        } else {

            if (node->Left == nullptr) {

                CAVLTreeNode* inode = new CAVLTreeNode;
                inode->pair.first=param.first;
                inode->pair.second=param.second;
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



int CAVLTree::balance( const CAVLTreeNode* node ) {

    assert( node != nullptr );
    return height( node->Left ) - height( node->Right );

}


void CAVLTree::fixupBalance( CAVLTreeNode*& node ) {

    assert( node != nullptr );

    if( balance( node ) == 2 ) {

        if( balance( node->Left ) == -1 ) {

            rotateLeft( node->Left );

        }


        rotateRight( node );

    } else if ( height( node->Left ) - height( node->Right ) == -2 ) {

        if( balance( node->Right ) == 1 ) {

            rotateRight( node->Right );

        }

        rotateLeft( node );

    } else {

        fixHeight( node );
    }
}

void CAVLTree::fixHeight( CAVLTreeNode* node ) {

    node->Height = std::max( height( node->Left ), height( node->Right ) ) + 1;

}

int CAVLTree::Max() {

    return max(root);

}


int CAVLTree::max( CAVLTreeNode* node ) {

    assert( node != nullptr );

    while (node->Right != nullptr) {

        node = node->Right;

    }

    return node->pair.second;
}

int CAVLTree::Min() {

    return min(root);

}

int CAVLTree::min( CAVLTreeNode* node ) {

    assert( node != nullptr );

    while (node->Left != nullptr) {

        node = node->Left;

    }

    return node->pair.second;
}


bool CAVLTree::Has( int key ) {

    return has( root, key);

}


bool CAVLTree::has( CAVLTreeNode* node, int key ) {

    if (node == nullptr) return false;

    if (node->pair.first == key) { return true; }

    if (key < node->pair.first) {

        return has(node->Left, key);

    }

    else {

        return has(node->Right, key);

    }
}

bool CAVLTree::Remove( int key ) {

    if (CAVLTree::Has(key)) {

        rem(root, key);
        return true;

    } else { return false; }

}


CAVLTree::CAVLTreeNode* CAVLTree::rem(CAVLTreeNode* node, int key ) {

    assert( node != nullptr );

    CAVLTreeNode *p;

    if (node->pair.first == key) {

        if (node->Left == nullptr || node->Right == nullptr) {

            if (node->Left == nullptr) {

                p = node->Right;

            }

            else {

                p = node->Left;

            }

            delete node;
            return p;

        } else {

            for (p = node->Right; p->Left != nullptr; p = p->Left);
            node->pair.first = p->pair.first;
            node->pair.second = p->pair.second;
            node->Right = rem(node->Right, p->pair.first);
            fixupBalance(node);
            return node;

        }
    }

    if (key < node->pair.first) {

        node->Left = rem(node->Left, key);

    }

    else {

        node->Right = rem(node->Right, key);

    }

    fixupBalance(node);
    return node;

}

void CAVLTree::Print(std::ostream &outputstream) {

    print( outputstream, root );

}

void CAVLTree::print(std::ostream &outputstream, CAVLTreeNode *node) {

	if (node == nullptr) { return; }

	std::queue <CAVLTreeNode*> q;
	q.push(node);
	

	while (!q.empty()) {

		CAVLTreeNode* node1 = q.front();
		outputstream << node1->pair.second << " ";
		q.pop();

		if (node1->Left != nullptr) { q.push(node1->Left); }
		if (node1->Right != nullptr) { q.push(node1->Right); }

	}

}
