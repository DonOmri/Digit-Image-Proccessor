#include "MlpNetwork.h"


MlpNetwork::MlpNetwork (Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE])
:_layers{Dense(weights[FIRST_LAYER],biases[FIRST_LAYER], relu),
         Dense(weights[SECOND_LAYER],biases[SECOND_LAYER], relu),
         Dense(weights[THIRD_LAYER],biases[THIRD_LAYER], relu),
         Dense(weights[FOURTH_LAYER],biases[FOURTH_LAYER], softmax)} {}


digit MlpNetwork::operator() (Matrix& img) const
{
  for(int i=0; i<=LAST_MLP_INDEX; i++)
  {
    img = _layers[i](img);
  }

  digit max = {INIT_VAL,INIT_PROB};
  for(int i=SMALLEST_DIGIT;i<=BIGGEST_DIGIT; i++)
  {
    if(img(i,SINGLE_COL) > max.probability)
    {
      max.value = i;
      max.probability = img(i,SINGLE_COL);
    }
  }
  return {max.value, max.probability};
}

