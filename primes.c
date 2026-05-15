#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "bitvector.h"

double customLog(double x, double base) {
    return log(x)/log(base);
}

bool isFib(int n) {
  double test1 = pow(n, 2) * 5 + 4;
  double test2 = pow(n, 2) * 5 - 4;
  if (sqrt(test1) == (int)sqrt(test1) || sqrt(test2) == (int)(sqrt(test2))) {
    return true;}
    return false;
  }

bool isLucas(int n) {
  if (n < 1) {
    return false;}
  if (n == 1 || n == 2 || n == 3) {
    return true;}
  double goldenRatio = (1+sqrt(5))/2;
  double psi = (1 - sqrt(5))/2;
  int i = round(customLog(n, goldenRatio));
  int lucas = round(pow(goldenRatio,i) - pow(psi, i));
  return lucas == n;
}
bool isMersenne(int n) {
  double m = n + 1;
  if (m < 1) {
    return false;}

  while (m > 1){
    m = m/2;}

  if (m == 1){
    return true;}
  return false;
}

bool isPalindromeBase(int n, int b) {
    int digits[64];
    int len = 0;

    while (n > 0) {
        digits[len] = n % b;
        n /= b;
        len++;
    }

    for (int i = 0; i < len / 2; i++) {
        if (digits[i] != digits[len - 1 - i]) {
            return false;
        }
    }

    return true;
}

int returnDigits(int n, int b) {
    int result = 0;

    while (n > 0) {
        int digit = n % b;
        result = result * 10 + digit;
        n /= b;
    }

    return result;
}

void printPrimes(BitVector *bv) {
    uint32_t n = bvGetLen(bv);
    for (uint32_t i = 2; i < n; i++) {
        if (bvGetBit(bv, i)) {
            bool fib = isFib(i);
            bool lucas = isLucas(i);
            bool mers = isMersenne(i);
              printf("%u: prime", i);
            if (fib == 1) {
              printf(", fibonacci");}
            if (lucas == 1) {
              printf(", lucas");}
            if (mers == 1) {
              printf(", mersenne");}
            printf("\n");
        }
    }
}

void printPalindromes(BitVector *bv) {
  uint32_t n = bvGetLen(bv);
    printf("\nBase 2\n-----\n");
    for (uint32_t i = 2; i < n; i++) {
        if (bvGetBit(bv, i)) {
          bool truth = isPalindromeBase(i, 2);
          if (truth) {
            printf("%d = %d\n", i, returnDigits(i, 2));
          }
        }
      }
    printf("\nBase 9\n-----\n");
    for (uint32_t i = 2; i < n; i++) {
        if (bvGetBit(bv, i)) {
          bool truth = isPalindromeBase(i, 9);
          if (truth) {
            printf("%d = %d\n", i, returnDigits(i, 9));
          }
        }
      }
    printf("\nBase 10\n-----\n");
    for (uint32_t i = 2; i < n; i++) {
        if (bvGetBit(bv, i)) {
          bool truth = isPalindromeBase(i, 10);
          if (truth) {
            printf("%d = %d\n", i, returnDigits(i, 10));
          }
        }
      }
    printf("\nBase 27\n-----\n");
    for (uint32_t i = 2; i < n; i++) {
        if (bvGetBit(bv, i)) {
          bool truth = isPalindromeBase(i, 27);
          if (truth) {
            printf("%d = %d\n", i, returnDigits(i, 27));
          }
        }
      }
}

int main(int argc, char *argv[]) {
  int opt;
  bool primes = false;
  bool palins = false;
  int n = 0;
  while ((opt = getopt(argc, argv, "spn:")) != -1) {
    switch(opt) {
      case 's':
        primes = true;
        break;
      case 'p':
        palins = true;
        break;
      case 'n':
        n = atoi(optarg);
        break;
    }
  }
  if (n < 2) {return 1;}
  
  BitVector *bv = sievePrimes(n);
  if (primes) {
  printPrimes(bv);}
  if (palins) {
  printPalindromes(bv);}
  bvDelete(bv);
  return 0;
}