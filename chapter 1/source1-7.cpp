#include <iostream>
#include "time.h"

#define N 10
#define AROWS 3
#define ACOLS 4
#define BROWS 4
#define BCOLS 5
#define CROWS 3
#define CCOLS 5
#define DROWS 5
#define DCOLS 4
#define EROWS 3
#define ECOLS 4

using namespace std;

class Matrix
{
    int rows;
    int cols;
    static int *data;
    static int free;
    int start;
    int finnish;
    int terms;
    int get_data();

public:
    Matrix(int, int);
    ~Matrix();
    int show_data();
    int sort_data();
    int get_start();
    int get_finnish();
    int get_rows();
    int get_cols();
    int addMatrix(Matrix &);
    int MultiplyMatrix(Matrix &, Matrix &);
};

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols)
{
    int index = 0;

    while (data[index] != -1)
    {
        index += 1;
    }

    start = index;

    finnish = start + rows * cols;
    data[finnish] = -1;

    get_data();
}

Matrix::~Matrix()
{
    delete data;
    cout << "Matrix destructed" << endl;
}

int Matrix::get_data()
{
    for (int i = start; i < finnish; i++)
    {
        data[i] = rand() % N;
    }

    return 0;
}

int Matrix::get_start()
{
    return start;
}

int Matrix::get_finnish()
{
    return finnish;
}

int Matrix::get_rows()
{
    return rows;
}

int Matrix::get_cols()
{
    return cols;
}

int Matrix::show_data()
{
    cout << "data from " << start << " to " << finnish - 1 << ":" << endl;

    for (int i = start; i < finnish; i++)
    {
        cout << data[i] << ((i - start + 1) % cols == 0 ? "\n" : " ");
    }
    cout << endl;

    return 0;
}

int Matrix::sort_data()
{
    int length = rows * cols;
    int *temp = new int[length];
    int tmp_cnt = 0; // i - start 해도 되지만 이게 보기에 더 깔끔

    for (int i = start; i < finnish; i++)
    {
        temp[tmp_cnt++] = data[i];
    }

    for (int i = 0; i < length - 1; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (temp[i] > temp[j])
            {
                int temp_store = temp[i];
                temp[i] = temp[j];
                temp[j] = temp_store;
            }
        }
    }

    tmp_cnt = 0;

    for (int i = start; i < finnish; i++)
    {
        data[i] = temp[tmp_cnt++];
    }

    return 0;
}

int Matrix::addMatrix(Matrix &operandMatrix)
{
    int o_start = operandMatrix.get_start();
    int o_rows = operandMatrix.get_rows();
    int o_cols = operandMatrix.get_cols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i * cols + j + start] += data[i * o_cols + j + o_start];
        }
    }

    return 0;
}

int Matrix::MultiplyMatrix(Matrix &operandMatrix, Matrix &storeMatrix)
{
    if (cols != operandMatrix.get_rows())
    {
        cout << "multiplication not avaliable" << endl;
        return 1;
    }

    int o_start = operandMatrix.get_start();
    int o_cols = operandMatrix.get_cols();
    int s_start = storeMatrix.get_start();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < o_cols; j++)
        {
            data[s_start + o_cols * i + j] = 0;
            for (int k = 0; k < cols; k++)
            {
                data[s_start + o_cols * i + j] += data[start + i * cols + k] * data[o_start + o_cols * k + j];
            }
        }
    }

    return 0;
}

int Matrix::free = 0;
int *Matrix::data = new int[100]{-1};

int main(void)
{
    srand(time(NULL));

    Matrix *a = new Matrix(AROWS, ACOLS);
    Matrix *b = new Matrix(BROWS, BCOLS);
    Matrix *c = new Matrix(CROWS, CCOLS);
    Matrix *d = new Matrix(DROWS, DCOLS);
    Matrix *e = new Matrix(EROWS, ECOLS);

    a->show_data();
    b->show_data();
    c->show_data();
    d->show_data();
    e->show_data();

    cout << "[SORT]" << endl;
    a->sort_data();
    a->show_data();

    cout << "[ADD]" << endl;
    a->addMatrix(*b);
    a->show_data();

    cout << "[ADD 2]" << endl;
    b->addMatrix(*c);
    b->show_data();

    cout << "[MULTIPLY]" << endl;
    a->MultiplyMatrix(*b, *c);
    c->show_data();

    cout << "[MULTIPLY 2]" << endl;
    c->MultiplyMatrix(*d, *e);
    e->show_data();

    return 0;
}