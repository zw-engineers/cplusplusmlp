#include "Matrix.h"


Matrix::Matrix(const Matrix& other) : m_NumOfRows(other.m_NumOfRows), m_NumofCols(other.m_NumofCols)
{
	m_Data = new double[other.m_NumOfRows * other.m_NumofCols];
	memcpy(m_Data, other.m_Data, sizeof(double) * other.m_NumOfRows * other.m_NumofCols);
}

Matrix::Matrix(const int &rows, const int &cols) :
m_NumOfRows(rows), m_NumofCols(cols), m_Data(new double[rows * cols])
{
	for (int i = 0; i < m_NumOfRows * m_NumofCols; i++)
	{
		m_Data[i] = 0;
	}
}

void Matrix::ones() const
{
	for (int i = 0; i < m_NumOfRows * m_NumofCols; i++)
	{
		m_Data[i] = 1;
	}
}


void Matrix::map(const std::function<double(double x)>& func) const
{
	for (int r = 0; r < m_NumOfRows; r++)
	{
		for (int c = 0; c < m_NumofCols; c++)
		{
			m_Data[r + c * m_NumOfRows] = func(m_Data[r + c * m_NumOfRows]);
		}
	}
}


void Matrix::randomize() const
{
	srand((unsigned int)time(0));
	for (int i = 0; i < m_NumOfRows * m_NumofCols; i++)
	{
		m_Data[i] = cos(sin(rand()));
	}
}

void Matrix::twos() const
{
	for (int i = 0; i < m_NumOfRows * m_NumofCols; i++)
	{
		m_Data[i] = 2;
	}
}


Matrix Matrix::operator+(const Matrix& other) const
{
	Matrix result(m_NumOfRows, other.m_NumofCols);
	for (int r = 0; r < result.m_NumOfRows; r++)
	{
		for (int c = 0; c < result.m_NumofCols; c++)
		{
			result.m_Data[r + c * m_NumOfRows] = m_Data[r + c * m_NumOfRows] + other.m_Data[r + c * other.m_NumOfRows];
		}
	}
	return result;
}

Matrix Matrix::operator+=(const Matrix& other) const
{
	for (int r = 0; r < m_NumOfRows; r++)
	{
		for (int c = 0; c < m_NumofCols; c++)
		{
			m_Data[r + c * m_NumOfRows] += other.m_Data[r + c * other.m_NumOfRows];
		}
	}
	return (*this);
}

Matrix Matrix::operator*(const double& other) const
{
	for (int r = 0; r < m_NumOfRows; r++)
	{
		for (int c = 0; c < m_NumofCols; c++)
		{
			m_Data[r + c * m_NumOfRows] *= other;
		}
	}
	return (*this);
}


Matrix Matrix::operator-(const Matrix& other) const
{
	Matrix result(m_NumOfRows, other.m_NumofCols);
	for (int r = 0; r < result.m_NumOfRows; r++)
	{
		for (int c = 0; c < result.m_NumofCols; c++)
		{
			result.m_Data[r + c * m_NumOfRows] = m_Data[r + c * m_NumOfRows] - other.m_Data[r + c * other.m_NumOfRows];
		}
	}
	return result;
}

Matrix Matrix::operator-=(const Matrix& other) const
{
	for (int r = 0; r < m_NumOfRows; r++)
	{
		for (int c = 0; c < m_NumofCols; c++)
		{
			m_Data[r + c * m_NumOfRows] -= other.m_Data[r + c * m_NumOfRows];
		}
	}
	return (*this);
}


Matrix Matrix::operator*(const Matrix& other) const
{
	Matrix result(m_NumOfRows, other.m_NumofCols);
	for (int r = 0; r < result.m_NumOfRows; r++)
	{
		for (int c = 0; c < result.m_NumofCols; c++)
		{
			for (int e = 0; e < m_NumofCols; e++)
			{
				result.m_Data[r + c * result.m_NumOfRows] += m_Data[r + e * m_NumOfRows] * other.m_Data[e + c * other.m_NumOfRows];
			}
		
		}
	}
	return result;
}

void Matrix::print()
{
	
	for (int r = 0; r < m_NumOfRows; r++)
	{
		std::cout << std::endl;
		for (int c = 0; c < m_NumofCols; c++)
		{
			printf("%.13f ", m_Data[r + c * m_NumOfRows]);
		}
	}
}

Matrix Matrix::fromArray(const std::vector<double>& arr)
{
	Matrix result(arr.size(), 1);
	for (int r = 0; r < result.m_NumOfRows; r++)
	{
		for (int c = 0; c < result.m_NumofCols; c++)
		{
			result.m_Data[r + c * result.m_NumOfRows] = arr[r];
		}
	}
	return result;
}

Matrix Matrix::map(const Matrix& other, const std::function<double(double x)>& func)
{
	Matrix result(other.m_NumOfRows, other.m_NumofCols);
	for (int r = 0; r < result.m_NumOfRows; r++)
	{
		for (int c = 0; c < result.m_NumofCols; c++)
		{
			result.m_Data[r + c * result.m_NumOfRows] = func(other.m_Data[r + c * result.m_NumOfRows]);
		}
	}

	return result;
}

void Matrix::hadamard(const Matrix& a) const
{
	for (int r = 0; r < m_NumOfRows; r++)
	{
		for (int c = 0; c < m_NumofCols; c++)
		{
			m_Data[r + c * m_NumOfRows] *= a.m_Data[r + c * a.m_NumOfRows];
		}
	}
}

Matrix Matrix::hadamard(const Matrix& a, const Matrix& b)
{
	Matrix result(a.m_NumOfRows, b.m_NumofCols);
	for (int r = 0; r < result.m_NumOfRows; r++)
	{
		for (int c = 0; c < result.m_NumofCols; c++)
		{
			result.m_Data[r + c * result.m_NumOfRows] = a.m_Data[r + c * a.m_NumOfRows] * b.m_Data[r + c * b.m_NumOfRows];
		}
	}
	return result;
}

Matrix Matrix::transpose(const Matrix& other)
{
	Matrix result(other.m_NumofCols, other.m_NumOfRows);
	for (int r = 0; r < result.m_NumOfRows; r++)
	{
		for (int c = 0; c < result.m_NumofCols; c++)
		{
			result.m_Data[r + c * result.m_NumOfRows] = other.m_Data[c + r * other.m_NumOfRows];
		}
	}
	return result;
}

std::vector<double> Matrix::toArray()
{
	std::vector<double> arr;
	arr.reserve(m_NumOfRows * m_NumofCols);
	
	for (int r = 0; r < m_NumOfRows; r++)
	{
		for (int c = 0; c < m_NumofCols; c++)
		{
			arr.push_back(m_Data[r + c * m_NumOfRows]);
		}
	}
	return arr;
}

Matrix::~Matrix()
{
	delete[] m_Data;
}
