#include <stdio.h>
#include "ulam.h"

int ulam_spiral_gen(char ***ulam_spiral_rtrn, bool *prime_list, int side_len)
{
	int i, j, k;
	int step_len = 1;
	int direction = X_POS;
	int step = 0;
	int square_size = side_len * side_len;
	char **ulam_spiral;

	if(side_len <= 0 || prime_list == NULL) {
		fprintf(stderr, "\nError: Could not parse arguments!\n");
		return ARG_ERROR;
	}

	if(!(ulam_spiral = malloc(sizeof(*ulam_spiral) * side_len))) {
		fprintf(stderr, "Error: Could not allocate memory!\n");
		return MEM_ERROR;
	}

	for(i = 0; i < side_len; i++) {
		if(!(ulam_spiral[i] = malloc(sizeof(*ulam_spiral) * side_len))) {
			while(i >= 0)
				free(ulam_spiral[i--]);
			free(ulam_spiral);

			fprintf(stderr, "Error: Could not allocate memory!\n");
			return MEM_ERROR;
		}
	}

	if(side_len % 2 == 0) { /* Determine where the starting position should be */
		j = (side_len / 2);
		i = j - 1;
	} else {
		i = j = ((side_len + 1) / 2) - 1;
	}

	for(k = 0; k < square_size; k++, step++) {
		ulam_spiral[j][i] = prime_list[k] ? '1' : '0';

		if(step == step_len) {
			if(direction == Y_NEG || direction == Y_POS)
				step_len++;

			direction = (direction < Y_NEG) ? direction + 1 : X_POS;
			step = 0;
		}

		switch(direction) {
			case X_POS:
				i++;
				break;
			case Y_POS:
				j--;
				break;
			case X_NEG:
				i--;
				break;
			case Y_NEG:
				j++;
				break;
			default:
				break;
		}
	}

	*ulam_spiral_rtrn = ulam_spiral;

	return EXEC_SUCCESS;
}

int ulam_write_file(char **ulam_spiral, int side_len, char *filename)
{
	FILE *file;

	if(!(file = fopen(filename, "wb")))
		return FILE_ERROR;

	fprintf(file, "P1 %d %d\n", side_len, side_len); /* Write PBM header */

	for(int i = 0; i < side_len; i++)
		fwrite(ulam_spiral[i], side_len, sizeof(**ulam_spiral), file);

	fclose(file);

	return EXEC_SUCCESS;
}