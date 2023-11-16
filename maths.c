#include "maths.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int sigmoid(int __z)
{
	int __s = (1 / (1 + exp(-__z)));

	return __s;
}

float mse(float __input, float __target)
{
	float __e = powf((__input - __target), 2.0f);

	return __e;
}

float cost(layer_t *__output, layer_t *__targets)
{
	if (!__output || !__targets)
	{
		fprintf(stderr, "cost() failed __output or __targets is NULL\n");

		exit(1);
	}

	float __cost = 0.0f;

	for (int i = 0; i < __output->__size; i++)
	{
		float __reached = __output->__neurons[i]->__activation;
		float __target  = __targets->__neurons[i]->__activation;

		float __mse = mse(__reached, __target);

		printf("MSE Iteration: [%d]. Reached: [%f] | Target: [%f] with Value: [%f]\n", i, __reached, __target, __mse);

		__cost = (__cost + __mse);
	}

	__cost = (__cost / __output->__size);

	return __cost;
}
