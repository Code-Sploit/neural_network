#include "layer.h"
#include "neuron.h"
#include "maths.h"

#include <stdlib.h>
#include <stdio.h>

layer_t *layer_create(int __size)
{
	layer_t *__layer = calloc(1, sizeof(layer_t));

	if (!__layer)
	{
		fprintf(stderr, "layer_create() failed with (s: %d)\n", __size);

		exit(1);
	}

	__layer->__size = __size;
	__layer->__neurons = (neuron_t**) calloc(__size, sizeof(neuron_t*));

	for (int i = 0; i < __size; i++)
	{
		__layer->__neurons[i] = (neuron_t*) calloc(1, sizeof(neuron_t));

		neuron_initialize_random(__layer->__neurons[i]);
	}

	return __layer;
}

layer_t *layer_create_null(int __size)
{
	layer_t *__layer = calloc(1, sizeof(layer_t));

	if (!__layer)
	{
		fprintf(stderr, "layer_create_null() failed with (s: %d)\n", __size);

		exit(1);
	}
	
	__layer->__size = __size;
	__layer->__neurons = (neuron_t**) calloc(__size, sizeof(neuron_t*));

	for (int i = 0; i < __size; i++)
	{
		__layer->__neurons[i] = (neuron_t*) calloc(1, sizeof(neuron_t));

		neuron_initialize_null(__layer->__neurons[i]);
	}

	return __layer;
}

layer_t *layer_create_output(int __start, int __end)
{
	layer_t *__layer = calloc(1, sizeof(layer_t));

	if (!__layer)
	{
		fprintf(stderr, "layer_create_output() failed with (s: %d | e: %d)\n", __start, __end);

		exit(1);
	}

	int __size = __end - __start;

	__layer->__size = __size;
	__layer->__neurons = (neuron_t**) calloc(__size, sizeof(neuron_t*));

	for (int i = __start; i < __end; i++)
	{
		__layer->__neurons[i] = (neuron_t*) calloc(1, sizeof(neuron_t));

		neuron_initialize_value(__layer->__neurons[i], (float) i);
	}

	return __layer;
}

void layer_delete(layer_t *__layer)
{
	if (!__layer)
	{
		fprintf(stdout, "layer_delete() warning deleting a NULL object\n");

		return;
	}

	free(__layer);
}

void layer_print(layer_t *__layer)
{
	if (!__layer)
	{
		fprintf(stdout, "layer_print() warning printing a NULL object\n");

		return;
	}

	printf("Printing Layer... [Size: %d]\n", __layer->__size);
	
	for (int i = 0; i < __layer->__size; i++)
	{
		float __activation = __layer->__neurons[i]->__activation;
		float __bias	   = __layer->__neurons[i]->__bias;

		printf("Neuron [%d] -> A: [%f] | B: [%f]\n", i, __activation, __bias);
	}

	printf("Finished Printing Layer!\n");
}

void layer_initialize_weights(layer_t *__layer)
{
	if (!__layer)
	{
		fprintf(stderr, "layer_initialize_weights() failed initializing a NULL object\n");

		exit(1);
	}

	for (int i = 0; i < __layer->__size; i++)
	{
		neuron_initialize_weights(__layer->__neurons[i]);
	}
}

void layer_print_weights(layer_t *__layer)
{
	if (!__layer)
	{
		fprintf(stdout, "layer_print_weights() warning printing a NULL object\n");

		return;
	}

	printf("Printing Layer Weights... [Size: %d]\n", __layer->__size);

	for (int i = 0; i < __layer->__size; i++)
	{
		neuron_t *__neuron = __layer->__neurons[i];

		for (int j = 0; j < __neuron->__nweights; j++)
		{
			printf("Neuron: [%d] | Weight Value: [%f]\n", i, __neuron->__weights[j]);
		}
	}

	printf("Finished Printing Layer Weights!\n");
}

void layer_calculate_single_activation(neuron_t *__neuron, layer_t *__previous, int __neuron_id)
{
	if (!__neuron || !__previous)
	{
		fprintf(stderr, "neuron_calculate_activation() failed neuron or previous layer is NULL\n");

		exit(1);
	}

	float __new_activation = 0.0f;

	for (int i = 0; i < __previous->__size; i++)
	{
		neuron_t *__previous_neuron = __previous->__neurons[i];

		__new_activation = (__new_activation + (__previous_neuron->__weights[__neuron_id] * __previous_neuron->__activation));
	}

	neuron_set_activation(__neuron, __new_activation);
}


void layer_calculate_activations(layer_t *__layer, layer_t *__previous)
{
	if (!__layer || !__previous)
	{
		fprintf(stderr, "layer_calculate_activations() failed layer(s) is NULL\n");

		exit(1);
	}

	for (int i = 0; i < __layer->__size; i++)
	{
		layer_calculate_single_activation(__layer->__neurons[i], __previous, i);
	}
}

void layer_print_lowest_cost(layer_t *__layer, layer_t *__target)
{
	if (!__layer || !__target)
	{
		fprintf(stderr, "layer_calculate_lowest_cost() failed layer(s) is NULL\n");

		exit(1);
	}

	float __lowest = 0.0f;

	int __index = 0;

	for (int i = 0; i < __layer->__size; i++)
	{
		float __cost = mse(__layer->__neurons[i]->__activation, __target->__neurons[i]->__activation);

		if (i == 0)
		{
			__lowest = __cost;

			continue;
		}

		if (__cost < __lowest)
		{
			__lowest = __cost;
			__index = i;
		}
	}

	printf("\n\nNeural Network Thinks: [%d]\n", __index);
}
