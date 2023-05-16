#include "Dense.h"

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#define MLP_SIZE 4
#define LAST_MLP_INDEX (MLP_SIZE -1)
#define SMALLEST_DIGIT 0
#define BIGGEST_DIGIT 9
#define INIT_VAL 0
#define INIT_PROB img[0]
#define SINGLE_COL 0
#define FIRST_LAYER 0
#define SECOND_LAYER 1
#define THIRD_LAYER 2
#define FOURTH_LAYER 3

using activation::relu;
using activation::softmax;

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};


class MlpNetwork
{
 public:
  ///Constructs a network with 4 dense layers
  MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]);

  ///Runs the layers on a given matrix, and returns the most probable digit
  /// the network recognized
  digit operator()(Matrix& img) const;
 private:
  Dense _layers[MLP_SIZE];
};

#endif // MLPNETWORK_H