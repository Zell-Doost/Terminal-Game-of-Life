#include "dataStruct.h"

BitVect* bit_vect_init(BitVect* bitVect, size_t capacity)
{
    bitVect->capacity = capacity;
    bitVect->data = calloc(capacity / BYTE_SIZE + 1, sizeof(uint8_t));
    return bitVect;
}

bool bit_vect_get(BitVect* bitVect, int index)
{
    if (index < 0 || index >= bitVect->capacity) {
        //BAD VALUE, OUT OF BOUNDS
    }
    uint8_t neededByte = bitVect->data[index / BYTE_SIZE];
    bool neededBit = neededByte & (1 << index % BYTE_SIZE);
    return neededBit;
}

void bit_vect_set(BitVect* bitVect, int index, bool element)
{
    if (index < 0 || index >= bitVect->capacity) {
        //BAD VALUE, OUT OF BOUNDS
    }
    uint8_t* neededByte = bitVect->data + (index / BYTE_SIZE);
    if (element) 
        *neededByte |= (1 << index % BYTE_SIZE);
    else  
        *neededByte &= ~(1 << index % BYTE_SIZE);
}

void bit_vect_comp(BitVect* bitVect, int index)
{
    if (index < 0 || index >= bitVect->capacity) {
        //BAD VALUE, OUT OF BOUNDS
    }
    uint8_t* neededByte = bitVect->data + (index / BYTE_SIZE);
    *neededByte ^= (1 << index % BYTE_SIZE);
}

void bit_vect_resize(BitVect* bitVect, size_t newSize)
{
    bitVect->capacity = newSize;
    bitVect->data = realloc(bitVect->data, newSize);
}

void bit_vect_free(BitVect* bitVect)
{
    bitVect->capacity = 0;
    free(bitVect->data);
}
