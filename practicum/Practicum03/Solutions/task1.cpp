#include <iostream>
#include <fstream>
#include <cmath>


const char SEPARATOR = ',';
const char ROW_BREAK = '|';


typedef int Cell;

struct Row {
    Cell* cells = nullptr;
    int length = 0;
};

struct Matrix {
    Row* rows = nullptr;
    int length = 0;
};

void allocateMatrix(Matrix &matrix, const char* filename) {
    std::ifstream in(filename);

    if (!in) {
        matrix.rows = nullptr;
        matrix.length = 0;
        return;
    }

    matrix.length = 0;

    int rowLength = 0, maxRowLenght = 0;
    Cell c;
    char separator;
    while (in >> c) {
        rowLength++;

        if (in >> separator) {
            if (separator == SEPARATOR) {
                continue;
            }
        }

        // Here we know we are either at EOF or '|'
        matrix.length++;
        maxRowLenght = std::max(rowLength, maxRowLenght);
        rowLength = 0;
    }

    matrix.rows = new Row[matrix.length];
    for (int i = 0; i < matrix.length; i++) {
        matrix.rows[i].cells = new Cell[maxRowLenght];
        matrix.rows[i].length = maxRowLenght;
    }

    in.close();
}

void freeMatrix(Matrix &matrix) {
    for (int i = 0; i < matrix.length; i++) {
        delete[] matrix.rows[i].cells;
    }
    delete[] matrix.rows;

    matrix.rows = nullptr;
    matrix.length = 0;
}

std::ifstream& readCell(std::ifstream &in, Cell &cell) {
    in >> cell;

    return in;
}

std::ifstream& readRow(std::ifstream &in, Row &row) {
    char separator;
    for (int i = 0; readCell(in, row.cells[i]); i++) {
        if (in >> separator) {
            if (separator == ',') {
                continue;
            }
        }

        break;
    }

    return in;
}

void readMatrix(Matrix &matrix, const char* filename) {
    allocateMatrix(matrix, filename);

    std::ifstream in(filename);

    if (!in) {
        freeMatrix(matrix);
        return;
    }

    for (int i = 0; readRow(in, matrix.rows[i]); i++) {
        ;
    }

    in.close();
}

void writeCell(std::ofstream &out, const Cell &cell) {
    out << cell;
}

void writeRow(std::ofstream &out, const Row &row) {
    if (row.length) {
        writeCell(out, row.cells[0]);
    }

    for (int i = 1; i < row.length; i++) {
        out << SEPARATOR;
        writeCell(out, row.cells[i]);
    }
}

void writeMatrix(const Matrix &matrix, const char* filename) {
    std::ofstream out(filename);

    if (!out) {
        std::cout << "Could not open file " << filename << '\n';
        return;
    }

    if (matrix.length) {
        writeRow(out, matrix.rows[0]);
    }

    for (int i = 1; i < matrix.length; i++) {
        out << ROW_BREAK;
        writeRow(out, matrix.rows[i]);
    }

    out.close();
}

Matrix multiply(Matrix lhs, Matrix rhs) {
    if (lhs.rows[0].length != rhs.length) {
        std::cout << "Unable to multiply these two matrices!\n";
        return Matrix{};
    }

    Matrix result;

    result.length = lhs.length;
    result.rows = new Row[lhs.length];
    for (int i = 0; i < result.length; i++) {
        result.rows[i].length = rhs.rows[0].length;
        result.rows[i].cells = new Cell[rhs.rows[0].length];
    }

    for (int i = 0; i < result.length; i++) {
        for (int j = 0; j < result.rows[i].length; j++) {
            result.rows[i].cells[j] = 0;
 
            for (int k = 0; k < rhs.length; k++) {
                result.rows[i].cells[j] += lhs.rows[i].cells[k] * rhs.rows[k].cells[j];
            }
        }
    }

    return result;
}

void multiplyFromFile(const char* A, const char* B, const char* output) {
    Matrix lhs, rhs;
    readMatrix(lhs, A);
    readMatrix(rhs, B);

    Matrix result = multiply(lhs, rhs);

    writeMatrix(result, output);

    freeMatrix(lhs);
    freeMatrix(rhs);
    freeMatrix(result);
}

int main() {
    multiplyFromFile("input1.txt", "input2.txt", "output.txt");

    return 0;
}