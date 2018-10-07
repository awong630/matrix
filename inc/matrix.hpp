#ifndef MATRIX_HPP_
#define MATRIX_HPP_
#include <vector>

class Matrix {
    // Private variables
    std::vector<double> elements_;
    int dim_x_;
    int dim_y_;
    
    // Private functions
    template <typename func> Matrix elementwise(func f) const;
    template <typename func> Matrix elementwise(const Matrix& rhs, func f) const;
    
    public:
    // Public functions
    Matrix(int dim_x, int dim_y, double element = 0);
    Matrix(int dim_x, int dim_y, const std::vector<double>& elements);
    static Matrix random(int dim_x, int dim_y, double min, double max, unsigned seed);
    int getDimX() const;
    int getDimY() const;
    double& operator()(int x, int y);
    double  operator()(int x, int y) const;
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;
    Matrix operator*(double rhs) const;
    Matrix elementMultiplies(const Matrix& rhs) const;
    Matrix transpose() const;
    double det() const;
    Matrix getMinorSubmatrix(int x, int y) const;
    Matrix f(double (*f)(double)) const;
};

#endif
