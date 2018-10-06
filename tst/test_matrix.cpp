#include "catch.hpp"
#include "../inc/matrix.hpp"
#include "math.h"

TEST_CASE("Constructor") {
    Matrix mat1(2, 2);
    REQUIRE(mat1(1, 1) == 0);

    double elems2 = -2;
    Matrix mat2(2, 1, elems2);
    REQUIRE(mat2(0, 0) == -2);
    REQUIRE(mat2(1, 0) == -2);
    
    double elems3[] = {1, -2, 3, -4, 5, 6};
    Matrix mat3(2, 3, elems3);
    REQUIRE(mat3(0, 0) == 1);
    REQUIRE(mat3(0, 1) == -2);
    REQUIRE(mat3(0, 2) == 3);
    REQUIRE(mat3(1, 0) == -4);
    REQUIRE(mat3(1, 1) == 5);
    REQUIRE(mat3(1, 2) == 6);

    Matrix rand_mat = Matrix::random(2, 2, -1, 1, 1990);
    REQUIRE(rand_mat(0, 0) == Approx(-0.663448));
    REQUIRE(rand_mat(0, 1) == Approx(0.10162));
    REQUIRE(rand_mat(1, 0) == Approx(-0.403476));
    REQUIRE(rand_mat(1, 1) == Approx(-0.710199));
}


TEST_CASE("Getter and Setter") {
    Matrix mat1(2, 2);
    mat1(0, 1) = 5;
    REQUIRE(mat1(0, 0) == 0);
    REQUIRE(mat1(0, 1) == 5);
    REQUIRE(mat1(1, 0) == 0);
    REQUIRE(mat1(1, 1) == 0);

    double elems2[] = {1, 2, 3, 4};
    Matrix mat2(2, 2, elems2);
    mat1 = mat2;
    REQUIRE(mat1(0, 0) == 1);
    REQUIRE(mat1(0, 1) == 2);
    REQUIRE(mat1(1, 0) == 3);
    REQUIRE(mat1(1, 1) == 4);
}

TEST_CASE("Element Math") {
    double elems1[] = {1, 2, 3, 4};
    Matrix mat1(2, 2, elems1);
    double elems2[] = {4, -2, 3, -1};
    Matrix mat2(2, 2, elems2);
    Matrix mat3 = mat1 + mat2;
    REQUIRE(mat3(0, 0) == 5);
    REQUIRE(mat3(0, 1) == 0);
    REQUIRE(mat3(1, 0) == 6);
    REQUIRE(mat3(1, 1) == 3);
    
    Matrix mat4 = mat1 - mat2;
    REQUIRE(mat4(0, 0) == -3);
    REQUIRE(mat4(0, 1) == 4);
    REQUIRE(mat4(1, 0) == 0);
    REQUIRE(mat4(1, 1) == 5);
    
    Matrix mat5 = mat1.elementMultiplies(mat2);
    REQUIRE(mat5(0, 0) == 4);
    REQUIRE(mat5(0, 1) == -4);
    REQUIRE(mat5(1, 0) == 9);
    REQUIRE(mat5(1, 1) == -4);
}

TEST_CASE("Multiplication") {
    double elems1[] = {1, 2, 3, 4, 5, 6};
    Matrix mat1(2, 3, elems1);
    double elems2[] = {3, 2, 1};
    Matrix mat2(3, 1, elems2);
    Matrix mat3 = mat1 * mat2;
    REQUIRE(mat3(0, 0) == 10);
    REQUIRE(mat3(1, 0) == 28);

    Matrix mat4 = mat1 * 2;
    REQUIRE(mat4(0, 0) == 2);
    REQUIRE(mat4(0, 1) == 4);
    REQUIRE(mat4(0, 2) == 6);
    REQUIRE(mat4(1, 0) == 8);
    REQUIRE(mat4(1, 1) == 10);
    REQUIRE(mat4(1, 2) == 12);
}

TEST_CASE("Transpose") {
    double elems[] = {1, 2, 3, 4, 5, 6};
    Matrix mat(3, 2, elems);
    Matrix tran = mat.transpose();

    REQUIRE(tran(0, 0) == 1);
    REQUIRE(tran(0, 1) == 3);
    REQUIRE(tran(0, 2) == 5);
    REQUIRE(tran(1, 0) == 2);
    REQUIRE(tran(1, 1) == 4);
    REQUIRE(tran(1, 2) == 6);
}

TEST_CASE("getMinorSubmatrix") {
    double elems[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix mat(3, 3, elems);
    Matrix sub = mat.getMinorSubmatrix(1, 2);

    REQUIRE(sub(0, 0) == 1);
    REQUIRE(sub(0, 1) == 2);
    REQUIRE(sub(1, 0) == 7);
    REQUIRE(sub(1, 1) == 8);
}

TEST_CASE("Determinant") {
    double elems1[] = {3};
    Matrix mat1(1, 1, elems1);
    REQUIRE(mat1.det() == 3);

    double elems2[] = {1, 2, 3, 4};
    Matrix mat2(2, 2, elems2);
    REQUIRE(mat2.det() == -2);

    double elems3[] = {1, 2, 3, 6, 5, 4, 9, 7, 8};
    Matrix mat3(3, 3, elems3);
    REQUIRE(mat3.det() == -21);
}

TEST_CASE("Function") {
    double elems[] = {1, 4, 9};
    Matrix mat(3, 1, elems);
    Matrix out = mat.f(sqrt);
    REQUIRE(out(0, 0) == 1);
    REQUIRE(out(1, 0) == 2);
    REQUIRE(out(2, 0) == 3);
}
