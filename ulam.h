#ifndef ULAM_H
#define ULAM_H

#include <stdlib.h>
#include <stdbool.h>

#define EXEC_SUCCESS 0
#define MEM_ERROR -1
#define ARG_ERROR -2
#define ULAM_ERROR -3
#define FILE_ERROR -4

#define X_POS 1
#define Y_POS 2
#define X_NEG 3
#define Y_NEG 4

int prime_sieve(bool **prime_list_rtrn, unsigned int field);					/* Sieve of eratosthenes */
int ulam_spiral_gen(char ***ulam_spiral_rtrn, bool *prime_list, int side_len);	/* Convert a list of primes to a corresponding spiral arrangement */
int ulam_write_file(char **ulam_spiral, int side_len, char *filename);			/* Create a PBM file containing the generated ulam spiral */

#endif