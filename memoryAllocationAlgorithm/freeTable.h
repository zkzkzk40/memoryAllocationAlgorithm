#pragma once
class freeTable
{
public:
    int num; //分区序号
    long address; //起始地址
    long length;   //分区大小
    int state;   //分区状态 0空闲 1分配
    freeTable(int num, long address, long length, int state);
};

