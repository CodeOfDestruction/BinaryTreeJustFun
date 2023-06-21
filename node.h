#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

template<typename T> struct Node
{
    T value;
    Node * leftChild;
    Node * rightChild;
    Node * parent;

    //constructors
    Node(): value(T()) , leftChild(nullptr) , rightChild(nullptr) , parent (nullptr) {}
    Node(T val) : value(val) , leftChild(nullptr) , rightChild(nullptr) , parent (nullptr) {}
};

#endif // NODE_H_INCLUDED
