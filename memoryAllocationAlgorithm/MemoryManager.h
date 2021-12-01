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
	int requestMemory(long memoryLen);//申请内存空间,返回申请到的内存空间地址,失败则返回-1
	int bestFit(long memoryLen);//最佳适配算法
	void freeMemory(int memoryNum);//释放内存
	int firstFit(long memoryLen);//首次适配算法
	int maxFit(long memoryLen);
	int allocateMemory(Node* reAllocatedNode, long memoryLen);//分配内存
};

