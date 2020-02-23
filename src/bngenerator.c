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
#include <time.h>
#include <math.h>
#include <signal.h>

#include "integer.h"
#include "mpersistence.h"

/* global variable used in the program */
static u_int8_t continue_execution;

/**
 * Handler the quit (CTRL^C) signals and gracefully
 * start the program.
 */
void
signal_handler(int signal) {
    continue_execution = 0;
}

/**
 * ----------------------------------------------------------------------------
 *  Main script starts here
 * ----------------------------------------------------------------------------
 */
int
main(int argc, char* argv[])
{
    struct integer_t number;

    /* define signal handlers */
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    continue_execution = 1;
    for (init_integer(&number, 4); continue_execution; increment(&number)) {
        print_integer(&number);
    }

    free_integer(&number); 

    return 0; /* that's all folks */
}
