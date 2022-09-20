#include <iostream>
#include "time.h"

#define TERMS 5
#define MaxExp 10

using namespace std;

class Matrix;

class Term
{
    friend Matrix;

public:
    Term();
    Term(const float, const int);
    ~Term();
    friend ostream &operator<<(ostream &, Term &);

private:
    float coef;
    int exp;
};

Term::Term()
{
}

Term::Term(const float num, const int value) : coef(num), exp(value)
{
}

Term::~Term()
{
}

ostream &operator<<(ostream &out, Term &term)
{
    out << term.coef << "x**" << term.exp << " ";
    return out;
}

class Matrix
{
private:
    int rows, cols;
    static Term *TermElement;
    static int free;
    int start, finnish;
    int terms;

public:
    Matrix(const int, const int);
    ~Matrix();
    int get_data() const;
    int show_data() const;
    int sort_data() const;
    int get_start() const;
    int get_finnish() const;
    int *get_rows_cols() const;
    Matrix *addMatrix(const Matrix &);
    Matrix &operator=(const Matrix *);
};

Matrix::Matrix(const int terms, const int maxExp) : rows(terms), cols(maxExp)
{
    start = free;
    this->terms = rows * cols;
    finnish = start + this->terms;
    free = finnish;
}

Matrix::~Matrix()
{
    free = start;
}

int Matrix::get_start() const
{
    return start;
}
int Matrix::get_finnish() const
{
    return finnish;
}

int *Matrix::get_rows_cols() const
{
    return new int[2]{rows, cols};
}

int Matrix::get_data() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            TermElement[i * cols + j + start] = Term(rand() % 10, terms - (i * cols + j));
            // cout << start + i * cols + j << endl;
        }
    }

    return 0;
}

int Matrix::show_data() const
{
    for (int i = start; i < start + rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << TermElement[(i - start) * cols + j + start] << " ";
        }
    }
    cout << endl;
}

Matrix *Matrix::addMatrix(const Matrix &operandMatrix)
{
    int *o_rows_cols = operandMatrix.get_rows_cols();

    if (rows != o_rows_cols[0] && cols != o_rows_cols[1])
    {
        cout << "addition not avaliable" << endl;
        return this;
    }

    int o_start = operandMatrix.get_start();
    int o_finnish = operandMatrix.get_finnish();

    int store_start = finnish > o_finnish ? finnish : o_finnish;

    Matrix *storeMatrix = new Matrix(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            TermElement[i * cols + j + store_start] = Term(TermElement[start + i * cols + j].coef + TermElement[o_start + i * cols + j].coef,
                                                           terms - (i * cols + j));
        }
    }
    return storeMatrix;
}

Matrix &Matrix::operator=(const Matrix *operandMatrix)
{
    int *int_wrap = operandMatrix->get_rows_cols();
    rows = int_wrap[0];
    cols = int_wrap[1];
    terms = int_wrap[0] * int_wrap[1];
    start = operandMatrix->get_start() - terms;
    finnish = operandMatrix->get_finnish() - terms;
    free = finnish;

    return *this;
}

int Matrix::free = 0;
Term *Matrix::TermElement = new Term[100];

int main()
{
    Matrix matrixA(3, 4);

    Matrix matrixB(3, 4);

    Matrix matrixC(3, 4);

    // F[5,6] = D[3,4] + E[5,6] 구현하기 실습

    srand(time(NULL));

    cout << endl
         << "matrix A:"
         //  << matrixA.get_start() << " to " << matrixA.get_finnish() - 1
         << endl;

    matrixA.get_data();

    matrixA.show_data();

    cout
        << endl
        << "matrix B:"
        // << matrixB.get_start() << " to " << matrixB.get_finnish() - 1
        << endl;

    matrixB.get_data();

    matrixB.show_data();

    cout << "\n"
         << "matrix C = A + B:" << endl;

    matrixC = matrixA.addMatrix(matrixB);

    matrixC.show_data();

    system("pause");

    return 0;
}
