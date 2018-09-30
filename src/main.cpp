#include <iostream>
#include "matrix.hpp"

int main() {

    double elems[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix mat(3, 3, elems);
    Matrix sub = mat.getMinorSubmatrix(1, 2);
    std::cout << "Post function" << endl;
    std::cout << sub.getDimX() << endl;
    std::cout << sub.getDimY() << endl;
    std::cout << sub(0, 0) << endl;
    std::cout << sub(0, 1) << endl;
    std::cout << sub(1, 0) << endl;
    std::cout << sub(1, 1) << endl;

}
