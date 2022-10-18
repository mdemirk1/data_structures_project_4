#ifndef LinkedList_H
#define LinkedList_H

#include <iostream>
#include <string>
#include "Fan.h"

using namespace std;

class LinkedList
{
private:
	struct node
	{
		Fan data;
		node * next;
	} *head, *tail;

public:
	int size = 0;
	void find(string fanid, int dollars);
	bool Search(Fan f);
	LinkedList();
	~LinkedList();
	void add(Fan * d);
	void remove(Fan *f);
	void clear();
	void display();
	Fan * GetFan();
	Fan * GetT();
	void iterate();
};

#endif