// Dense.h
#ifndef DENSE_H
#define DENSE_H
#include "Activation.h"

typedef Matrix (*activation_func) (const Matrix& x);



class Dense{
  public:
  Dense(const Matrix& weights,const Matrix& bias,activation_func activation):
  _weights(weights),_bias(bias),_activation(activation){}
  Matrix get_weights()const {return _weights;}
  Matrix get_bias()const {return _bias;}
  activation_func get_activation()const {return _activation;}
  Matrix operator()(Matrix& x);
  Matrix operator()(const Matrix& x)const;
  private:
  Matrix _weights;
  Matrix _bias;
  activation_func _activation;
};










#endif //DENSE_H