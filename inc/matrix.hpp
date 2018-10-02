#ifndef MATRIX_H_
#define MATRIX_H_
#include <vector>

using namespace std;

class Matrix {
    double* elements_;
    int dim_x_;
    int dim_y_;

    public:
    Matrix(int dim_x, int dim_y);
    Matrix(int dim_x, int dim_y, double element);
    Matrix(int dim_x, int dim_y, double elements[]);
    int getDimX() const;
    int getDimY() const;
    double& operator()(int x, int y);
    double  operator()(int x, int y) const;
    Matrix operator+(Matrix& rhs) const;
    Matrix operator*(Matrix& rhs) const;
    Matrix transpose() const;
    double det() const;
    Matrix getMinorSubmatrix(int x, int y) const;
    Matrix f(double (*f)(double)) const;    
};

#endif
