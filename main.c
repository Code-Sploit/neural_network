#include "layer.h"
#include "neuron.h"
#include "mnist.h"
#include "maths.h"

int main(int argc, char** argv)
{
	load_mnist();

	layer_t *input_layer = layer_create_null(784);
	layer_t *hidden_layer_one = layer_create(16);
	layer_t *hidden_layer_two = layer_create(16);
	layer_t *output_layer = layer_create_null(9);
	layer_t *referention_layer = layer_create_output(0, 9);

	for (int i = 0; i < 784; i++)
	{
		neuron_set_activation(input_layer->__neurons[i], test_image[0][i]);
		neuron_set_nweights(input_layer->__neurons[i], 16);
	}

	for (int i = 0; i < 16; i++)
	{
		neuron_set_nweights(hidden_layer_one->__neurons[i], 16);
	}

	for (int i = 0; i < 16; i++)
	{
		neuron_set_nweights(hidden_layer_two->__neurons[i], 9);
	}

	layer_initialize_weights(input_layer);
	layer_initialize_weights(hidden_layer_one);
	layer_initialize_weights(hidden_layer_two);

	layer_calculate_activations(hidden_layer_one, input_layer);
	layer_print(hidden_layer_one);
	layer_calculate_activations(hidden_layer_two, hidden_layer_one);
	layer_calculate_activations(output_layer, hidden_layer_two);

//	layer_print(hidden_layer_one);
//	layer_print(hidden_layer_two);

	printf("This is a: [%d]\n", test_label[0]);
	printf("Testing cost function...\n");
	printf("Cost: [%f]\n", cost(output_layer, referention_layer));

	layer_print_lowest_cost(output_layer, referention_layer);

	return 0;
}
