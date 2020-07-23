/* 
 * Filename:	main.c
 * Version:		0.1
 * Author:		Jess Turner
 * Date:		9-AUG-2016
 * Licence:		GNU GPL V3
 *
 * Ulam spiral generator
 * 
 * Todo:
 *		- Standardise error handling
 *		- Upgrade PBM file to PNG to reduce size
 *		- Improve/add argument handling
 */

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "ulam.h"

int main(int argc, char *argv[])
{
	char *file_name;
	long side_len;
	bool *prime_list = NULL;
	char **ulam_spiral = NULL;

	if(argc < 3) {
		fprintf(stderr, "usage: %s square_size file_name\n", argv[0]);
		return ARG_ERROR;
	}

	if(!(side_len = strtol(argv[1], NULL, 10)) || side_len <= 0) { /* Temporarily use side_len to hold the user approximated value for the size of the square */
		fprintf(stderr, "Error: Invalid arguments!\n");
		return ARG_ERROR;
	}

	if(!(file_name = malloc(strlen(argv[2])))) {
		fprintf(stderr, "Error: Could not allocate memory!\n");
		return MEM_ERROR;
	}

	strcpy(file_name, argv[2]);

	side_len = (int) ceil(sqrt(side_len)); /* Convert the user given value into a side length of the largest approximate square */

	printf("Square size set to %ld...\n", side_len * side_len);
	printf("Generating primes... ");
	fflush(stdout);

	if(prime_sieve(&prime_list, side_len * side_len) != EXEC_SUCCESS) {
		free(file_name);

		fprintf(stderr, "Error: Could not allocate memory!\n");
		return MEM_ERROR;
	}

	printf("Done!\n");

	printf("Generating ulam spiral... ");
	fflush(stdout);

	if(ulam_spiral_gen(&ulam_spiral, prime_list, side_len) != EXEC_SUCCESS) {
		free(prime_list);
		free(file_name);

		fprintf(stderr, "Error: Could not generate spiral!\n");

		return ULAM_ERROR;
	}

	printf("Done!\n");

	printf("Writing to file... ");
	fflush(stdout);

	if(ulam_write_file(ulam_spiral, side_len, argv[2]) != EXEC_SUCCESS) {
		fprintf(stderr, "Error: Could not write to file \"%s\"\n", argv[2]);
		
		while(--side_len >= 0)
			free(ulam_spiral[side_len]);
		
		free(file_name);
		free(prime_list);
		free(ulam_spiral);

		return FILE_ERROR;
	}
		
	printf("Done!\n");

	for(int i = side_len - 1; i >= 0; i--)
		free(ulam_spiral[i]);

	free(file_name);
	free(prime_list);
	free(ulam_spiral);

	return EXEC_SUCCESS;
}