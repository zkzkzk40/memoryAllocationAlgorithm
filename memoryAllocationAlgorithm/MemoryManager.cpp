#include "MemoryManager.h"

MemoryManager::MemoryManager(int _num, long _address, long _length, int _state)
{
	head = new Node(_num, _address, _length, _state);
}

MemoryManager::MemoryManager(long _length):MemoryManager(0,0,40,1)//假设操作系统本身占用40KB的容量
{
    if (_length <= 40) {
        cout << "分配的内存不足" << endl;
        exit(0);
    }
    maxLenth = _length;
    head->next = new Node(1, 40, maxLenth - 40, 0,head,0);
}

void MemoryManager::show()
{
    /*
    * 显示主存分配情况
    */
    int flag = 0;//用来记录分区序号
    Node* p=head;
    //sort();
    printf("\t\t》主存空间分配情况《\n");
    printf("**********************************************************\n");
    printf("分区序号\t起始地址\t分区大小\t分区状态\n");
    while (p)
    {
        printf("%d\t\t%d\t\t%dKB", p->data.num, p->data.address, p->data.length);
        if (p->data.state == 0) printf("\t\t空闲");
        else printf("\t\t已分配");
        cout << "\t\t";
        cout << endl;
        p = p->next;
    }
    printf("**********************************************************\n");
}

int MemoryManager::requestMemory(long memoryLen)
{
    return bestFit(memoryLen);
}

int MemoryManager::bestFit(long memoryLen)
{
    /// <summary>
    /// //最佳适配算法,选择内存空闲块中最适合进程大小的块分配
    /// 申请内存空间,返回申请到的内存空间地址,失败则返回-1
    /// </summary>
    /// <param name="memoryLen">要申请的内存长度</param>
    /// <returns></returns>
    Node* p = head->next,*reAllocateMemoryNode=p;
    while (p) {
        if (p->data.state==0) {
            if (p->data.length >= reAllocateMemoryNode->data.length) {
                reAllocateMemoryNode = p;
            }
        }
        p = p->next;
    }
    p = head;
    while (p) {
        if (p->data.state==0) {//空间空闲
            if (p->data.length > memoryLen && p->data.length <= reAllocateMemoryNode->data.length) {
                //当前指针节点的空间合适且比上次定位的指针节点空间小
                //则改变定位指针的位置
                reAllocateMemoryNode = p;
            }
        }
        p = p->next;
    }

    return allocateMemory(reAllocateMemoryNode, memoryLen);
    
}

void MemoryManager::freeMemory(int memoryNum)
{
    /// <summary>
    /// 释放内存
    /// </summary>
    /// <param name="memoryNum">要释放的内存的序号</param>
    if (memoryNum<=0) {
        cout << "不可以释放该内存" << endl;
        exit(1);
    }
    Node* p = head;
    while (p) {
        if (p->data.num == memoryNum) {
            p->data.state = 0;
            break;
        }
        p = p->next;
    }
    if (p == nullptr) {
        cout << "未找到该内存空间" << endl;
        exit(1);
    }
    /*内存释放完毕,下面开始合并上下内存
    分四种情况
    a.释放区下邻空闲区（低地址邻接）
    b.释放区上邻空闲区（高地址邻接）
    c.释放区上下都与空闲区邻接
    d.释放区上下邻都与空闲区不邻接*/
    if (p->next && p->next->data.state == 0) {//当释放区下邻空闲区（低地址邻接）
        p = p->next;//将p下移
    }
    while (p->prior && p->prior->data.state == 0) {
        //释放区上邻空闲区（高地址邻接）
        //下面的操作会将p和p前面的空间合并,并且循环直到p前面不为空闲区
        p->prior->data.length += p->data.length;
        p->prior->next = p->next;
        if (p->next) {
            p->next->prior = p->prior;
        }
        Node* temp = p;
        p = p->prior;
        delete temp;
    }
}

int MemoryManager::firstFit(long memoryLen)
{
    
    Node* reAllocateMemoryNode = head->next;
    while (reAllocateMemoryNode) {//找到第一个适配的内存空间
        if (reAllocateMemoryNode->data.state == 0) {
            if (reAllocateMemoryNode->data.length >= memoryLen) {
                break;
            }
        }
        reAllocateMemoryNode = reAllocateMemoryNode->next;
    }
    return allocateMemory(reAllocateMemoryNode, memoryLen);
}

int MemoryManager::maxFit(long memoryLen)
{
    Node* p = head->next, * reAllocateMemoryNode = p;
    while (p) {
        if (p->data.state == 0) {
            if (p->data.length >= reAllocateMemoryNode->data.length) {
                reAllocateMemoryNode = p;
            }
        }
        p = p->next;
    }
    return allocateMemory(reAllocateMemoryNode, memoryLen);
}

int MemoryManager::allocateMemory(Node* reAllocatedNode,long memoryLen)
{
    if (reAllocatedNode && reAllocatedNode->data.length < memoryLen) {
        cout << "内存不足以分配" << endl;
        exit(1);
    }
    //开始分配
    //这块指针节点将被分配成两部分,第一部分为被分配的空间,第二部分为未分配的空间
    nodeNum++;
    if (reAllocatedNode->data.length == memoryLen) {
        //如果被分配的空间大小和申请的空间大小相同,则直接改变状态即可
        reAllocatedNode->data.state = 1;
        reAllocatedNode->data.num = nodeNum;
        return nodeNum;
    }
    long nodeAddress = reAllocatedNode->data.address;
    Node* newNode = new Node(nodeNum, nodeAddress, memoryLen, 1, reAllocatedNode->prior, reAllocatedNode);
    //指针指向改变
    reAllocatedNode->data.address += memoryLen;
    reAllocatedNode->data.length -= memoryLen;
    reAllocatedNode->prior->next = newNode;
    reAllocatedNode->prior = newNode;
    return nodeNum;
}
