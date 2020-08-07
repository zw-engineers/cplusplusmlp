#include "NN.h"


NN::NN(const int a, const int b, const int c):
NumOfInputNodes(a), NumOfHiddenNodes(b), NumOfOutputNodes(c), weightsIH(new Matrix(NumOfHiddenNodes, NumOfInputNodes)),
weightsHO(new Matrix(NumOfOutputNodes, NumOfHiddenNodes)), biasH(new Matrix(NumOfHiddenNodes, 1)), biasO(new Matrix(NumOfOutputNodes, 1))
{
	weightsIH->randomize();
	weightsHO->randomize();
	
	biasH->randomize();
	biasO->randomize();
}

std::vector<double> NN::predict(const std::vector<double>& input)
{
	Matrix inputs = Matrix::fromArray(input);
	Matrix hidden = *weightsIH * inputs;

	hidden += *biasH;
	hidden.map(d_sigmoid);

	Matrix output = *weightsHO * hidden;
	output += *biasO;
	output.map(d_sigmoid);

	return output.toArray();
}

void NN::train(const std::vector<double>& input, const std::vector<double>& target)
{

	Matrix inputs = Matrix::fromArray(input);
	Matrix hidden = *weightsIH * inputs;
	
	hidden += *biasH;
	hidden.map(d_sigmoid);

	Matrix output = *weightsHO * hidden;
	output += *biasO;
	output.map(d_sigmoid);
	Matrix targets = Matrix::fromArray(target);
	Matrix outputErrors = targets - output;

	Matrix gradients = Matrix::map(output, d_dsigmoid);

	gradients.hadamard(outputErrors);
	gradients * 0.1;

	Matrix hiddenTranpose = Matrix::transpose(hidden);
	Matrix weightsHoDeltas = gradients * hiddenTranpose;
	*weightsHO += weightsHoDeltas;
	
	*biasO += gradients;

	Matrix weightTranspose = Matrix::transpose(*weightsHO);
	Matrix hiddenErrors = weightTranspose * outputErrors;
	Matrix hiddenGradient = Matrix::map(hidden, d_dsigmoid);
	hiddenGradient.hadamard(hiddenErrors);
	hiddenGradient * 0.1;

	Matrix inputTranspose = Matrix::transpose(inputs);
	Matrix weightIHDeltas = hiddenGradient * inputTranspose;
	*weightsIH += weightIHDeltas;

	*biasH += hiddenGradient;
}

NN::~NN()
{
}
