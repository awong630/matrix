#include "matrix.hpp"
#include <algorithm>
#include <functional>
#include <random>
#include <stdexcept>

Matrix::Matrix(int dim_x, int dim_y, double element) : elements_(dim_x * dim_y, element) {
    // Initialize Matrix with single element value
    dim_x_ = dim_x;
    dim_y_ = dim_y;
}

Matrix::Matrix(int dim_x, int dim_y, const std::vector<double>& elements) : elements_(elements) {
    // Initialize Matrix with element array
    dim_x_ = dim_x;
    dim_y_ = dim_y;
}

Matrix Matrix::random(int dim_x, int dim_y, double min, double max, unsigned seed) {
    // Initialize Matrix with random elements [min, max] using seed
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> dist(min, std::nextafter(max, std::numeric_limits<double>::max()));

    std::vector<double> elements(dim_x * dim_y);
    std::generate(elements.begin(), elements.end(), [&mt, &dist](){return dist(mt);});

    return Matrix(dim_x, dim_y, elements);
}

int Matrix::getDimX() const {
    return dim_x_;
}

int Matrix::getDimY() const {
    return dim_y_;
}

/*Matrix& Matrix::operator=(const Matrix& rhs) {
    if (dim_x_ != rhs.dim_x_ || dim_y_ != rhs.dim_y_) {
        throw std::invalid_argument("Dimensions must be equal");
    }
    std::copy(rhs.elements_, rhs.elements_ + rhs.dim_x_ * rhs.dim_y_, elements_);
    return *this;
}*/

double Matrix::operator()(int x, int y) const {
    return elements_.at(x * dim_y_ + y);
}

double& Matrix::operator()(int x, int y) {
    return elements_.at(x * dim_y_ + y);
}

Matrix Matrix::operator+(const Matrix& rhs) const {
    return elementwise(rhs, std::plus<double>());
}

Matrix Matrix::operator-(const Matrix& rhs) const {
    return elementwise(rhs, std::minus<double>());
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    int mid_dim = dim_y_;
    if (mid_dim != rhs.dim_x_) {
        throw std::invalid_argument("Dimensions mismatch (Must be (IxJ) * (JxH))");
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

Matrix Matrix::operator*(double rhs) const {
    return elementwise(std::bind(std::multiplies<double>(), std::placeholders::_1, rhs));
}

Matrix Matrix::elementMultiplies(const Matrix& rhs) const {
    return elementwise(rhs, std::multiplies<double>());
}

template <typename func> Matrix Matrix::elementwise(func f) const {
    std::vector<double> elements;
    elements.reserve(elements_.size());

    std::transform(elements_.begin(), elements_.end(),
        std::back_inserter(elements), f);

    return Matrix(dim_x_, dim_y_, elements);
}

template <typename func> Matrix Matrix::elementwise(const Matrix& rhs, func f) const {
    if (dim_x_ != rhs.dim_x_ || dim_y_ != rhs.dim_y_) {
        throw std::invalid_argument("Dimensions must be equal");
    }
    
    std::vector<double> elements;
    elements.reserve(elements_.size());

    std::transform(elements_.begin(), elements_.end(), rhs.elements_.begin(),
        std::back_inserter(elements), f);

    return Matrix(dim_x_, dim_y_, elements);
}

Matrix Matrix::transpose() const {
    std::vector<double> elements;
    elements.reserve(dim_x_ * dim_y_);
    for (std::vector<double>::size_type i = 0; i < elements_.size(); i++) {
        elements.push_back(elements_[i % dim_x_ * dim_y_ + i / dim_x_]);
    }

    return Matrix(dim_y_, dim_x_, elements);
}

double Matrix::det() const {
    if (dim_x_ != dim_y_) {
        throw std::domain_error("Must be a square matrix");
    }

    if (dim_x_ == 1) {
        // 1x1 determinant
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

Matrix Matrix::getMinorSubmatrix(int x, int y) const {
    // Get the submatrix corresponding to the minor of an element
    if (dim_x_ != dim_y_) {
        throw std::domain_error("Must be a square matrix");
    }
    
    int sub_dim = dim_x_ - 1;
    std::vector<double> elements;
    elements.reserve(sub_dim * sub_dim);
    for (int i = 0; i < dim_x_; i++) {
        if (i == x) {
            continue;
        }
        for (int j = 0; j < dim_y_; j++) {
            if (j == y) {
                continue;
            }
            elements.push_back((*this)(i, j));
        }
    }

    return Matrix(sub_dim, sub_dim, elements);
}

Matrix Matrix::f(double (*f)(double)) const {
    return elementwise(f);
}

