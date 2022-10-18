#include <iostream>
#include "Phone.h"
#include "Email.h"

using namespace std;

template <typename T>
class BinaryTree
{
	struct node{
		T value;
		struct node* right;
		struct node* left;
	};


public:
	BinaryTree();
	void SetCon(int dollars);
	~BinaryTree();
	void Remove(BinaryTree * tree, string fanid);
	void add(T val);
	void printPreOrder();
	void printInOrder();
	void printPostOrder();
	int size();
	bool lookup(T val);
	Fan* search(string fanid);


private:
	struct node* root;
	int treeSize;
	void add(struct node** node, T val);
	bool lookup(struct node* node, T val);
	Fan* search(struct node* node, string fanid);
	void printPreOrder(struct node* node);
	void printInOrder(struct node* node);
	void printPostOrder(struct node* node);
	void deleteTree(struct node* node);
};

template <typename T>
BinaryTree<T>::BinaryTree(){
	this->root = NULL;
	this->treeSize = 0;
}

template <typename T>
BinaryTree<T>::~BinaryTree(){
	deleteTree(this->root);
}

template <typename T>
int BinaryTree<T>::size(){
	return this->treeSize;
}

template <typename T>
void BinaryTree<T>::add(T val){
	add(&(this->root), val);
}

template <typename T>
void BinaryTree<T>::add(struct node** node, T val){
	if(*node == NULL)	{
		struct node* tmp = new struct node;
		tmp->value = val;
		tmp->left=NULL;
		tmp->right = NULL;
		*node = tmp;
		this->treeSize++;
	}else{
		if(*val > *((*node)->value)){
			//cout << "saga ekledi.." << endl;
			// cout << "val -> " << *val << " value -> " << *((*node)->value) << endl;
			add(&(*node)->right, val);
		}else{
			//cout << "sola ekledi.." << endl;
			add(&(*node)->left, val);
		}
	}
}

template <typename T>
void BinaryTree<T>::printInOrder(){
	printInOrder(this->root);
	std::cout << std::endl;
}

template <typename T>
void BinaryTree<T>::printInOrder(struct node* node){
	if(node != NULL){
		printInOrder(node->left);
		std::cout << *(node->value) << ", ";
		printInOrder(node->right);
	}
}

template <typename T>
void BinaryTree<T>::printPreOrder(){
	printPreOrder(this->root);
	std::cout << std::endl;
}

template <typename T>
void BinaryTree<T>::printPreOrder(struct node* node){
	if(node != NULL)	{
		std::cout << node->value << ", ";
		printInOrder(node->left);
		printInOrder(node->right);
	}
}

template <typename T>
void BinaryTree<T>::printPostOrder(){
	printPostOrder(this->root);
	std::cout << std::endl;
}

template <typename T>
void BinaryTree<T>::printPostOrder(struct node* node){
	if(node != NULL){
		printInOrder(node->left);
		printInOrder(node->right);
		std::cout << node->value << ", ";
	}
}


template <typename T>
void BinaryTree<T>::deleteTree(struct node* node){
	if(node != NULL){
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}

template <typename T>
bool BinaryTree<T>::lookup(T val){
	return lookup(this->root, val);
}

template <typename T>
bool BinaryTree<T>::lookup(struct node* node, T val){
	if(node == NULL){
		return false;
	}else{
		if(val == node->value){
			return true;
		}

		if(val > node->value){
			return lookup(node->right, val);
		}else{
			return lookup(node->left, val);
		}
	}

}


template <typename T>
Fan* BinaryTree<T>::search(string fanid){
	return search(this->root, fanid);
}


template <typename T>
Fan* BinaryTree<T>::search(struct node* node, string fanid) {
	if (node == NULL) {
		return NULL;
		
	}
	else {
		if (fanid == node->value->GetVal()) {
			
			return (node->value->GetFan());
		}
		if (fanid > node->value->GetVal()) {
			
			return search(node->right, fanid);
		}
		if (fanid < node->value->GetVal()) {
			
			return search(node->left, fanid);
		}

	}
}
template <typename T>
void BinaryTree<T>::Remove(BinaryTree * tree, string fanid) {

	struct node* curr = tree->root;
    struct node* prev = NULL;
 
    while (curr != NULL && curr->value->GetVal() != fanid) {
        prev = curr;
        if (fanid < curr->value->GetVal())
            curr = curr->left;
        else
            curr = curr->right;
    }
 
    if (curr == NULL) {
        // cout << "Key " << fanid << " not found in the"
        //      << " provided BST.\n";
        return;
    }
 
    if (curr->left == NULL || curr->right == NULL) {

        struct node* newCurr;
 
        if (curr->left == NULL)
            newCurr = curr->right;
        else
            newCurr = curr->left;
 
        if (prev == NULL)
            return;

        if (curr == prev->left)
            prev->left = newCurr;
        else
            prev->right = newCurr;
 
        delete curr;
    }
 
    else {
        struct node* p = NULL;
        struct node* temp;
 
        temp = curr->right;
        while (temp->left != NULL) {
            p = temp;
            temp = temp->left;
        }

        if (p != NULL)
            p->left = temp->right;
 
        else
            curr->right = temp->right;
 
        curr->value = temp->value;
        delete temp;
    }
    return;
}



