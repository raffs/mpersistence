/*
 * This file is part of the raffs/challenges.
 * Copyright (c) 2020 Rafael Oliveira Silva
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "integer.h"

/**
 * Given a pointer to integer_t struct, initialize the integer_t
 * struct and value with the given size and 0's in digits
 */
int
init_integer(struct integer_t *n, size_t size)
{
    if (n == NULL)
        return -1;

    /* define size of integer_t struct */
    n->size = size;

    /* alloc and initialize the integer value with 0's */
    n->value = (u_int8_t *) malloc(size * sizeof(u_int8_t));
    for (int i = 0; i < size; ++i)
        n->value[i] = 0;

    return 0;
}


/**
 * Given a pointer to integer_t print value of integer
 * on the standard output (STDOUT).
 */
void
print_integer(struct integer_t *n)
{
    if (n != NULL) {
        for (int i = 0; i < n->size; ++i)
            fprintf(stdout, "%d", n->value[i]);
        fprintf(stdout, "\n");
    }
}

/**
 * Given an integer, let's double the size of the integer_t
 * struct
 */
void
reinit_integer(struct integer_t *n)
{
    n->size = n->size + 1;
    n->value = realloc(n->value, n->size * sizeof(u_int8_t));

    if (n->size < 3) {
        n->value[0] = 1;
        for (int i = 1; i < n->size; i++)
            n->value[i] = 0;
    }
    else {
        n->value[0] = 2;
        for (int i = 1; i < n->size; i++)
            n->value[i] = 6;
    }
}

/**
 * increment the integer_t number to next valid value for
 * multiplicative persistence.
 *
 * Note: this increment function are optmized for the multiplicate
 * persistence problem, therefore the increment are more complex.
 */
void
increment(struct integer_t * n)
{
    for (long i = (n->size - 1); i >= 0; --i) {

        if (n->value[i] == 9) {
            /* if we hit only 9999's is time to double the number */
            if (i == 0) {
                reinit_integer(n);
                break; /* we double the size, let's move one */
            } 

            n->value[i] = (n->size > 2) ? 2 : 0;
            continue; /* we have carry on, let go to next round */
        }

        n->value[i] += 1;

        for (long j = 0; j < (n->size - 1); j++) {
            if (n->value[j] >  n->value[j + 1]) {
                n->value[j + 1] = n->value[i];  
            }
        }
        
        break; /* we finished the increment, we need to stop */
    }

    return;
}

/**
 * Compute the persistence of a integer_t.
 */
unsigned int 
compute_persistence(struct integer_t *n)
{
    unsigned int persistence = 0;
    unsigned long long int np = 1, product = 1;

    if (n->size < 2) return 0;
    persistence += 1;

    for (long i = 0; i < n->size; i++) {
        product = product * n->value[i]; 
    }

    for (; product > 9 ; persistence += 1) {
        np = product; 
        for (product = 1; np ; np /= 10) {
            product = product * (np % 10);
        }
    }

    return persistence;
}

/**
 * Given a pointer of integer_t struct, free
 * all the allocated (!= null) memory address
 */
inline void
free_integer(struct integer_t *n)
{
    if (n != NULL) free(n->value);
}
