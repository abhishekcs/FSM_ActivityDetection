#ifndef DLIST_H
#define DLIST_H

#include<iostream>
#include "include.h"

class node
{
	public:
	float wx;      	
	float wy;
	float wz;
	int frameIndex;
	node *next;    	
	node *prev;     
};

class dlist
{
	public:
	node *front;    
	node *back;     
	int size;

	dlist();
	int getsize();
	void insertFront(float x, float y, float z, int i);             
	void insertBack(float x, float y, float z, int i);
	void removeFront();
	void removeBack();
	void insertBefore(float x, float y, float z, int i, node *nodeB);
	void insertAfter(float x, float y, float z, int i, node *nodeA);
	void removeBefore(node *nodeB);
	void removeAfter(node *nodeA);
	void removeNode(node *newNode);
	void deleteall();
	void printDListFront();
	void printDListBack();
};

#endif
