#include "Tree.h"

#include <iostream>
#include <iomanip>
using namespace std;

Tree::Tree() {
    root = NULL;
}

void Tree::insert(pair<string,Record> record) {
    root = addNode(record, root);
}

bool Tree::find(pair<string,Record> record) {
    bool result =false;
    Node *temp = root;
    do {
        if (temp->record.second.winLoss < record.second.winLoss) {
            temp = temp->right;
        } else
            temp = temp->left;
    } while (temp->record.second.winLoss != record.second.winLoss && temp!=NULL);
    if(temp->record.second.winLoss == record.second.winLoss){
        cout << record.second.winLoss;
        result = true;
    }
    return result;
}

Node* Tree::addNode(pair<string,Record> record, Node*& node) {
    if (node == NULL) {
        node = new Node;
        node->record = record;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;

        return node;
    } else if (record.second.winLoss < node->record.second.winLoss) {
        addNode(record, node->left);
        node = balancing(node);
    } else {
        addNode(record, node->right);
        node = balancing(node);
    }

    return node;
}

Node* Tree::rightRight(Node* node) {
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    return temp;
}

Node* Tree::leftLeft(Node* node) {
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;
}

Node* Tree::rightLeft(Node* node) {
    Node* temp = node->right;
    node->right = leftLeft(temp);
    return rightRight(node);
}

Node* Tree::leftRight(Node* node) {
    Node* temp = node->left;
    node->left = rightRight(temp);
    return leftLeft(node);
}

int Tree::height(Node* node) {
    int h = 0;
    if (node != NULL) {
        int left = height(node->left);
        int right = height(node->right);
        int maxHeight = max(left, right);
        h = maxHeight + 1;
    }

    return h;
}

int Tree::diff(Node* node) {
    int diff;
    int htLeft = height(node->left);
    int htRight = height(node->right);

    if (node == NULL)
        diff = 0;
    else
        diff = htLeft - htRight;

    return diff;
}

Node* Tree::balancing(Node*& node) {
    int balanced = diff(node);

    if (balanced > 1) {
        if (diff(node->left) > 0)
            node = leftLeft(node);
        else
            node = leftRight(node);
    } else if (balanced < -1) {
        if (diff(node->right) > 0)
            node = rightLeft(node);
        else
            node = rightRight(node);
    }

    return node;
}

void Tree::inorder() {
    printInorder(root);
}

void Tree::printInorder(Node* node) {
    if (node == NULL)
        return;
    printInorder(node->right);
    Record& ptr = node->record.second;
    set<int>& ptr2 = ptr.win;
    set<int>::iterator itr;
    
    cout << setw(11) << node->record.first;
    const int W = 4;
    itr = --ptr2.end();
    cout << setw(W) << *itr;
    ptr2 = ptr.loss;
    itr = --ptr2.end();
    cout << setw(W) << *itr;
    ptr2 = ptr.tie;
    itr = --ptr2.end();
    cout << setw(W) << *itr;
    cout << node->record.second.winLoss * 100 << "%" << endl;
    printInorder(node->left);
}

bool Tree::isEmpty() {
    if (root == NULL)
        return true;
    else
        return false;
}