#include "ulam.h"

int prime_sieve(bool **prime_list_rtrn, unsigned int field)
{
	bool *prime_list;
	unsigned int i, j;
	register unsigned int product;
	
	if(!(prime_list = malloc(sizeof(*prime_list) * field)))
		return MEM_ERROR;

	for(i = 0; i < field; i++)
		prime_list[i] = true;

	for(i = 2; i <= field; i++)
		for(j = 2; (product = j * i) <= field; j++)
			prime_list[product - 1] = false;

	*prime_list_rtrn = prime_list;

	return EXEC_SUCCESS;
}