#include <iostream>
#include "MemoryManager.h"
//显示主存分配情况

int main()
{
    MemoryManager memoryManager(640);
    memoryManager.show();
    cout << "作业1申请130KB" << endl;
    int first = memoryManager.requestMemory(130);memoryManager.show();
    cout << "作业2申请60KB" << endl;
    int second = memoryManager.requestMemory(60);memoryManager.show();
    cout << "作业3申请100KB" << endl;
    int third = memoryManager.requestMemory(100);memoryManager.show();
    cout << "作业2释放60KB" << endl;
    memoryManager.freeMemory(second);            memoryManager.show();
    cout << "作业4申请200KB" << endl;
    int four = memoryManager.requestMemory(200);memoryManager.show();
    cout << "作业3释放100KB" << endl;
    memoryManager.freeMemory(third);             memoryManager.show();
    cout << "作业1释放130KB" << endl;
    memoryManager.freeMemory(first);             memoryManager.show();
    cout << "作业5申请140KB" << endl;
    int five = memoryManager.requestMemory(140); memoryManager.show();
    cout << "作业6申请60KB" << endl;
    int six = memoryManager.requestMemory(60); memoryManager.show();
    cout << "作业7申请50KB" << endl;
    int seven = memoryManager.requestMemory(70); memoryManager.show();
}

