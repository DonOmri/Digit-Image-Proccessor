#include "Matrix.h"


/*************Constructors and Destructor*************/

///Constructs a matrix filled with 0's
Matrix::Matrix(int rows, int cols)
    :_dims(), _data(nullptr)
{
  if(rows < MIN_ROW_NUM || cols < MIN_COL_NUM)
  {
    throw length_error(INIT_INPUT_ERR);
  }
  _data = new float*[rows];
  _dims.rows = rows;
  _dims.cols = cols;

  for(int i=0; i<_dims.rows;i++)
  {
    _data[i] = new float[_dims.cols];
    for(int j=0;j<_dims.cols;j++)
    {
      _data[i][j] =INITIAL_MATRIX_VAL;
    }
  }
}

///Constructs a matrix using an existing m matrix (copy constructor)
Matrix::Matrix(const Matrix& m)
    : Matrix (m._dims.rows,m._dims.cols)
{
  for(int i=0; i<_dims.rows;i++)
  {
    for(int j=0;j<_dims.cols;j++)
    {
      _data[i][j] = m._data[i][j];
    }
  }
}

Matrix::~Matrix()
{
  delete_data();
}

/*************Inner Functions*************/

///Transposes A given matrix (mirrors its cells around the (x,x) diagonal)
Matrix& Matrix::transpose ()
{
  auto* temp_data = new float[_dims.rows*_dims.cols];
  int temp_rows = _dims.rows;
  int temp_cols = _dims.cols;
  copy_delete_insert (temp_rows,temp_cols,temp_data);
  delete[] temp_data;
  return *this;
}

///Creates a vector from matrix rows
Matrix& Matrix::vectorize ()
{
  auto* tmp_data = new float[_dims.rows*_dims.cols];
  int temp_rows = _dims.rows*_dims.cols;
  int temp_cols = INIT_COL;
  copy_delete_insert (temp_rows,temp_cols,tmp_data);
  delete[] tmp_data;
  return transpose();
}

///Prints the matrix
void Matrix::plain_print () const
{
  for(int i=0; i<_dims.rows;i++)
  {
    for(int j=0;j<_dims.cols;j++)
    {
      cout << _data[i][j] << " ";
    }
    cout << endl;
  }
}

///Returns a new dot_matrix, with cells containing a(i,j)^2 for each i,j
Matrix Matrix::dot (const Matrix& m) const
{
  if(_dims.rows != m._dims.rows || _dims.cols != m._dims.cols)
  {
    throw length_error(LENGTH_ERR_A);
  }
  Matrix dot_matrix(_dims.rows, _dims.cols);
  for(int i=0; i<_dims.rows;i++)
  {
    for(int j=0;j<_dims.cols;j++)
    {
      dot_matrix._data[i][j] = _data[i][j] * m._data[i][j];
    }
  }
  return dot_matrix;
}

///Returns the square root of the sum of all matrix cells
float Matrix::norm () const
{
  float sum =0;
  for(int i=0; i<_dims.rows;i++)
  {
    for(int j=0;j<_dims.cols;j++)
    {
      sum += (_data[i][j]*_data[i][j]);
    }
  }
  return std::sqrt(sum);
}

/**************************
      Helper Functions
**************************/


///Helper function to delete the data
void Matrix::delete_data()
{
  for(int i=0;i<_dims.rows;i++)
  {
    delete[] _data[i];
  }
  delete[] _data;
}


/**Helper function to the vectorize and transpose: copies current data,
*** removes existing data from given matrix, and then creates the new matrix
*** with the given rows, cols and copied data.
**/
Matrix& Matrix::copy_delete_insert(int temp_rows, int temp_cols, float*
temp_data)
{
  for(int i=0; i<_dims.rows;i++)
  {
    for(int j=0;j<_dims.cols;j++)
    {
      temp_data[i*_dims.cols+j] = _data[i][j];
    }
  }

  delete_data();
  _dims.rows = temp_cols;
  _dims.cols = temp_rows;
  _data = new float*[_dims.rows];

  for(int i=0; i<_dims.rows;i++)
  {
    _data[i] = new float[_dims.cols];
    for(int j=0;j<_dims.cols;j++)
    {
      _data[i][j] = temp_data[j*temp_cols+i];
    }
  }
  return *this;
}

/*************Operators*************/

///adds each cell of matrix b to the correspondant cell in a given matrix
Matrix Matrix::operator+ (const Matrix& b) const
{
  if(_dims.rows != b.get_rows() || _dims.cols != b.get_cols())
  {
    throw length_error(LENGTH_ERR_A);
  }
  Matrix sum_mat(_dims.rows,_dims.cols);

  for(int i=0; i<_dims.rows;i++)
  {
    for(int j=0;j<_dims.cols;j++)
    {
      sum_mat._data[i][j] = _data[i][j] + b._data[i][j];
    }
  }
  return sum_mat;
}

///Copy assignment - changes data of a given matrix to other matrix' data
Matrix& Matrix::operator= (const Matrix& b)
{
  if(this != &b)
  {
    delete_data();
    _dims.rows = b._dims.rows;
    _dims.cols = b._dims.cols;
    _data = new float*[_dims.rows];

    for(int i=0; i<_dims.rows;i++)
    {
      _data[i] = new float[_dims.cols];
      for(int j=0;j<_dims.cols;j++)
      {
        _data[i][j] = b._data[i][j];
      }
    }
  }
  return *this;
}

///Returns a new matrix with the product of 2 matrices multiplication, as
/// learned in linear algebra I
Matrix Matrix::operator* (const Matrix& b) const
{
  if(_dims.cols != b.get_rows())
  {
    throw length_error(LENGTH_ERR_A);
  }
  Matrix mult(_dims.rows, b._dims.cols);
  for(int i=0; i<mult._dims.rows;i++)
  {
    for(int j=0;j<mult._dims.cols;j++)
    {
      for(int k=0;k<_dims.cols;k++)
      {
        mult._data[i][j] += (_data[i][k] * b._data[k][j]);
      }
    }
  }
  return mult;
}

///Returns a nex matrix which is the result of scalar multiplication with
/// matrix - SCALAR FROM THE RIGHT
Matrix Matrix::operator* (const float& b) const
{
  Matrix mult(_dims.rows, _dims.cols);
  for(int i=0; i<_dims.rows;i++)
  {
    for(int j=0;j<_dims.cols;j++)
    {
      mult._data[i][j] = _data[i][j] * b;
    }
  }
  return mult;
}

///Returns a nex matrix which is the result of scalar multiplication with
/// matrix - SCALAR FROM THE LEFT
Matrix operator* (const float& b,Matrix& m)
{
  return m*b;
}

///Adds matrix b to a given matrix, and changes the given matrix
Matrix& Matrix::operator+= (const Matrix& b)
{
  if(_dims.rows != b.get_rows() || _dims.cols != b.get_cols())
  {
    throw length_error(LENGTH_ERR_A);
  }
  for(int i=0; i<_dims.rows;i++)
  {
    for(int j=0;j<_dims.cols;j++)
    {
      _data[i][j] += b._data[i][j];
    }
  }
  return *this;
}

///Gets the data from the (i,j) cell - CONST VERSION
const float& Matrix::operator() (const int& i,const int& j) const
{
  if(i >= _dims.rows || i < 0 || j >= _dims.cols || j < 0)
  {
    throw out_of_range(OUT_OF_RANGE_ERR_A);
  }
  return _data[i][j];
}

///Gets the data from the (i,j) cell - NON CONST VERSION
float& Matrix::operator() (const int& i,const int& j)
{
  if(i >= _dims.rows || i < 0 || j >= _dims.cols || j < 0)
  {
    throw out_of_range(OUT_OF_RANGE_ERR_A);
  }
  return _data[i][j];
}

///Gets the data from the i'th cell, treating the matrix as a continuous
/// array - CONST VERSION
const float& Matrix::operator[] (const int& i) const
{
  if(i >= _dims.rows*_dims.cols || i < 0)
  {
    throw out_of_range(OUT_OF_RANGE_ERR_B);
  }
  return _data[(int) i/(_dims.cols)][i%(_dims.cols)];
}
///Gets the data from the i'th cell, treating the matrix as a continuous
/// array - NON CONST VERSION
float& Matrix::operator[] (const int& i)
{
  if(i >= _dims.rows*_dims.cols || i < 0)
  {
    throw out_of_range(OUT_OF_RANGE_ERR_B);
  }
  return _data[(int) i/(_dims.cols)][i%(_dims.cols)];
}

///Prints the matrix to a given output stream
std::ostream& operator<< (std::ostream& output,const Matrix& m)
{
  for(int i=0;i<m.get_rows();i++)
  {
    for(int j=0;j<m.get_cols();j++)
    {
      if(m(i,j) > BRIGHTNESS_BAR)
      {
        output << "**";
      }
      else
      {
        output << "  ";
      }
    }
    output << endl;
  }
  return output;
}

///Inserts given input stream to the matrix cells
std::istream& operator>> (istream& stream, const Matrix& m)
{
  long matrix_cells =(long) (m.get_rows()*m.get_cols()*sizeof(float));
  stream.seekg(0, std::ios_base::end);
  long file_size_bytes = stream.tellg();

  if(file_size_bytes != matrix_cells)
  {
    throw std::runtime_error(RUNTIME_ERR_A);
  }
  stream.seekg(0,std::ios_base::beg);

  for(int i=0; i<m.get_rows();i++)
  {
    if(!stream.read((char*) m._data[i],(long) (m.get_cols()*sizeof(float))))
    {
      throw runtime_error(RUNTIME_ERR_B);
    }

  }
  return stream;
}

