#pragma once
#include"Node.h"
#include <iostream>
using namespace std;
class MemoryManager
{
private: 
	Node* head;
	int nodeNum=1;
	int maxLenth;
public:
	MemoryManager(int _num, long _address, long _length, int _state);
	MemoryManager(long _length);
	void show();
	int requestMemory(long memoryLen);//�����ڴ�ռ�,�������뵽���ڴ�ռ��ַ,ʧ���򷵻�-1
	int bestFit(long memoryLen);//��������㷨
	void freeMemory(int memoryNum);//�ͷ��ڴ�
	int firstFit(long memoryLen);//�״������㷨
	int maxFit(long memoryLen);
	int allocateMemory(Node* reAllocatedNode, long memoryLen);//�����ڴ�
};

