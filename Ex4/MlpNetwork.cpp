#include "MlpNetwork.h"



class Dense;
class Matrix;

MlpNetwork::MlpNetwork(const Matrix *weights,const Matrix *bias):layers{

  Dense (weights[0], bias[0], activation::relu),
  Dense (weights[1], bias[1], activation::relu),
  Dense (weights[2], bias[2], activation::relu),
  Dense (weights[3], bias[3], activation::softmax)
}{}

digit MlpNetwork::operator() (Matrix& x)
{
  x.vectorize();
  Matrix r1 = layers[0](x);
  Matrix r2 = layers[1](r1);
  Matrix r3 = layers[2](r2);
  Matrix r4 = layers[3](r3);
  float max_value = 0;
  unsigned int max_index = r4.argmax();
  for(int j=0;j<r4.get_rows();j++){
    if(r4[j]> max_value){
      max_value = r4[j];
    }
  }
  digit result{max_index,max_value};
  return result;
}

digit MlpNetwork::operator() (Matrix& y) const
{
  Matrix x = y;
  x.vectorize();
  Matrix r1 = layers[0](x);
  Matrix r2 = layers[1](r1);
  Matrix r3 = layers[2](r2);
  Matrix r4 = layers[3](r3);
  float max_value = 0;
  unsigned int max_index = r4.argmax();
  for(int j=0;j<r4.get_rows();j++){
    if(r4[j]> max_value){
      max_value = r4[j];
    }
  }
  digit result{max_index,max_value};
  return result;
}