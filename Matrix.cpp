//
// Created by asus on 3/26/2018.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>


using namespace std;

class Exception{
private:
	char* message;
public:
	Exception(): message(nullptr){}
	Exception(const char* const str): message(message){}
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
};




int main(){


	Matrix a(3,4);  // single block of memory 3 * 4 set all to 0.0

	a(1,1) = 1.5;
	a(2,1) = 3.2;
	/**
	 0.0  0.0  0.0  0.0
	 0.0  1.5  0.0  0.0
	 3.2  0.0  0.0  0.0
 */

	cout << a(1,2) << '\n';

	cout << a;

	Matrix b(3,4,1.5); // set all values to 1.5
	Matrix c = a + b;
	Matrix d(4,3,2.5);
	Matrix e = b * d; // matrix  mult.
	return 0;
}


