#include <stdio.h>
#include <stdlib.h>	/* rand */
#include <assert.h> 	/* assert */

#include "knights_tour.h"

int main(void)
{
	unsigned char *path = (unsigned char *)calloc(65, sizeof(unsigned char));
	size_t index = 0;

	assert(path);

	for(index = 0; index < 64; index++)
	{
		printf("Looking for path... index %ld\n", index);
		KnightsTour(index, path);
	}

	free(path);

	return 0;
}

