//Author Dheerajabc@gmail.com

#ifndef BINTREE_H_INCLUDED
#define BINTREE_H_INCLUDED

#include <iostream>
#include <iterator>
#include <exception>
#include "node.h"
#include "exceptions.hpp"

template<typename T> class binTree;
template<typename T> std::iostream& operator<< (std::iostream&, const binTree<T>& rhs);

template<typename T> class binTree
{

	Node<T> * TreeNode;

private:

	void auxInsert(Node<T>* parent , Node<T>*& child, T val);
	void printTree(Node<T>* nodes) const;
	Node<T>* searchHelper( const T& val , Node<T>* temp) const;
	size_t sizeHelper(Node<T>* tNode ) const ;
	void removeHelper(Node<T>*&  NodeToBeDeleted , Node<T>*&  connParentsChildPointerToNodeToBeDelsChild) const;

public:
	//constructors and copy constructos
	binTree(): TreeNode(nullptr)  {}
	binTree(T val) ;
	binTree(const binTree& );
	binTree(binTree&&);
	binTree& operator= (const binTree&);
	binTree& operator=(binTree&&);

	//non-observer interface
	void insert(T val) throw(std::bad_alloc);
	void remove(const T& val);
	void clear(Node<T>* node);
	~binTree() throw();

	//internal utilities
	enum rightOrLeftChild {leftChild_ , rightChild_ , root_};
	rightOrLeftChild whichChild(Node<T>* child) const;

	//observer interface
	void print() const;
	friend std::iostream& operator<< <> (std::iostream&, const binTree<T>& rhs) ;
	bool empty() const;

	size_t size() const;
	Node<T>* search( const T& val ) const;
	int height(Node<T>* temp) const;

	struct iterator;
	iterator begin() const ;
	iterator end() const;
};


template<typename T>
void binTree<T>::auxInsert(Node<T>* parent , Node<T>*& child, T val)
{
	if(child == nullptr)
	{
		child = new Node<T>(val);
		child->parent = parent;
	}
	else if (val > child ->value) auxInsert(child, child->rightChild, val);
	else if (val <= child ->value ) auxInsert(child, child->leftChild, val);
}

template<typename T>
void binTree<T>::printTree(Node<T>* nodes) const
{
	if(nodes == nullptr) return;
	printTree(nodes->leftChild);
	std::cout<< nodes->value<<" ";
	printTree(nodes->rightChild);
}

template<typename T>
binTree<T>::binTree(T val) : binTree<T>::TreeNode(new Node<T>(val)) {}

template<typename T>
binTree<T>::binTree(const binTree& rhs)
{
    typename binTree<T>::iterator begin = rhs.begin();
    for(;begin!=rhs.end();++begin) insert(*begin);
}

template<typename T>
binTree<T>::binTree(binTree&& rhs) : TreeNode(rhs.TreeNode) { }

template<typename T>
binTree<T>& binTree<T>::operator= (const binTree<T>& rhs)
{
    typename binTree<T>::iterator begin = rhs.begin();
    for(;begin!=rhs.end();++begin) insert(*begin);
    return *this;
}

template<typename T>
binTree<T>& binTree<T>::operator= (binTree<T>&& rhs)
{
   TreeNode = rhs.TreeNode;
    return *this;
}

template<typename T>
void binTree<T>::insert(T val) throw(std::bad_alloc) try
{
	if(TreeNode == nullptr)
	{
		TreeNode = new Node<T>(val);
		TreeNode->parent = nullptr;
	}
	else
	{
		auxInsert(nullptr,TreeNode, val );
	}
}
catch(std::bad_alloc& err)
{
	std::cerr<<"There occured some unhandlable exception, error : "<< err.what() <<std::endl;
}

template<typename T>
void binTree<T>::print() const
{
	printTree(TreeNode);
	std::cout<<std::endl;
}

template<typename T>
Node<T>* binTree<T>::searchHelper( const T& val , Node<T>* temp) const
{

	if(temp == nullptr) return nullptr;
	else if(temp->value == val) return temp;
	else if(temp->value > val) return searchHelper(val, temp->leftChild);
	else  return searchHelper(val, temp->rightChild);
}

//empty function to check whether tree is empty or not
template<typename T>
bool binTree<T>::empty() const
{
	return TreeNode==nullptr? true : false;
}

template<typename T>
size_t binTree<T>::sizeHelper(Node<T>* tNode ) const
{
	if(tNode==nullptr) return 0;
	else return 1+ sizeHelper(tNode->leftChild) + sizeHelper(tNode->rightChild);
}

template<typename T>
size_t binTree<T>::size() const
{
	return sizeHelper(TreeNode);
}

template<typename T>
Node<T>* binTree<T>::search( const T& val ) const
{
	return searchHelper(val, TreeNode);
}

template<typename T>
int binTree<T>::height(Node<T>* temp) const
{
	if(temp == nullptr) return 0;
	else return (height(temp->leftChild) > height(temp->rightChild)) ? height(temp->leftChild) +1 : height(temp->rightChild)+1 ;
}

template<typename T>
typename binTree<T>::rightOrLeftChild binTree<T>::whichChild(Node<T>* child) const
{
	Node<T>* parent_ = child->parent;
	if(parent_ == nullptr) return root_;
	if(parent_ ->leftChild != nullptr && parent_ ->leftChild == child) return leftChild_;
	else return rightChild_;
}

template<typename T>
void binTree<T>::removeHelper(Node<T>*&  NodeToBeDeleted , Node<T>*&  connParentsChildPointerToNodeToBeDelsChild) const
{
	// delete node helper of case when node to be deleted has one child, either L or R Child
            if(NodeToBeDeleted->rightChild != nullptr)
            {
                        connParentsChildPointerToNodeToBeDelsChild = NodeToBeDeleted->rightChild;
                        NodeToBeDeleted->rightChild->parent = NodeToBeDeleted->parent;
                        delete NodeToBeDeleted;
            }
            else
            {
                        connParentsChildPointerToNodeToBeDelsChild= NodeToBeDeleted->leftChild;
                        NodeToBeDeleted->leftChild->parent = NodeToBeDeleted->parent;
                        delete NodeToBeDeleted;
            }
}

template<typename T>
void binTree<T>::remove(const T& val)
{
	Node<T>* NodeToBeDeleted = search(val);

	if(NodeToBeDeleted == nullptr) std::cerr<<"Node doesn't exists!"<<std::endl;
	else
	{
		if(NodeToBeDeleted->rightChild != nullptr && NodeToBeDeleted->leftChild != nullptr)
		{
                    Node<T>* temp =NodeToBeDeleted->rightChild;
                    while(temp->leftChild != nullptr) temp = temp->leftChild;

                    NodeToBeDeleted->value = temp->value; //swap the value i.e node to be deleted's value swapped with node to be deleted's R sub tree's smallest child which is L most node of R sub tree

                    Node<T>* tempParent =   temp->parent;
                    if(whichChild(temp) ==rightChild_) // need to find whether smallest child of R sub tree of node_to_be_deleted is L child of it's parent
                    {
                        // or R child due to the reason that R sub tree of node to be deleted might have only node in its R sub tree i.e node to be deleted has only one R child node/sub tree
                                if(temp->rightChild !=nullptr)
                                {
                                        tempParent->rightChild = temp->rightChild;
                                        temp->rightChild->parent =tempParent;
                                        delete temp;
                                }
                                else
                                {
                                        delete temp;
                                        tempParent->rightChild = nullptr;
                                }
                    }
                    else
                    {
                                if(temp->rightChild !=nullptr)
                                {
                                        tempParent->leftChild = temp->rightChild;
                                        temp->rightChild->parent =tempParent;
                                        delete temp;
                                }
                                else
                                {
                                        delete temp;
                                        tempParent->leftChild = nullptr;
                                }
                    }
		}
		else if(NodeToBeDeleted->rightChild == nullptr && NodeToBeDeleted->leftChild == nullptr)
		{
			Node<T>* tempParent =NodeToBeDeleted->parent;
                    if(tempParent->leftChild == NodeToBeDeleted)
                    {
                            delete tempParent->leftChild;
                            tempParent->leftChild= nullptr;
                    }
                    else
                    {
                            delete tempParent->rightChild;
                            tempParent->rightChild= nullptr;
                    }
		}
		else
		{
			Node<T>* tempParent =NodeToBeDeleted->parent;
			if(tempParent->leftChild == NodeToBeDeleted) removeHelper(NodeToBeDeleted, tempParent->leftChild );
			else removeHelper(NodeToBeDeleted, tempParent->rightChild );
		}
	}
}

template<typename T>
void binTree<T>::clear(Node<T>* node)
{
	if(node != NULL)
	{
		clear(node->leftChild);
		clear(node->rightChild);
		delete node;
	}
}

template<typename T>
inline binTree<T>::~binTree() throw()
{
	clear(TreeNode);
}

template<typename T> std::ostream& operator<< (std::ostream& lhs,  const binTree<T>& rhs)
{
	rhs.print();
	return lhs;
}

#include "iterator.hpp"

template<typename T>
inline typename binTree<T>::iterator binTree<T>::end() const
{
	return typename binTree<T>::iterator(nullptr);
}

template<typename T>
inline typename binTree<T>::iterator binTree<T>::begin() const
{
	Node<T>* temp = binTree<T>::TreeNode;
	while(temp->leftChild != nullptr) temp = temp->leftChild;
	return typename binTree<T>::iterator(temp);
}

#endif // BINTREE_H_INCLUDED
