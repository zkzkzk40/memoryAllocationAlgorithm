#pragma once
#include "freeTable.h"
typedef freeTable ElemType;
class Node
{
public:
	ElemType data;
	Node* prior; //前趋指针
	Node* next;  //后继指针
	Node(int num, long address, long length, int state);
	Node(int num, long address, long length, int state, Node* pre,Node* nxt);
};

