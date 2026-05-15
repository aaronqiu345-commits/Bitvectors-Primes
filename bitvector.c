#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "bitvector.h"

BitVector *bvCreate(uint32_t bitLen) {
    BitVector *bv = malloc(sizeof(BitVector));
    if (!bv) {
        return NULL;}
    
    uint32_t byteLen = (bitLen + 7)/8;

    bv->vector = malloc(byteLen);
    if (!bv->vector) {
        free(bv);
        return NULL;}
    bv->length = bitLen;
    return bv;
}

void bvDelete(BitVector *v){
    free(v->vector);
    free(v);
}

uint32_t bvGetLen(BitVector*v) {
    return v->length;
}

void bvBitSet(BitVector *v, uint32_t i) {
    (v->vector[(i) / 8] |= (1 << ((i) % 8)));
}

void bvClearBit(BitVector *v, uint32_t i) {
    (v->vector[(i) / 8] &= ~(1 << ((i) % 8)));
}

uint8_t bvGetBit(BitVector *v, uint32_t i) {
    return (v->vector[(i) / 8] >> (i % 8)) & 1;
}

void bvSetAll(BitVector *v) {
    uint32_t byteLen = (v->length+7)/8;
    memset(v->vector, 0xFF, byteLen);
}

BitVector *sievePrimes(uint32_t n) {
    if (n < 2) return bvCreate(n+1);

    BitVector *bv = bvCreate(n+1);
    if (!bv) {return NULL;}
    bvSetAll(bv);

    if (bvGetLen(bv) > 0) {
        bvClearBit(bv, 0);}
    if (bvGetLen(bv) > 1) {
        bvClearBit(bv, 1);}

    uint32_t limit = (uint32_t)sqrt((double)n);

    for (uint32_t i = 2; i <= limit; i++) {
        if (bvGetBit(bv, i)){
            for (uint32_t multiple = i * i; multiple <= n; multiple += i) {
                bvClearBit(bv, multiple);
            }
        }
    }
    return bv;
}