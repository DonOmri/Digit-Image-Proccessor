#include "Activation.h"


using std::exp;

Matrix activation::relu(const Matrix& m)
{
  Matrix new_mat(m);
  for(int i=0; i<m.get_rows(); i++)
  {
    for(int j=0; j<m.get_cols(); j++)
    {
      if(new_mat(i,j) < RELU_BAR)
      {
        new_mat(i,j) = UNDER_RELU_BAR_RESULT;
      }
    }
  }
  return new_mat;
}

Matrix activation::softmax(const Matrix& m)
{
  float sum = 0;
  Matrix new_mat(m);
  for(int j=0; j<m.get_cols(); j++)
  {
    for(int i=0; i<m.get_rows(); i++)
    {
      sum += exp(m(i,j));
    }
    for(int i=0; i<m.get_rows(); i++)
    {
      new_mat(i,j) = exp(m(i,j));
      new_mat(i,j) *= SOFT_MAX_MACRO;
    }
  }
  return new_mat;
}

