#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <string>
#include "LinkedListInterface.h"

using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T> {
private:
	struct Node {
		T data;
		Node* next;
		Node(const T& d, Node* n) : data(d), next(n) {}
		~Node() = default;
		friend ostream& operator<<(ostream& os, Node* node) {
			return os << ((node) ? node->data : "Not Found");
		}
	};
	Node* head;
public:
	LinkedList() : head(NULL) {}
	~LinkedList() {
		clear();
	}

	virtual void push_front(const T& value) {	//Insert function of node at front of list
		head = new Node(value, head);
		return;
	}
	virtual void pop_front(void) {	//Delete function of node at front of list
		Node* node_ptr = head;
		if (node_ptr == NULL) {
			return;
		}
		else {
			head = head->next;
			delete node_ptr;
			return;
		}
	}
	virtual T& front(void) {	//First function to output first item of list
		Node* node_ptr = head;
		return node_ptr->data;
	}
	virtual bool empty(void) const {	//Empty function to say if list is empty 
		Node* node_ptr = head;
		bool empty = false;
		if (node_ptr == NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	virtual void remove(const T& value) {	//Remove function for all like items in list
		while (head && head->data == value) {
			Node* tmp = head;
			head = head->next;
			delete tmp;
		}
		for (Node* current = head; current != NULL; current = current->next) {
			while (current->next != NULL && current->next->data == value) {
				Node* tmp = current->next;
				current->next = tmp->next;
				delete tmp;
			}
		}
		return;
	}
	virtual void clear(void) {	//Clear function of list of nodes
		Node* node_ptr = head;
		Node* next_ptr = NULL;
		while (node_ptr != NULL) {
			next_ptr = node_ptr->next;
			delete node_ptr;
			node_ptr = next_ptr;
		}
		head = NULL;
		return;
	}
	virtual void reverse(void) {	//Reverse function of the list 
		Node* current = head;
		Node* prev = NULL;
		Node* next = NULL;
		while (current != NULL) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		head = prev;
		return;
	}
	virtual size_t size(void) const {	//Size function to return number of nodes in list
		size_t listSize = 0;
		Node* node_ptr = head;
		while (node_ptr != NULL) {
			node_ptr = node_ptr->next;
			++listSize;
		}
		return listSize;
	}
	virtual string toString(void) const {	//PrintList function of the linked list
		string out = " ";
		string empty = " Empty!";
		Node* node_ptr = head;
		if (node_ptr == NULL) {
			return empty;
		}
		else {
			while (node_ptr != NULL) {
				out += node_ptr->data + " ";
				node_ptr = node_ptr->next;
			}
			return out;
		}
	}
	LinkedList<T>(const LinkedList<T>& other) {		//Copy function for deep copy of list
		Node* tmp = other.head;
		while (tmp != NULL) {
			push_front(tmp->data);
			tmp = tmp->next;
		}
		this->reverse();
		return;
	}	
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {	//Deep copy assignment operation
		this->clear();
		Node* tmp = rhs.head;
		while (tmp != NULL) {
			push_front(tmp->data);
			tmp = tmp->next;
		}
		this->reverse();
		return *this; 
	}	 
};
#endif //LINKED_LIST_H
