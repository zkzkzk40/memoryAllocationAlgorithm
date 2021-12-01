#include "freeTable.h"

freeTable::freeTable(int _num, long _address, long _length, int _state)
{
    this->num= _num;
    this->address = _address;
    this->length = _length;
    this->state = _state;
}
