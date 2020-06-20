#ifndef TREE_H
#define	TREE_H
#include "Node.h"
#include <iostream>

using namespace std;

class Tree {
private:
    Node* root;
    Node* newNode(int);
    Node* addNode(pair<string,Record>, Node*&);
    Node* rightRight(Node*);
    Node* rightLeft(Node*);
    Node* leftLeft(Node*);
    Node* leftRight(Node*);
    int height(Node*);
    Node* balancing( Node*&);
    int diff(Node*);
    void printInorder(Node*);
public:
    Tree();
    void inorder();
    void insert(pair<string,Record>);
    bool isEmpty();
    bool find(pair<string,Record>);
};

#endif	/* TREE_H */