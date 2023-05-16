#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <cmath>

#define SOFT_MAX_MACRO (1/sum)
#define RELU_BAR 0
#define UNDER_RELU_BAR_RESULT 0


typedef Matrix (*Activation)(const Matrix& m);

namespace activation
{
    Matrix relu(const Matrix& m); ///relu function, formula in pdf
    Matrix softmax(const Matrix& m); ///softmax function, formula in pdf
}

#endif //ACTIVATION_H