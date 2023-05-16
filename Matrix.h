#include <cmath>
#include <iostream>

#ifndef MATRIX_H
#define MATRIX_H

#define INIT_COL 1
#define INIT_ROW 1
#define INITIAL_MATRIX_VAL 0
#define BRIGHTNESS_BAR 0.1
#define LENGTH_ERR_A "Matrices have different dimensions"
#define OUT_OF_RANGE_ERR_A "Given row or column is illegal"
#define OUT_OF_RANGE_ERR_B "Index is illegal"
#define INIT_INPUT_ERR "Given rows and columns must be bigger than 0"
#define RUNTIME_ERR_A "Given file and matrix have different number of floats"
#define RUNTIME_ERR_B "Could not read from input"
#define MIN_COL_NUM 1
#define MIN_ROW_NUM 1

using std::ifstream;
using std::istream;
using std::cout;
using std::endl;
using std::runtime_error;
using std::length_error;
using std::out_of_range;
using std::istream;
using std::ostream;

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;

class Matrix
{
 public:
  /*************Constructors and Destructor*************/
  Matrix(int rows, int cols);
  Matrix(): Matrix (INIT_ROW, INIT_COL) {};
  Matrix(const Matrix &m);
  ~Matrix();
  /*************Getters*************/
  long get_rows() const {return _dims.rows;}
  long get_cols() const {return _dims.cols;}
  /*************Inner Functions*************/
  Matrix& transpose();
  Matrix& vectorize();
  void plain_print() const;
  Matrix dot(const Matrix& m) const;
  float norm() const;
  /*************Operators*************/
  Matrix operator+(const Matrix& b) const;
  Matrix& operator=(const Matrix& b);
  Matrix operator*(const Matrix& b) const;
  Matrix operator*(const float& b) const;
  friend Matrix operator*(const float& b, Matrix& m);
  Matrix& operator+=(const Matrix& b);
  const float& operator()(const int& i,const int& j) const;
  float& operator()(const int& i,const int& j);
  const float& operator[](const int& i) const;
  float& operator[](const int& i);
  friend ostream& operator<<(ostream& output,const Matrix& m);
  friend istream& operator>>(istream& stream, const Matrix& m);

 private:
  matrix_dims _dims;
  float **_data;
  /*************Helper Functions*************/
  void delete_data();
  Matrix& copy_delete_insert(int temp_rows, int temp_cols,float* temp_data);
};

#endif //MATRIX_H