#include "Dense.h"

Matrix Dense::operator()(Matrix& x)
{
  return _activation(_weights*x + _bias);
}

Matrix Dense::operator()(const Matrix& x) const{
  Matrix y(x.get_rows(),x.get_cols());
  y=x;
  return _activation(_weights*y + _bias);
}