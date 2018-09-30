#ifndef MATRIX_H_
#define MATRIX_H_
#include <vector>

using namespace std;

class Matrix {
    double* elements;
    unsigned dim_x;
    unsigned dim_y;

    public:
    Matrix(unsigned dim_x, unsigned dim_y);
    Matrix(unsigned dim_x, unsigned dim_y, double elements[]);
    unsigned getDimX() const;
    unsigned getDimY() const;
    double& operator()(unsigned x, unsigned y);
    double  operator()(unsigned x, unsigned y) const;
    Matrix operator+(Matrix& rhs) const;
    Matrix operator*(Matrix& rhs) const;
    double det() const;
    Matrix getMinorSubmatrix(unsigned x, unsigned y) const;
    
};

#endif
