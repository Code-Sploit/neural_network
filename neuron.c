#include "neuron.h"

#include <stdlib.h>
#include <stdio.h>

neuron_t *neuron_create(float __activation, float __bias, int __nweights)
{
	neuron_t *__neuron = calloc(1, sizeof(neuron_t));

	if (!__neuron)
	{
		fprintf(stderr, "neuron_create() failed with (a: %f, b: %f\n", __activation, __bias);

		exit(1);
	}

	__neuron->__activation = __activation;
	__neuron->__bias       = __bias;
	__neuron->__nweights   = __nweights;

	return __neuron;
}

void neuron_delete(neuron_t *__neuron)
{
	if (!__neuron)
	{
		fprintf(stdout, "neuron_delete() warning deleting a NULL object\n");

		return;
	}

	free(__neuron);
}

void neuron_set_activation(neuron_t *__neuron, float __activation)
{
	if (!__neuron)
	{
		fprintf(stderr, "neuron_set_activation() failed with [v: %f] neuron is NULL!\n");

		exit(1);
	}

	__neuron->__activation = __activation;
}

void neuron_set_bias(neuron_t *__neuron, float __bias)
{
	if (!__neuron)
	{
		fprintf(stderr, "neuron_set_bias() failed with [v: %f] neuron is NULL!\n");

		exit(1);
	}

	__neuron->__bias = __bias;
}

void neuron_set_nweights(neuron_t *__neuron, int __nweights)
{
	if (!__neuron)
	{
		fprintf(stderr, "neuron_set_nweights() failed with [v: %d] neuron is NULL!\n", __nweights);

		exit(1);
	}

	__neuron->__nweights = __nweights;
}

void neuron_initialize_random(neuron_t *__neuron)
{
	if (!__neuron)
	{
		fprintf(stderr, "neuron_initialize_random() failed neuron is NULL\n");

		exit(1);
	}

	float __random_activation = (float) rand() / (float) (RAND_MAX / 1.0f);
	float __random_bias	  = (float) rand() / (float) (RAND_MAX / 1.0f);

	__neuron->__activation = __random_activation;
	__neuron->__bias       = __random_bias;

//	printf("Initializing Neuron -> A: [%f] | B: [%f]\n", __neuron->__activation, __neuron->__bias);
}

void neuron_initialize_null(neuron_t *__neuron)
{
	if (!__neuron)
	{
		fprintf(stderr, "neuron_initialize_null() failed neuron is NULL\n");

		exit(1);
	}

	__neuron->__activation = 0.0f;
	__neuron->__bias       = 0.0f;

//	printf("Initializing Neuron -> A: [%f] | B: [%f]\n", 0.0f, 0.0f);
}

void neuron_initialize_value(neuron_t *__neuron, float __value)
{
	if (!__neuron)
	{
		fprintf(stderr, "neuron_initialize_value() failed with [v: %f] neuron is NULL\n", __value);

		exit(1);
	}

	__neuron->__activation = __value;
	__neuron->__bias       = 0.0f;

	printf("Initializing Neuron -> A: [%f] | B: [%f]\n", __value, 0.0f);
}

void neuron_initialize_weights(neuron_t *__neuron)
{
	if (!__neuron)
	{
		fprintf(stderr, "neuron_initialize_weights() failed neuron is NULL\n");

		exit(1);
	}

	__neuron->__weights = (float*) calloc(__neuron->__nweights, sizeof(float));

	for (int i = 0; i < __neuron->__nweights; i++)
	{
		float __rnumber = (float) rand() / (float) (RAND_MAX / 1.0f);

		__neuron->__weights[i] = __rnumber;
	}
}
