#include "Node.h"


Node::Node(int _num, long _address, long _length, int _state):data(_num,  _address,  _length,  _state)
{
	prior = nullptr;
	next = nullptr;
}

Node::Node(int num, long address, long length, int state, Node* pre, Node* nxt):Node(num, address, length, state)
{
	this->prior = pre;
	this->next = nxt;
}
