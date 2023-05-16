#include "Dense.h"

Dense::Dense(const Matrix& weights, const Matrix& bias, Activation
ActivationFunction)
: _weights(weights),_bias(bias), _act_func(ActivationFunction) {}


Matrix Dense::operator() (const Matrix& input) const
{
  return _act_func((_weights*input) + _bias);
}

