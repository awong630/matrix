#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdexcept>
#include "matrix.hpp"

Matrix::Matrix(unsigned dim_x, unsigned dim_y) {
    elements = new double[dim_x * dim_y] {};
    this->dim_x = dim_x;
    this->dim_y = dim_y;
}

Matrix::Matrix(unsigned dim_x, unsigned dim_y, double elements[]) {
    this->elements = new double[dim_x * dim_y];
    std::copy(elements, elements + dim_x * dim_y, this->elements);
    this->dim_x = dim_x;
    this->dim_y = dim_y;
}

unsigned Matrix::getDimX() const {
    return dim_x;
}

unsigned Matrix::getDimY() const {
    return dim_y;
}

double Matrix::operator()(unsigned x, unsigned y) const {
    return elements[x * dim_y + y];
}

double& Matrix::operator()(unsigned x, unsigned y) {
    return elements[x * dim_y + y];
}

Matrix Matrix::operator+(Matrix& rhs) const {
    if (dim_x != rhs.dim_x || dim_y != rhs.dim_y) {
        throw std::invalid_argument("Dimensions must be equal");
    }

    Matrix out(dim_x, dim_y);
    for (int i = 0; i < out.dim_x; i++) {
        for (int j = 0; j < out.dim_y; j++) {
            out(i, j) = (*this)(i, j) + rhs(i, j);
        }
    }

    return out;
}

Matrix Matrix::operator*(Matrix& rhs) const {
    unsigned mid_dim = dim_y;
    if (mid_dim != rhs.dim_x) {
        throw std::invalid_argument("Dimensions mismatch (Must be (IxJ) * (JxH)");
    }

    Matrix out(dim_x, rhs.dim_y);
    for (int i = 0; i < out.dim_x; i++) {
        for (int j = 0; j < out.dim_y; j++) {
            double dot_prod = 0;
            for (int k = 0; k < mid_dim; k++) {
                dot_prod += (*this)(i, k) * rhs(k, j);
            }
            out(i, j) = dot_prod;
        }
    }

    return out;
}

double Matrix::det() const {
    if (dim_x != dim_y) {
        throw std::domain_error("Must be a square matrix");
    }

    if (dim_x == 1) {
        // 1x1 determinent
        return (*this)(0, 0);
    } else if (dim_x == 2) {
        // 2x2 determinant
        return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
    } else {
        // Dimensions greater than 2, use expansion
        double out = 0;
        // Calculate cofactors using first row
        for (int i = 0; i < dim_y; i++) {
            Matrix minor = getMinorSubmatrix(0, i);
            out += pow(-1, i) * (*this)(0, i) * minor.det();
        }
        return out;
    }
}

Matrix Matrix::getMinorSubmatrix(unsigned x, unsigned y) const {
    // Get the submatrix corresponding to the minor of an element
    if (dim_x != dim_y) {
        throw std::domain_error("Must be a square matrix");
    }
    
    unsigned sub_dim = dim_x - 1;
    double sub_elements[sub_dim * sub_dim];
    unsigned ind = 0;
    for (int i = 0; i < dim_x; i++) {
        if (i == x) {
            continue;
        }
        for (int j = 0; j < dim_y; j++) {
            if (j == y) {
                continue;
            }
            sub_elements[ind] = (*this)(i, j);
            ind++;
        }
    }

    return Matrix(sub_dim, sub_dim, sub_elements);
}

