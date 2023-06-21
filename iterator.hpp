#ifndef ITERATOR_HPP_INCLUDED
#define ITERATOR_HPP_INCLUDED

template<typename T>
struct binTree<T>::iterator : public std::iterator<std::bidirectional_iterator_tag, Node<T>>
{

	friend iterator binTree<T>::begin() const ;
	friend iterator binTree<T>::end() const;
	Node<T>* current;

private:

	rightOrLeftChild whichChild(Node<T>* child)
	{
		Node<T>* parent_ = child->parent;
		if(parent_ == nullptr) return root_;

		else if( parent_ ->leftChild!= nullptr && parent_ ->leftChild == child)
        { return leftChild_; }
		else return rightChild_;
	}

public:
	//constructors
	iterator() throw (): current (nullptr){}
	iterator(Node<T>* arg) throw () : current (arg) {}

	typename binTree<T>::iterator& operator++ ()
	{
		typename binTree<T>::rightOrLeftChild wChild=  whichChild(current);
		if(current->rightChild!= nullptr)
		{
			current = current->rightChild; // goto the right child
			while(current->leftChild!=nullptr) current = current->leftChild;// if have left node , go to the left most node
		}
		else if(wChild== binTree<T>::leftChild_ && current->rightChild== nullptr)
		{
			current = current->parent;
		}
		else if(wChild== binTree<T>::rightChild_ && current->rightChild== nullptr)
		{
			for(typename binTree<T>::rightOrLeftChild w_Child =whichChild(current->parent); w_Child!= binTree<T>::leftChild_;)  // [&&] go to the chains of parent until find a parent who is L child child of it's parent
				if(w_Child== binTree<T>::root_)  { current = nullptr ; return *this;} //delete this whole statement and next next line's else keyword you get my old code which was buggy, why?
				else { current = current->parent; w_Child =whichChild(current->parent); } //cause we might reach at some R node whose parent is root node , e.g a tree with three nodes, now if we're currently at R node, that means, it's parent is root node (a node whose parent is null is root node) -
				//since we're at right node and it's doesn't has R child, jump to [&&]. we do this since we're done printing some subtree. if 're done with some left subtree then we make parent of that left subtree current
				//if subtree is right that we're done with, that means , we're done printing sibling L subtree and it's parent and R subtree, now go to parent of R subtree's parent.
				current = current->parent->parent; //done this two times since we're at some current whose parent is left child of it's parent, so current = current->parent; makes current who is left child of it's parent now
				//current = current->parent; //done with some left subtree, now it's parent is current
		}
		return *this;
	}

	typename binTree<T>::iterator& operator-- ()  // to write this operator ,I used code of operator++ and I simply replaced current->leftChild with current->rightChild and vice versa. Also replaced binTree<T>::rightChild_ with binTree<T>::leftChild_ and vice versa
	{
		typename binTree<T>::rightOrLeftChild wChild=  whichChild(current);
		if(current->leftChild!= nullptr)
		{
			current = current->leftChild; // goto the right child
			while(current->rightChild!=nullptr) current = current->rightChild;// if have left node , go to the left most node
		}
		else if(wChild== binTree<T>::rightChild_ && current->leftChild== nullptr)
		{
			current = current->parent;
		}
		else if(wChild== binTree<T>::leftChild_ && current->leftChild== nullptr)
		{
			while(whichChild(current->parent)!= binTree<T>::rightChild_ )
				if(whichChild(current->parent) == binTree<T>::root_) { current = nullptr ; return *this;}
				else current = current->parent;
				current = current->parent;
				current = current->parent;
		}
		return *this;
	}
	typename binTree<T>::iterator operator-- (int)
	{
		iterator copy(*this);
		--(*this);
		return copy;
	}
	typename binTree<T>::iterator operator++ (int)
	{
		iterator copy(*this);
		++(*this);
		return copy;
	}

	T& operator* () const
	{
		if (current== nullptr) throw nullDeref("Dereferenced nullptr!!, error in operator*"); else return current->value ;
	}
	bool operator == (const iterator& rhs) const
	{
		return (current == rhs.current) ?  true :  false;
	}
	bool operator != (const iterator& rhs) const
	{
		return (current != rhs.current) ?  true : false;
	}
	T* operator-> () const
	{
		return &(current->value);
	}
};


#endif // ITERATOR_HPP_INCLUDED
