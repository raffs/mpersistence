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
#include <signal.h>
#include <sys/stat.h>

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

void
pprint(struct integer_t *n, unsigned int p, double t)
{
    fprintf(stdout, "Minimum number of persistency %d is ", p);

    for (int i = 0; i < n->size; ++i)
        fprintf(stdout, "%d", n->value[i]);

    fprintf(stdout, " calculated in  %.6fs\n", t);
}

/**
 * Initialize the first number to start looking for the persistence
 * If the file LAST_FILE exists, than the number will be initialize
 * with the latest number.
 *
 * This should help recover from an unexpected exit, and help us
 * continue on our search.
 */
void initialize(struct integer_t *n)
{
    char c;
    FILE *fp;
    struct stat last_file;

    if (lstat(LAST_FILE, &last_file) != -1)
        fp = fopen(LAST_FILE, "r");

    /* in case we have an open file, let's initialize the number
     * from the value stored on the file and continue our search */
    if (fp != NULL) {
        init_integer(n, last_file.st_size);

        for (long long i = 0; (c = fgetc(fp)) != EOF; i++)
            n->value[i] = c - '0';

        fclose(fp);

        fprintf(stdout, "INFO: reading previous number: ");
        print_integer(n);

        return; /* our job is done here */
    }

    init_integer(n, 1);
    return; /* that's all folks */
}

/**
 * Given a number, write the number to a file on the path
 * LAST_FILE. This should help recovery from unexpected halt of
 * the system.
 */
void write_to_file(struct integer_t *n)
{
    FILE *fp;

    fp = fopen(LAST_FILE, "w");
    if (fp < 0)
        return; /* if we can't open the file, we should move on */

    for (int i = 0; i < n->size; ++i)
        fprintf(fp, "%d", n->value[i]);

    fclose(fp);
}

/**
 * Compute execution time with the small example from cs.tufts 111
 * http://www.cs.tufts.edu/comp/111/examples/Time/clock_gettime.c
 */
double
compute_time(struct timespec *start)
{
    struct timespec end;
    long seconds, nanoseconds;

    clock_gettime(CLOCK_REALTIME, &end);

    seconds = end.tv_sec - start->tv_sec;
    nanoseconds = end.tv_nsec - start->tv_nsec;

    if (start->tv_nsec > end.tv_nsec) { // clock underflow 
        seconds = seconds - 1;
        nanoseconds = nanoseconds + 1000000000;
    } 

    return (double)seconds + (double)nanoseconds / (double)1000000000;
}

/**
 * ----------------------------------------------------------------------------
 *  Main script starts here
 * ----------------------------------------------------------------------------
 */
int
main(int argc, char* argv[])
{
    double dtime;
    struct timespec start;
    struct integer_t number;
    unsigned int persistence;

    /* define signal handlers */
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    /* initialize the values */
    persistence = 0;
    continue_execution = 1;

    /* initialize the clock */
    clock_gettime(CLOCK_REALTIME, &start);

    lookfor_persistence_on(number, continue_execution) {
        if (compute_persistence(&number) == persistence) {
            dtime = compute_time(&start);
            pprint(&number, persistence, dtime);

            persistence = persistence + 1; /* let's move on to the next persistence */
        }
    }

    /* compute the end of the execution */
    dtime = compute_time(&start);
    fprintf(stdout, "\nDuration: %.3fs\n", dtime);

    write_to_file(&number);
    fprintf(stdout, "Last computed number: "); print_integer(&number);

    free_integer(&number); 

    return 0; /* that's all folks */
}
