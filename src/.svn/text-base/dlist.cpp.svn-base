#include "../include/dlist.h"

dlist::dlist()
{
	front = NULL;
	back = NULL;
	size = 0;
}

void dlist::insertBefore(float x, float y, float z, int i, node *nodeB)    
{
	node *newNode;
	newNode = new node();
	newNode->prev = nodeB->prev;
	newNode->next = nodeB;
	newNode->wx = x;
	newNode->wy = y;
	newNode->wz = z;
	newNode->frameIndex = i; 
	if (nodeB->prev == NULL)
		this->front = newNode; 
	nodeB->prev = newNode;
	size++;
}

void dlist::insertFront(float x, float y, float z, int i)
{
	node *newNode;
	if (this->front == NULL)
	{
		newNode = new node();
		this->front = newNode;
		this->back = newNode;
		newNode->prev = NULL;
		newNode->next = NULL;
		newNode->wx = x;
		newNode->wy = y;
		newNode->wz = z;
		newNode->frameIndex = i;
		size++;
	}
	else
		insertBefore(x, y, z, i, this->front);
}

void dlist::insertAfter(float x, float y, float z, int i, node *nodeB)
{
	node *newNode;
	newNode = new node();
	newNode->next = nodeB->next;
	newNode->prev = nodeB;
	newNode->wx = x;
	newNode->wy = y;
	newNode->wz = z;
	newNode->frameIndex = i;
	if (nodeB->next == NULL)
		this->back = newNode; 
	nodeB->next = newNode;
	size++;
}

void dlist::insertBack(float x, float y, float z, int i)
{          
	if (this->back == NULL)
		insertFront(x, y, z, i);
	else
		insertAfter(x, y, z, i, this->back);
}

void dlist::removeFront()
{
	ASSERT(this->front != NULL);
	removeNode(this->front);
}

void dlist::removeBack()
{
	ASSERT(this->back != NULL);
	removeNode(this->back);
}

void dlist::removeBefore(node *nodeB)
{
	if (nodeB->prev == this->front)
	{
		this->front = nodeB;
		this->front->prev = NULL;
		size--;
	}
	else
		removeNode(nodeB->prev);
}

void dlist::removeAfter(node *nodeA)
{
	if (nodeA->next == this->back)
	{
		this->back = nodeA;
		this->back->next = NULL;
		size--;
	}
	else
		removeNode(nodeA->next);
}

void dlist::removeNode(node *nodeToRemove)
{
	ASSERT(nodeToRemove != NULL);
	if (nodeToRemove == this->front)
	{
		this->front = this->front->next;
		this->front->prev = NULL;
	}
	else if (nodeToRemove == this->back)
	{
		this->back = this->back->prev;
		this->back->next = NULL ;
	}
	else
	{
		nodeToRemove->prev->next = nodeToRemove->next;
		nodeToRemove->next->prev = nodeToRemove->prev;
	}
	size--;
}

int dlist::getsize()
{
	return size;
}

void dlist::deleteall()
{
	front = NULL;
	back = NULL;
	size = 0;
}

void dlist::printDListFront()
{
	node* curr = this->front;
	while (curr != NULL)
	{
		cout << "|" << curr->wx << "|" << curr->wy << "|" << curr->wz << "|" << curr->frameIndex << "|\n";
		curr = curr->next;
	}
}

void dlist::printDListBack()
{
	node* curr = this->back;
	while (curr != NULL)
	{
		cout << "|" << curr->wx << "|" << curr->wy << "|" << curr->wz << "|" << curr->frameIndex << "|\n";
		curr = curr->prev;
	}
}
