#include <stdio.h>
#include "DynamicAllocation.h"

int main()
{
	char *s;
	mm_init();
	s = (char*)mm_malloc(10);
	scanf("%s",s);
	printf("%s\n",s);
	return 0;
}
