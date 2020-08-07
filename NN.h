#pragma once
#include "Matrix.h"
class NN
{

private:
	std::function<double(double)> d_sigmoid = [](double x){ return 1.0 / (1.0 + exp(-x)); };
	std::function<double(double)> d_dsigmoid = [](double x){ return x * (1.0 - x); };
	std::function<double(double)> d_tanh = [](double x){return tanh(x); };
	std::function<double(double)> d_dtanh = [](double x){return 1.0 / (x * x); };
	const int NumOfInputNodes;
	const int NumOfHiddenNodes;
	const int NumOfOutputNodes;
	std::shared_ptr<Matrix> weightsIH;
	std::shared_ptr<Matrix> weightsHO;

	std::shared_ptr<Matrix> biasH;
	std::shared_ptr<Matrix> biasO;


public:
	NN(const int a, const int b, const int c);
	std::vector<double> predict(const std::vector<double>& input);
	void train(const std::vector<double>& input, const std::vector<double>& target);

	~NN();
};

