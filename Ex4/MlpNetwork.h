// MlpNetwork.h
#ifndef MLPNETWORK_H
#define MLPNETWORK_H
#include "Dense.h"




class Dense;
class Matrix;


#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

class MlpNetwork{
 public:
  MlpNetwork(const Matrix weights[MLP_SIZE],const Matrix bias[MLP_SIZE]);
  digit operator()(Matrix& x);
  digit operator()(Matrix& x) const;
 private:
  Dense layers[MLP_SIZE];
};

#endif // MLPNETWORK_H