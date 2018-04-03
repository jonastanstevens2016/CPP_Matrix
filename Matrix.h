#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H



#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;

class Exception{
private:
	string message;
public:
	Exception(): message(nullptr){}
	Exception(const string& str): message(str){}
};

class InvalidMatrixOpsException: public Exception {
public:
	InvalidMatrixOpsException(): Exception() {}
	InvalidMatrixOpsException(const char* const str): Exception(str){}
};

class Matrix {
private:
	double* array;
	int rowlen, collen;
public:
	Matrix(): array(nullptr), rowlen(0), collen(0){}

	Matrix(int rowlen, int collen): rowlen(rowlen), collen(collen), array(new double[rowlen * collen]){
		for(int i = 0; i < rowlen * collen; ++i)
			array[i] = 0;
	}

	Matrix(int rowlen, int collen, double init_value): rowlen(rowlen), collen(collen), array(new double[rowlen*collen]){
		for(int i = 0; i < rowlen * collen; ++i)
			array[i] = init_value;
	}

	Matrix(const Matrix& other): rowlen(other.rowlen), collen(other.collen), array(new double[rowlen * collen]){
		for(int i = 0; i < rowlen * collen; i ++)
			array[i] = other.array[i];
	}

	~Matrix(){delete [] array;}

	Matrix& operator = (const Matrix& m1){
		if(this == &m1) return *this;

		delete [] array;
		rowlen = m1.rowlen;
		collen = m1.collen;
		if(m1.array == nullptr)
			array = nullptr;
		else {
			array = new double[rowlen * collen];
			for(int i = 0; i < rowlen * collen; i ++)
				array[i] = m1.array[i];
		}
		return *this;
	}

	friend ostream& operator << (ostream& cout, const Matrix& m){
		for(int i = 0; i < m.rowlen; i ++){
			cout << '[';
			for(int j = 0; j < m.collen; j ++){
				cout << setprecision(2) << m.array[i * m.collen + j] << ',';
			}
			cout << ']' << endl;
		}
		return cout;
	}

	double operator() (int row, int col) const{
		if(row < 0 || row >= rowlen || col < 0 || col > collen)
			throw Exception("Matrix out of bound exception");

		return array[row * collen + col];
	}

	double& operator() (int row, int col) {
		if(row < 0 || row >= rowlen || col < 0 || col > collen)
			throw Exception("Matrix out of bound exception");
		return array[row * collen + col];
	}

	Matrix operator +(const Matrix& other) const {
		if(rowlen != other.rowlen || collen != other.collen)
			throw InvalidMatrixOpsException("Cannot add 2 matrixes with different sizes");

		Matrix res(other.rowlen, other.collen);
		for(int i = 0; i < rowlen * collen; i ++)
			res.array[i] = array[i] + other.array[i];

		return res;
	}

	Matrix operator * (const Matrix& other) const {
		if(collen != other.rowlen)
			throw InvalidMatrixOpsException("Illegal matrix shape for matrix multiplication");

		Matrix res (rowlen, other.collen, 0);
		for(int i = 0; i < rowlen; i ++){
			for(int j = 0; j < collen; j ++){
				for(int k = 0; k < other.collen; k ++){
					res.array[i * res.collen + k] += array[i* collen + j] * other.array[j *other.collen + k];
				}
			}
		}
		return res;
	}

	// MOVE constructor
	Matrix (Matrix&& orig) {
		array = orig.array;
		orig.array = nullptr;
		rowlen = orig.rowlen;
		collen = orig.collen;
	}
};

#endif //MATRIX_MATRIX_H