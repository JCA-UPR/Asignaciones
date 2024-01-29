#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <regex>
#include "A1_Matrices.cpp"

#define DEBUG 3

std::vector<int> multiply_poly(const std::vector<int>& Poly_A, const std::vector<int>& Poly_B) {
    std::vector<int>* product {new std::vector<int>((Poly_A.size() + Poly_B.size() - 1), 0)};

    for (auto i {0}; i < Poly_A.size(); i++) {
        for (auto j {0}; j < Poly_B.size(); j++) {
            (*product)[i + j] += Poly_A[i] * Poly_B[j];
        }
    }

    std::cout << "[";
    for (const auto& num : *product) {
        std::cout << " " << num; 
    }
    std::cout << "]" << std::endl;;

    return *product;
}


int determinante_2x2(Matrix& A) {
    if (A.get_columns() != 2 || A.get_rows() != 2) {
        return 0;
    }
    return A(0,0) * A(1,1) - A(0,1) * A(1,0);
}

int determinante_3x3(Matrix& A) {
    if (A.get_columns() != 3 || A.get_rows() != 3) {
        return 0;
    }

    return  A(0,0) * A(1,1) * A(2,2)
            + A(0,1) * A(1,2) * A(2,0)
            + A(0,2) * A(1,0) * A(2,1)
            - A(0,2) * A(1,1) * A(2,0)
            - A(0,0) * A(1,2) * A(2,1)
            - A(0,1) * A(1,0) * A(2,2);
}

Matrix& matrix_remaming_when_removing(Matrix& A, int non_row, int non_column) {
    // Make a new matrix that will hold the resulting matrix
    Matrix* NewMatrix = new Matrix(A.get_rows() - 1, A.get_columns() - 1);

    // Copy all values except those in row i or column j
    for (int Ai {0}, Bi {0}; Ai < A.get_rows(); Ai++, Bi++) {
        for (int Aj {0}, Bj {0}; Aj < A.get_columns(); Aj++, Bj++) {
            if (Ai == non_row) Ai++;
            if (Aj == non_column) Aj++;
            (*NewMatrix)(Bi, Bj) = A(Ai, Aj);
        }
    }

    if (DEBUG) {
        for (int i {0}; i < NewMatrix->get_rows(); i++) {
            for (int j {0}; j < NewMatrix->get_columns(); j++) {
                std::cout << (*NewMatrix)(i,j);
            }
            std::cout << std::endl;
        }
    }

    return *NewMatrix;
}

int calcular_determinante(Matrix& A, int rows, int columns) {

    // Caso base de la recursión
    if (rows == 3 && columns == 3) return determinante_3x3(A);

    // Find the row with the greatest ammount of ceros
    int ceros[rows];
    auto max_ceros {0};


    for (int i {0}; i < rows; i++ ) {
        ceros[i] = 0;
    }

    for (int i {0}; i < rows; i++) {
        for (int j {0}; j < columns; j++) {
            if (A(i,j) == 0) {
                ceros[i]++;
            }
        }
    }


    for (const auto& num : ceros) {
        if (num > 0) {max_ceros = num;}
    }

    auto det {0};

    for (int col {0}; col < columns; col++) {
        det += A(max_ceros, col) * pow(-1, max_ceros + col) * calcular_determinante(matrix_remaming_when_removing(A, max_ceros, col), rows - 1, columns - 1);
    }
    return det;

}

int main() {

    // int array[3][3] {{1,2,3},{1,0,1},{2,2,1}};
    // int four_by_four[4][4] {{4,1,0,3},{3,2,9,7},{8,9,0,5},{2,3,9,8}};
    // Matrix MyMatrix(3,3);
    // Matrix four_by_four_matrix(4,4);

    // for (int i {0}; i < MyMatrix.get_rows(); i++) {
    //     for (int j {0}; j < MyMatrix.get_columns(); j++) {
    //         MyMatrix(i,j) = array[i][j];
    //     }
    // }

    // for (int i {0}; i < four_by_four_matrix.get_rows(); i++) {
    //     for (int j {0}; j < four_by_four_matrix.get_columns(); j++) {
    //         four_by_four_matrix(i,j) = four_by_four[i][j];
    //     }
    // }

    // if (DEBUG) {
    //     for (int i {0}; i < four_by_four_matrix.get_rows(); i++) {
    //         for (int j {0}; j < four_by_four_matrix.get_columns(); j++) {
    //             std::cout << four_by_four_matrix(i,j);
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << "\n\n\n";
    // }
    // std::cout << calcular_determinante(four_by_four_matrix,4,4) << std::endl;


    if (DEBUG == 2) {
        int four_by_four_of_ones[4][4] {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
        int four_by_four_of_fours[4][4] {{4,4,4,4},{4,4,4,4},{4,4,4,4},{4,4,4,4}};
        Matrix _4_by_4_1(4,4);
        Matrix _4_by_4_2(4,4);

        for (int i {0}; i < _4_by_4_1.get_rows(); i++) {
            for (int j {0}; j < _4_by_4_1.get_columns(); j++) {
                _4_by_4_1(i,j) = four_by_four_of_ones[i][j];
                _4_by_4_2(i,j) = four_by_four_of_fours[i][j];
            }
        }

        for (int i {0}; i < _4_by_4_1.get_rows(); i++) {
            for (int j {0}; j < _4_by_4_1.get_columns(); j++) {
                std::cout << _4_by_4_1(i,j);
            }
            std::cout << std::endl;
        }
        std::cout << "\n\n\n";

        for (int i {0}; i < _4_by_4_2.get_rows(); i++) {
            for (int j {0}; j < _4_by_4_2.get_columns(); j++) {
                std::cout << _4_by_4_2(i,j);
            }
            std::cout << std::endl;
        }
        std::cout << "\n\n\n";

        std::cout << (_4_by_4_2 + _4_by_4_2 - _4_by_4_1) << std::endl;
        // std::cout << 2 * std::string("x") * 2<< std::endl;

    }

    if (DEBUG == 3) {
        std::vector<int> p_1 {1,2,3};
        std::vector<int> p_2 {4,5,6};

        multiply_poly(p_1,p_2);
    }
}