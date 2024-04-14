#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>
#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int16_t common;
    int16_t rare;
    int16_t epic;
} Booksset;

/**
 * @brief   initializes typedef of books set
*/
Booksset * createBookSet();

void checkInput(int * absNum);


Booksset * evolve(uint8_t from, uint8_t till);

Booksset * combineBooks(Booksset * bs1, Booksset * bs2, Booksset * bs3);

void printBooks(Booksset * books);

void subtract(Booksset * totalBooks, Booksset * ownedBooks);

void calculate(Booksset * demandedBooks, Booksset * ownedBooks);



#endif