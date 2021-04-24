#include "utils.h"

#include <stdio.h>


int Input_GetInt()
{
	int value;
	char str[10];
	gets_s(str, 10);
	sscanf_s(str, "%i", &value);

	return value;
}
