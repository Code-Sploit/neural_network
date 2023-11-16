#ifndef MATHS_H
#define MATHS_H

#include "layer.h"

int sigmoid(int __z);
float mse(float __input, float __target);
float cost(layer_t *__layer, layer_t *__output);

#endif
