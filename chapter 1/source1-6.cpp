#include <iostream>
#include "time.h"

#define AROWS 3
#define ACOLS 4
#define BROWS 4
#define BCOLS 5
#define CROWS 3
#define CCOLS 5
#define N 10

using namespace std;

class Matrix
{
private:
    const int rows;
    const int cols;
    int *data;

public:
    Matrix(int, int);
    ~Matrix();
    int get_rows();
    int get_cols();

    int *get_data();
    int show_data();
    int sort_data();

    int addMatrix(Matrix &);
    int MultiplyMatrix(Matrix &, Matrix &);
};

Matrix::Matrix(const int rows, const int cols) : rows(rows), cols(cols)
{
    data = new int[rows * cols];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i * cols + j] = rand() % (N);
        }
    }
}

Matrix::~Matrix()
{
    delete data;
}

int Matrix::get_rows()
{
    return rows;
}

int Matrix::get_cols()
{
    return cols;
}

int *Matrix::get_data()
{
    return data;
}

int Matrix::show_data()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << data[i * cols + j] << " ";
        }
        cout << endl;
    }

    return 1;
}

int Matrix::addMatrix(Matrix &operandMatrix)
{
    int *operand = operandMatrix.get_data();
    int operand_cols = operandMatrix.get_cols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i * cols + j] += operand[i * operand_cols + j];
        }
    }
}

int Matrix::MultiplyMatrix(Matrix &operandMatrix, Matrix &storeMatrix)
{
    if (cols != operandMatrix.get_rows())
        return 0;

    int *operand = operandMatrix.get_data();
    int *store = storeMatrix.get_data();

    int bcols = operandMatrix.get_cols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < bcols; j++)
        {
            store[i * bcols + j] = 0;
            for (int k = 0; k < cols; k++)
            {
                store[i * bcols + j] += data[i * cols + k] * operand[bcols * k + j];
            }
            // cout << store[i * bcols + j] << " ";
        }
        // cout << endl;
    }
}

int main(void)
{
    Matrix matrixA(AROWS, ACOLS);
    Matrix matrixA1(AROWS, ACOLS);
    Matrix matrixB(BROWS, BCOLS);
    Matrix matrixC(CROWS, CCOLS);

    srand(time(NULL));

    cout << "\nmatrixA" << endl;
    matrixA.get_data();
    matrixA.show_data();

    cout << "\nmatrixB" << endl;
    matrixB.get_data();
    matrixB.show_data();

    matrixC.get_data();

    matrixA.MultiplyMatrix(matrixB, matrixC);

    cout << "\nmatrixC" << endl;
    matrixC.show_data();

    cout << "\nmatrixA1 origin" << endl;
    matrixA1.show_data();

    cout << "\nmatrixA1 after" << endl;
    matrixA1.addMatrix(matrixC);
    matrixA1.show_data();

    return 0;
}