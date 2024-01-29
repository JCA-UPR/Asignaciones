#ifndef MATRICES_HPP
#define MATRICES_HPP

#include <iostream>
#include <fstream>


class Matrix {
    private:
        std::vector<std::vector<int> > data;
        int rows, columns, det;

    public:
    // Getters
    std::vector<std::vector<int> > get_data() {
        return data;
    }
    int get_rows() const {
        return rows;
    }
    int get_columns() const {
        return columns;
    }
    int get_det() {
        return det;
    }

    // Setters
    void set_data(std::vector<std::vector<int> > new_data) {
        data = new_data;
    }
    void set_rows(int new_rows) {
        rows = new_rows;
    }
    void set_columns(int new_columns) {
        columns = new_columns;
    }
    void set_det(int new_det) {
        det = new_det;
    }

    // Constructors
    // Matrix() : rows(0), columns(0) {}
    Matrix(int new_rows, int new_columns) : rows(new_rows) , columns(new_columns), det(0) {
        data.resize(new_rows, std::vector<int>(new_columns, 0));
    }

    // Operators

    friend std::ostream& operator<<(std::ostream& out, Matrix& Matrix_A) {

        for (auto i {0}; i < Matrix_A.rows; i++) {
            out << "[";
            for (auto j {0}; j < Matrix_A.columns; j++) {
                if (j == Matrix_A.columns - 1) {
                    out << Matrix_A(i,j);
                } else {
                    out << Matrix_A(i,j) << ", ";
                }
            }
            out << "]" << std::endl;
        }

        return out;
    }

    int& operator() (int row, int column) {
        return data[row][column];
    }

    friend Matrix& operator- (Matrix& Matrix_A, Matrix& Matrix_B) {
        if ((Matrix_A.columns != Matrix_B.columns) || (Matrix_A.rows != Matrix_B.rows)) std::cout << "Error 1" << std::endl;

        Matrix* Substraction_Matrix {new Matrix(Matrix_A.rows, Matrix_A.columns)};

        for (int i {0}; i < Matrix_A.rows; i++) {
            for (int j {0}; j < Matrix_A.columns; j++) {
                (*Substraction_Matrix)(i,j) = Matrix_A(i,j) - Matrix_B(i,j);
            }
        }
        return *Substraction_Matrix;
    }

    friend Matrix& operator+ (Matrix& Matrix_A, Matrix& Matrix_B) {
        if ((Matrix_A.columns != Matrix_B.columns) || (Matrix_A.rows != Matrix_B.rows)) std::cout << "Error 1" << std::endl;

        Matrix* Addition_Matrix {new Matrix(Matrix_A.rows, Matrix_A.columns)};

        for (int i {0}; i < Matrix_A.rows; i++) {
            for (int j {0}; j < Matrix_A.columns; j++) {
                (*Addition_Matrix)(i,j) = Matrix_A(i,j) + Matrix_B(i,j);
            }
        }
        return *Addition_Matrix;
    }
};

#endif