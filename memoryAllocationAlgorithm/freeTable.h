#pragma once
class freeTable
{
public:
    int num; //�������
    long address; //��ʼ��ַ
    long length;   //������С
    int state;   //����״̬ 0���� 1����
    freeTable(int num, long address, long length, int state);
};

