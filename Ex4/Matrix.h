// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include <string>
#include <iostream>











// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims {
    int rows, cols;
};


class Matrix
{
 private:
  int row, col;
  float *data;

 public:
  Matrix (int rows, int cols) : row (rows), col (cols)
  {
    data = new float[row * col]{0};
  }
  Matrix () : Matrix (1,1){}
  Matrix (const Matrix &m);
  int get_rows () const
  { return row; }
  int get_cols () const
  { return col; }
  ~Matrix ()
  { delete[] data; }
  Matrix &transpose ();
  Matrix& vectorize ();
  void plain_print ();
  Matrix dot (const Matrix& B);
  float norm ();
  Matrix rref () const;
  unsigned int argmax ()const;
  float sum ()const;
  Matrix &operator+= (const Matrix &B);
  Matrix operator* (float c) const;
  Matrix& operator= (const Matrix &B);
  Matrix operator* (const Matrix &B)const;
  Matrix operator + (const Matrix &B);
  friend Matrix operator* (float c, const Matrix &B);
  float &operator() (int row, int col);
  const float &operator() (int row, int col) const;
  float &operator[] (int cell);
  const float& operator[] (int cell) const;
  friend std::ostream& operator<< (std::ostream &os,Matrix& A);
  friend std::istream& operator>> (std::istream &is,Matrix& A);
};



#endif //MATRIX_H