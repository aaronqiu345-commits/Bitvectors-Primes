#ifndef BITVECTOR_H
#define BITVECTOR_H

#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

typedef struct BitVector {
    uint8_t *vector;
    uint32_t length;
} BitVector;

BitVector *bvCreate(uint32_t bitLen);

void bvDelete(BitVector *v);

uint32_t bvGetLen(BitVector*v);

void bvBitSet(BitVector *v, uint32_t i);

void bvClearBit(BitVector *v, uint32_t i);

uint8_t bvGetBit(BitVector *v, uint32_t i);

void bvSetAll(BitVector *v);

BitVector *sievePrimes(uint32_t n);

#endif