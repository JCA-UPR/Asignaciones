#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <regex>
#include "A1_Matrices.cpp"

#define DEBUG 3


std::string operator *(int num, std::string var) {
    return var + std::to_string(num);
}
std::string operator *(std::string var, int num) {
    return var + std::to_string(num);
}

std::string operator * (std::string var_1, std::string var_2) {

    std::vector<std::string>* terms_1 {nullptr};
    std::vector<std::string>* terms_2 {nullptr};
    std::vector<std::string>* big_terms {nullptr};
    std::vector<std::string>* smol_terms {nullptr};


    // // break into terms using + and - as deliminting characters
    // if (var_1.find("+") != std::string::npos || var_1.find("-") != std::string::npos) {
    //     std::vector<std::string> terms_1 = splitString(var_1);
    // } else {
    //     std::vector<std::string> terms_1 {var_1};
    // }
    // if (var_2.find("+") != std::string::npos || var_2.find("-") != std::string::npos) {
    //     std::vector<std::string> terms_2 = splitString(var_2);
    // } else {
    //     std::vector<std::string> terms_2 {var_2};
    // }

    // // Choose the polinomial with the most terms
    // if (terms_1->size() > terms_2->size()) {
    //     big_terms = &*terms_1;
    //     smol_terms = &*terms_2;
    // } else {
    //     big_terms = &*terms_2;
    //     smol_terms = &*terms_1;
    // }


    // // Extract numbers and characters for both termsthat are being multiplied
    // std::pair<std::vector<int>, std::vector<std::string>> num_char_big_terms {extractNumbersAndChars((*big_terms)[0])};
    // std::pair<std::vector<int>, std::vector<std::string>> num_char_smol_terms {extractNumbersAndChars((*smol_terms)[0])};


    // std::cout << "Numbers: ";

    // for (auto i {0}; i < num_char_big_terms.first.size(); i++) {
    //     std::cout << num_char_big_terms.first[i] << " ";
    // }
    // std::cout << std::endl;




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
        std::cout << 2 * std::string("x") * 2<< std::endl;

    }

    if (DEBUG == 3) {
        std::string eq_1 {"2x"};
        std::string eq_2 {"3x"};

        // std::cout << eq_1 * eq_2 << std::endl;
    }
}