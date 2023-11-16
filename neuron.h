#ifndef NEURON_H
#define NEURON_H

typedef struct neuron_t
{
	float __activation;
	float __bias;
	float __dactivation;
	float __dbias;

	float *__weights;
	float *__dweights;

	int __nweights;
} neuron_t;

neuron_t *neuron_create(float __activation, float __bias, int __nweights);

void neuron_delete(neuron_t *__neuron);

void neuron_set_activation(neuron_t *__neuron, float __activation);
void neuron_set_bias(neuron_t *__neuron, float __bias);
void neuron_set_nweights(neuron_t *__neuron, int __nweights);

void neuron_initialize_random(neuron_t *__neuron);
void neuron_initialize_null(neuron_t *__neuron);
void neuron_initialize_value(neuron_t *__neuron, float __value);

void neuron_initialize_weights(neuron_t *__neuron);

#endif
