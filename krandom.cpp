
#include "krandom.h"

#include <stdlib.h>

int rand_ex_i(int min, int max)
{
	if (min - max == 0)
		return 0 + min; // avoid zero division

	if (min > max)
	{
		int tmp;
		tmp = min;
		min = max;
		max = tmp;
	}

	return ( rand() % (max - min) ) + min;
}


// floating point version
float rand_ex_f(float min, float max)
{
	return ((float)rand_ex_i( (int)(min * 1000.0),(int)(max * 1000.0))) / 1000.0;
}


// version for switching the sign (positive, negative)
float rand_sign_switch(float number)
{
	if (rand()%100 < 50)
		return number;
	else
		return -number;
}


int rand_sign_switch(int number)
{
	if (rand()%100 < 50)
		return number;
	else
		return -number;
}
