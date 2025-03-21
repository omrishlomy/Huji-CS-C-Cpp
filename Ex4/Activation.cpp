#include "Activation.h"
#include <cmath>
#include <algorithm>



namespace activation
{
    Matrix softmax (const Matrix &x)
    {
      Matrix soft_mat(x);
      float exp_sum = 0;
      for(int i = 0; i < (soft_mat.get_cols() * soft_mat.get_rows()); i++)
      {
        exp_sum += std::exp (soft_mat[i]);
        soft_mat[i] = std::exp (soft_mat[i]);
      }
      exp_sum = 1 / exp_sum;
      soft_mat = soft_mat * exp_sum;
      return soft_mat;
    }

    Matrix relu (const Matrix &x)
    {
      Matrix relu_mat(x);
      float zero = 0;
      for (int i = 0; i < relu_mat.get_rows() * relu_mat.get_cols(); i++)
      {
        relu_mat[i] = std::max(relu_mat[i], zero);
      }
      return relu_mat;
    }
}