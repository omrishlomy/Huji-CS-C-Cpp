#include "Matrix.h"
#include <cmath>
#include <algorithm>
#define MATRIX_CANNOT_MULT "matrix dimensions do not match"
#define SHORT_STREAM_ERR "the input provided is too short"
#define FILE_OPEN_ERR "can't open the file"
#define INDEX_ERR "index out of range"
#define MIN_THRESHOLD 0.1


Matrix::Matrix(const Matrix &m):row(m.get_rows()),col(m.get_cols())//
{
  data = new float[row * col];
  for(int i=0;i<row*col;i++){
    data[i] = m[i];
  }
}

Matrix& Matrix::transpose()
{
  int trow = col;
  int tcol = row;
  Matrix transposed(trow,tcol);
  for( int rows=0;rows<row;rows++)
  {
    for( int cols=0;cols<col;cols++)
    {
      transposed.data[(cols*row) + rows] = data[(rows*col) + cols];
    }

  }
  for( int i=0;i<col*row;i++){data[i] = transposed.data[i];}
  int tmp=row;
  row = col;
  col = tmp;
  return *this;
}

Matrix& Matrix::vectorize()
{
  row = col*row;
  col = 1;
  return *this;
}
void Matrix::plain_print ()
{
  for( int r = 0;r< row;r++)
  {
    for( int c=0;c< col;c++)
    {
      std::cout << data[(col*r)+c] << " ";
    }
    std::cout << std::endl;
  }
}

Matrix Matrix::dot (const Matrix &B)
{
  if(B.col != col || B.row != row)
  {
    throw std::invalid_argument (MATRIX_CANNOT_MULT);
  }
  Matrix mult_mat(row,col);
  for(int i=0;i<row*col;i++){
    mult_mat[i] = data[i] * B.data[i];
  }
  return mult_mat;
}

float Matrix::norm()
{
  float sum =0;
  for (int r=0;r<row*col;r++){
      sum+= data[r]*data[r];
    }
  float sqr_sum = std::sqrt(sum);
  return sqr_sum;
}
Matrix Matrix::rref() const
{
  Matrix result(*this); // Create a copy of the current matrix
  int lead = 0;
  int row_count = result.get_rows();
  int column_count = result.get_cols();

  for (int r = 0; r < row_count; r++)
  {
    if (lead >= column_count){return result;}
    int i = r;
    while (result(i, lead) == 0)
    {
      i++;
      if (i == row_count)
      {
        i = r;
        lead++;
        if (column_count == lead){return result;}
      }
    }
    // Swap rows i and r
    for (int j = 0; j < column_count; j++)
    {
      float temp = result(i, j);
      result(i, j) = result(r, j);
      result(r, j) = temp;
    }
    // Normalize row r
    float div = result(r, lead);
    for (int j = 0; j < column_count; j++)
    {
      result(r, j) /= div;
    }
    // Eliminate lead column element in other rows
    for (int k = 0; k < row_count; k++)
    {
      if (k != r)
      {
        float mult = result(k, lead);
        for (int j = 0; j < column_count; j++)
        {
          result(k, j) -= result(r, j) * mult;
        }
      }
    }
    lead++;
  }
  return result;
}


unsigned int Matrix::argmax ()const
{
   unsigned int max_index = 0;
  float max_value = data[0];
     int index=1;
  for(;index<col*row;index++){
    if(data[index] > max_value){
      max_index=index;
      max_value= data[index];}
  }
  return max_index;
}

float Matrix::sum()const{
  float sum=0;
  for( int i=0;i<row*col;i++){
    sum+=data[i];
  }
  return sum;
}

Matrix& Matrix::operator+=(const Matrix &B)
{
  if(row != B.row || col !=B.col){
    throw std::invalid_argument (MATRIX_CANNOT_MULT);
  }
  for( int i=0;i<row*col;i++){
    data[i]+=B.data[i];}
  return *this;
  }
Matrix Matrix::operator+ (const Matrix &B)
{
  if(row != B.row || col !=B.col){
    throw std::invalid_argument (MATRIX_CANNOT_MULT);
  }
  Matrix sum(row,col);
  for( int i=0;i<row*col;i++){
    sum[i] = data[i]+B.data[i];}
  return sum;
}
Matrix& Matrix::operator=(const Matrix& B)
{
  if(this ==&B){return *this;}
  delete []data;
  col = B.col;
  row = B.row;
  data = new float[row*col];
  for(int i=0;i<row*col;i++){data[i] = B[i];}
  return *this;
}
Matrix Matrix::operator*(const Matrix& B) const
{
  if(col != B.row){
    throw std::invalid_argument (MATRIX_CANNOT_MULT);
  }
  Matrix mult_mat(row,B.col);
  for( int r=0;r<row;++r){
    for( int bc=0;bc<B.col;++bc){
      for( int c=0;c<col;++c)
      {
        mult_mat.data[(r*(B.col))+bc] += data[(r * (col)) + c] * B.data[
            (c*((B
                                                                     .col)))
                                                                    +bc];
      }
    }
  }
  return mult_mat;
}
Matrix Matrix::operator*(float c)const { //A*c
  Matrix scalar_mult(*this);
  for( int i=0;i<row*col;i++){scalar_mult[i]*=c;}
  return scalar_mult;
}
Matrix operator*(float c,const Matrix& B){//c*A
  Matrix scalar_mult(B);
  for( int i=0;i<B.row*B.col;i++){scalar_mult[i]*=c;}
  return scalar_mult;
}
float& Matrix::operator()( int rows, int cols){
  if(rows >= row || cols>=col || rows<0 || cols<0){
    throw std::out_of_range(INDEX_ERR);
  }
  return data[(rows*this->col) + cols];
}
const float& Matrix::operator()( int rows, int cols) const{
  if(rows >= row || cols>=col || rows<0 || cols<0){
    throw std::out_of_range(INDEX_ERR);
  }
  return data[(rows*this->col) + cols];
}
float& Matrix::operator[](int cell){
  if(cell >= row*col || cell<0){
    throw std::out_of_range(INDEX_ERR);
  }
  return data[cell];
}
const float& Matrix::operator[](int cell)const{
  if(cell >= row*col || cell<0){
    throw std::out_of_range(INDEX_ERR);
  }
  return data[cell];
}
std::ostream& operator<<(std::ostream &os,Matrix& A)
{
  for (int i =0;i<A.get_rows();i++){
    for(int j =0;j<A.get_cols();j++){
      if(A[i*A.get_cols() + j]>MIN_THRESHOLD){
       os << "**";}
      else{os << "  ";}
    }
    os<<std::endl;
    }
  return os;
  }


std::istream& operator>>(std::istream &is,Matrix &A){
  if(!is){throw std::runtime_error (FILE_OPEN_ERR);}
  is.read(reinterpret_cast<char*>(A.data),A.col*A.row*sizeof(float));
  //converting
  // the data type into char* for read and then converting back to float*
  if(!is){
    throw std::runtime_error (SHORT_STREAM_ERR);
  }
  return is;
}

