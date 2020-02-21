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
#ifndef __MPERSISTENCE_INTEGER_H
#define __MPERSISTENCE_INTEGER_H

// define the buffer in which the INTEGER_BUFFER will grow
#define INTEGER_SIZE 2

struct integer_t
{
    /* define the size of the integer (in amount of digits) */
    size_t size;

    /**
     * The integer number represented as an array of unsigned 8 bites
     * digits. This allows the program to handle large numbers that
     * are not possible with the current basic types.
     */
    u_int8_t *value;
};

/* function prototypes */
int  init_integer (struct integer_t *, size_t);
void reinit_integer (struct integer_t *);
void free_integer (struct integer_t *);
void print_integer (struct integer_t *);
void increment (struct integer_t *);
unsigned int compute_persistence (struct integer_t *);

#endif
