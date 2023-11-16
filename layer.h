#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"

typedef struct layer_t
{
	int __size;

	neuron_t **__neurons;
} layer_t;

layer_t *layer_create(int __size);
layer_t *layer_create_null(int __size);
layer_t *layer_create_output(int __start, int __end);

void layer_delete(layer_t *__layer);
void layer_print(layer_t *__layer);

void layer_initialize_weights(layer_t *__layer);
void layer_print_weights(layer_t *__layer);

void layer_calculate_activations(layer_t *__target, layer_t *__previous);
void layer_calculate_single_activation(neuron_t *__neuron, layer_t *__previous, int __neuron_id);

void layer_print_lowest_cost(layer_t *__layer, layer_t *__target);

#endif
