#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdexcept>
#include "matrix.hpp"

Matrix::Matrix(unsigned dim_x, unsigned dim_y) {
    elements_ = new double[dim_x * dim_y] {};
    dim_x_ = dim_x;
    dim_y_ = dim_y;
}

Matrix::Matrix(unsigned dim_x, unsigned dim_y, double element) {
    elements_ = new double[dim_x * dim_y];
    std::fill_n(elements_, dim_x * dim_y, element);
    dim_x_ = dim_x;
    dim_y_ = dim_y;
}

Matrix::Matrix(unsigned dim_x, unsigned dim_y, double elements[]) {
    elements_ = new double[dim_x * dim_y];
    std::copy(elements, elements + dim_x * dim_y, elements_);
    dim_x_ = dim_x;
    dim_y_ = dim_y;
}

unsigned Matrix::getDimX() const {
    return dim_x_;
}

unsigned Matrix::getDimY() const {
    return dim_y_;
}

double Matrix::operator()(unsigned x, unsigned y) const {
    return elements_[x * dim_y_ + y];
}

double& Matrix::operator()(unsigned x, unsigned y) {
    return elements_[x * dim_y_ + y];
}

Matrix Matrix::operator+(Matrix& rhs) const {
    if (dim_x_ != rhs.dim_x_ || dim_y_ != rhs.dim_y_) {
        throw std::invalid_argument("Dimensions must be equal");
    }

    Matrix out(dim_x_, dim_y_);
    for (int i = 0; i < out.dim_x_; i++) {
        for (int j = 0; j < out.dim_y_; j++) {
            out(i, j) = (*this)(i, j) + rhs(i, j);
        }
    }

    return out;
}

Matrix Matrix::operator*(Matrix& rhs) const {
    unsigned mid_dim = dim_y_;
    if (mid_dim != rhs.dim_x_) {
        throw std::invalid_argument("Dimensions mismatch (Must be (IxJ) * (JxH)");
    }

    Matrix out(dim_x_, rhs.dim_y_);
    for (int i = 0; i < out.dim_x_; i++) {
        for (int j = 0; j < out.dim_y_; j++) {
            double dot_prod = 0;
            for (int k = 0; k < mid_dim; k++) {
                dot_prod += (*this)(i, k) * rhs(k, j);
            }
            out(i, j) = dot_prod;
        }
    }

    return out;
}

Matrix Matrix::transpose() const {
    double new_elements[dim_x_ * dim_y_];
    for (int i = 0; i < dim_x_ * dim_y_; i++) {
        new_elements[i] = elements_[i % dim_x_ * dim_y_ + i / dim_x_];
    }

    return Matrix(dim_y_, dim_x_, new_elements);
}

double Matrix::det() const {
    if (dim_x_ != dim_y_) {
        throw std::domain_error("Must be a square matrix");
    }

    if (dim_x_ == 1) {
        // 1x1 determinent
        return (*this)(0, 0);
    } else if (dim_x_ == 2) {
        // 2x2 determinant
        return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
    } else {
        // Dimensions greater than 2, use expansion
        double out = 0;
        // Calculate cofactors using first row
        for (int i = 0; i < dim_y_; i++) {
            Matrix minor = getMinorSubmatrix(0, i);
            out += pow(-1, i) * (*this)(0, i) * minor.det();
        }
        return out;
    }
}

Matrix Matrix::getMinorSubmatrix(unsigned x, unsigned y) const {
    // Get the submatrix corresponding to the minor of an element
    if (dim_x_ != dim_y_) {
        throw std::domain_error("Must be a square matrix");
    }
    
    unsigned sub_dim = dim_x_ - 1;
    double sub_elements[sub_dim * sub_dim];
    unsigned ind = 0;
    for (int i = 0; i < dim_x_; i++) {
        if (i == x) {
            continue;
        }
        for (int j = 0; j < dim_y_; j++) {
            if (j == y) {
                continue;
            }
            sub_elements[ind] = (*this)(i, j);
            ind++;
        }
    }

    return Matrix(sub_dim, sub_dim, sub_elements);
}

Matrix Matrix::f(double (*f)(double)) const {
    double new_elements[dim_x_ * dim_y_];
    for (int i = 0; i < dim_x_ * dim_y_; i++) {
        new_elements[i] = (*f)(elements_[i]);
    }

    return Matrix(dim_x_, dim_y_, new_elements);
}
