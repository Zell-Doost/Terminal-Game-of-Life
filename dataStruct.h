#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define BYTE_SIZE 8

typedef struct {
    size_t size;
    size_t capacity;
    uint8_t* data;
} BitVect;



BitVect* bit_vect_init(BitVect* bitVect, size_t capacity);

bool bit_vect_get(BitVect* bitVect, int index);

void bit_vect_set(BitVect* bitVect, int index, bool element);

void bit_vect_comp(BitVect* bitVect, int index);

void bit_vect_resize(BitVect* bitVect, size_t newSize);

void bit_vect_free(BitVect* bitVect);
