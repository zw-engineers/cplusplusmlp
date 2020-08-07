#pragma once
#include <memory>
#include <iostream>
#include <time.h>
#include <functional>
#include <vector>
class Matrix
{
private:
	double* m_Data;
	const int m_NumOfRows;
	const int m_NumofCols;
	
public:
	Matrix(const int &, const int &);
	Matrix(const Matrix& other);
	Matrix operator+(const Matrix& other) const;
	Matrix operator+=(const Matrix& other) const;

	Matrix operator-(const Matrix& other) const;
	Matrix operator-=(const Matrix& other) const;

	static Matrix hadamard(const Matrix& a, const Matrix& b);
	void hadamard(const Matrix& a) const;
	Matrix operator*(const Matrix& other) const;
	Matrix dot(const Matrix& other) const;


	void ones() const;
	void  twos() const;
	void  randomize() const;
	void map(const std::function<double(double x)>& func) const;

	static Matrix fromArray(const std::vector<double>& arr);
	static Matrix transpose(const Matrix& other);
	static Matrix map(const Matrix& other ,const std::function<double(double x)>& func);

	std::vector<double> toArray();
	Matrix operator*(const double& other) const;


	~Matrix();
	void print();
};

