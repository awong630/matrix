#ifndef MATRIX_H_
#define MATRIX_H_
#include <vector>

using namespace std;

class Matrix {
    double* elements_;
    unsigned dim_x_;
    unsigned dim_y_;

    public:
    Matrix(unsigned dim_x, unsigned dim_y);
    Matrix(unsigned dim_x, unsigned dim_y, double element);
    Matrix(unsigned dim_x, unsigned dim_y, double elements[]);
    unsigned getDimX() const;
    unsigned getDimY() const;
    double& operator()(unsigned x, unsigned y);
    double  operator()(unsigned x, unsigned y) const;
    Matrix operator+(Matrix& rhs) const;
    Matrix operator*(Matrix& rhs) const;
    Matrix transpose() const;
    double det() const;
    Matrix getMinorSubmatrix(unsigned x, unsigned y) const;
    Matrix f(double (*f)(double)) const;    
};

#endif
