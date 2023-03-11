// when compiling I have to use flag -lgsl, otherwise it doesn't work
#include <stdio.h>
#include <gsl/gsl_ieee_utils.h>
#include <math.h>

int main()
{
	// floats are 32bit
	float f = 1.12345678 * exp2(-124);

	for (size_t i = 0; i < 27; i++)
	{
		f/=2;
		gsl_ieee_printf_float(&f);
		printf("\n");
	}
	
	return 0;
}
