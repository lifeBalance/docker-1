#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	*ptr;

	ptr = (char *)malloc(strlen("hello world") + 1);
	printf("%s\n", ptr);

	return (0);
}
