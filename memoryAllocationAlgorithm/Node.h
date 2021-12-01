#pragma once
#include "freeTable.h"
typedef freeTable ElemType;
class Node
{
public:
	ElemType data;
	Node* prior; //ǰ��ָ��
	Node* next;  //���ָ��
	Node(int num, long address, long length, int state);
	Node(int num, long address, long length, int state, Node* pre,Node* nxt);
};

