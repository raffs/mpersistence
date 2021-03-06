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
#ifndef __MPERSISTENCE_PUZZLE_H
#define __MPERSISTENCE_PUZZLE_H

void signal_handler(int);
void pprint(struct integer_t *, unsigned int, double);
void write_to_file(struct integer_t *);
void initialize(struct integer_t *);
double compute_time(struct timespec *);

#define LAST_FILE ".last-computed-number"

#define lookfor_persistence_on(number, expr) \
    for (initialize(&number); expr; increment(&number))

#endif
