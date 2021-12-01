#include "MemoryManager.h"

MemoryManager::MemoryManager(int _num, long _address, long _length, int _state)
{
	head = new Node(_num, _address, _length, _state);
}

MemoryManager::MemoryManager(long _length):MemoryManager(0,0,40,1)//�������ϵͳ����ռ��40KB������
{
    if (_length <= 40) {
        cout << "������ڴ治��" << endl;
        exit(0);
    }
    maxLenth = _length;
    head->next = new Node(1, 40, maxLenth - 40, 0,head,0);
}

void MemoryManager::show()
{
    /*
    * ��ʾ����������
    */
    int flag = 0;//������¼�������
    Node* p=head;
    //sort();
    printf("\t\t������ռ���������\n");
    printf("**********************************************************\n");
    printf("�������\t��ʼ��ַ\t������С\t����״̬\n");
    while (p)
    {
        printf("%d\t\t%d\t\t%dKB", p->data.num, p->data.address, p->data.length);
        if (p->data.state == 0) printf("\t\t����");
        else printf("\t\t�ѷ���");
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
    /// //��������㷨,ѡ���ڴ���п������ʺϽ��̴�С�Ŀ����
    /// �����ڴ�ռ�,�������뵽���ڴ�ռ��ַ,ʧ���򷵻�-1
    /// </summary>
    /// <param name="memoryLen">Ҫ������ڴ泤��</param>
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
        if (p->data.state==0) {//�ռ����
            if (p->data.length > memoryLen && p->data.length <= reAllocateMemoryNode->data.length) {
                //��ǰָ��ڵ�Ŀռ�����ұ��ϴζ�λ��ָ��ڵ�ռ�С
                //��ı䶨λָ���λ��
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
    /// �ͷ��ڴ�
    /// </summary>
    /// <param name="memoryNum">Ҫ�ͷŵ��ڴ�����</param>
    if (memoryNum<=0) {
        cout << "�������ͷŸ��ڴ�" << endl;
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
        cout << "δ�ҵ����ڴ�ռ�" << endl;
        exit(1);
    }
    /*�ڴ��ͷ����,���濪ʼ�ϲ������ڴ�
    ���������
    a.�ͷ������ڿ��������͵�ַ�ڽӣ�
    b.�ͷ������ڿ��������ߵ�ַ�ڽӣ�
    c.�ͷ������¶���������ڽ�
    d.�ͷ��������ڶ�����������ڽ�*/
    if (p->next && p->next->data.state == 0) {//���ͷ������ڿ��������͵�ַ�ڽӣ�
        p = p->next;//��p����
    }
    while (p->prior && p->prior->data.state == 0) {
        //�ͷ������ڿ��������ߵ�ַ�ڽӣ�
        //����Ĳ����Ὣp��pǰ��Ŀռ�ϲ�,����ѭ��ֱ��pǰ�治Ϊ������
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
    while (reAllocateMemoryNode) {//�ҵ���һ��������ڴ�ռ�
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
        cout << "�ڴ治���Է���" << endl;
        exit(1);
    }
    //��ʼ����
    //���ָ��ڵ㽫�������������,��һ����Ϊ������Ŀռ�,�ڶ�����Ϊδ����Ŀռ�
    nodeNum++;
    if (reAllocatedNode->data.length == memoryLen) {
        //���������Ŀռ��С������Ŀռ��С��ͬ,��ֱ�Ӹı�״̬����
        reAllocatedNode->data.state = 1;
        reAllocatedNode->data.num = nodeNum;
        return nodeNum;
    }
    long nodeAddress = reAllocatedNode->data.address;
    Node* newNode = new Node(nodeNum, nodeAddress, memoryLen, 1, reAllocatedNode->prior, reAllocatedNode);
    //ָ��ָ��ı�
    reAllocatedNode->data.address += memoryLen;
    reAllocatedNode->data.length -= memoryLen;
    reAllocatedNode->prior->next = newNode;
    reAllocatedNode->prior = newNode;
    return nodeNum;
}
