#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"


class Dense
{
 public:

  ///Constructs a layer with a weight and bias matrices, and either relu or
  /// softmax functions
  Dense(const Matrix& weights, const Matrix& bias, Activation
  ActivationFunction);

  ///Returns the weights matrix of the layer
  const Matrix& get_weights() const {return _weights;}

  ///Returns the bias matrix of the layer
  const Matrix& get_bias() const {return _bias;}

  ///Returns the activation function (relu / softmax( of the layer
  Activation get_activation() const {return _act_func;}

  ///Returns the result of the activation function on the layers' weights,
  /// and bias matrices, and given input
  Matrix operator()(const Matrix& input) const;
 private:
  Matrix _weights;
  Matrix _bias;
  Activation _act_func;
};

#endif //DENSE_H
