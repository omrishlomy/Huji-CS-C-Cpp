// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"

class Matrix;

namespace activation{
      Matrix softmax(const Matrix &x);
      Matrix relu(const Matrix &x);

}











#endif //ACTIVATION_H