#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList()
{
	head = NULL;
}	

LinkedList::~LinkedList()
{
	node *p, *q;
	p = head;
	if(p == NULL) return;
	while(p) {
		q = p->next;
		delete p;
		p = q;
	}
}

void LinkedList::add(Fan * d) 
{	
	this->size++;
	node *p, *q;
	if(head == NULL) {
		head = new node;
		head->data = * d;
		head->next = NULL;
		return;
	} 
	p = head;
	while(p->next != NULL) 
		p = p->next;
	q = new node;
	q->data = * d;
	q->next = NULL;
	p->next = q;
	tail = p->next;
}

void LinkedList::remove(Fan *f)
{
	node *p, *q;
	int flag = 0;
	if(head == NULL) {
		this->size--;
		return;	
	}
	p = head;
	while(p) {
		
		if(p->data == *f) {
			if (flag == 0) {
				
				q = head;
				head = head->next;
				delete q;
				this->size--;
				return;
			}
			q->next = p->next;
			delete p;
			this->size--;
			return;
		}
		q = p;
		p = p->next;
		flag = 1;
	}
}

void LinkedList::clear()
{
	node *p, *q;
	if(head == NULL) return;
	p = head;
	while(p) {
		q = p->next;
		delete p;
		if(q != head)  {
			head = NULL;
			return;
		}
		p = q;
	}
}

void LinkedList::display()
{
	node *p;
	if(head == NULL) return;
	p = head;
	while(p) {
		cout << p->data << endl;
		p = p->next;
		if(p != NULL) {
			if(p == head) return;
		}
	}
}

void LinkedList::find(string fanid, int dollars) {
	node *p;
	if(head == NULL) return;
	p = head;
	while(p) {
		if (p->data.GetPnum() == fanid || p->data.GetMail() == fanid) {
			p->data.SetConces(dollars);
			return;
		}
		p = p->next;
		if(p != NULL) {
			if(p == head) return;
		}
	}
}

bool LinkedList::Search(Fan f) {
	node *p;
	if (head == NULL) {
		return false;
	}
	p = head;
	while(p) {
		if (p->data == f) {
			return true;
		}
		p = p->next;
		if (p != NULL) {
			if (p == head) {
				return false;
			}
		}
	}
	return false;
}



Fan * LinkedList::GetFan() {
	return &(head->data);
}

Fan * LinkedList::GetT() {
	if (this->size == 1) {
		return &(head->data);
	}else{
		return &(tail->data);
	}
}

void LinkedList::iterate() {
	this->head = this->head->next;
}