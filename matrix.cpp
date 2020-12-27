#include <math.h>
#include "matrix.h"

double* Matrix::operator[] (int j)
{
    return A[j];
}

void Matrix::setA(int row, int column, double item)
{
    A[row][column] = item;
}

Matrix::Matrix(const Matrix& q)
{
    N = q.N;
    A = new double*[N];
    for (int i = 0; i < N;i++)
        A[i] = new double[N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = q.A[i][j];
}

// выделение памяти для матрицы и инициализация её нулями
Matrix::Matrix(int n)
{
    N = n;
    A = new double *[N];
    for (int i = 0; i < N; i++)
        A[i] = new double [N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = 0;
}

// метод нахождения детерминанта матрицы А
double Matrix::determinant(Matrix& a, int n)
{
    double det = 1;
    if (n == 1) {det = a[0][0]; return det;}
    if (n == 2) {det = a[0][0] * a[1][1] - a[0][1] * a[1][0]; return det;}
    if (n > 2) {
           int i, j, k, r; double c, M, max;

           for(k = 0; k < n; k++)
           {
                max = abs(a[k][k]);
                r = k;
                for(i = k + 1; i < n; i++)
                    if (abs(a[i][k]) > max)
                    {
                        max=abs(a[i][k]);
                        r = i;
                    }
                if (r != k) det = -det;
                for(j = 0; j < n; j++)
                {
                    c = a[k][j];
                    a[k][j] = a[r][j];
                    a[r][j] = c;
                }
                for(i = k + 1; i < n; i++)
                    for(M = a[i][k] / a[k][k], j = k; j < n; j++)
                        a[i][j] -= M * a[k][j];
           }
           for(i = 0; i < n; i++)
               det *= a[i][i];
        }
    return det;
}

Matrix::~Matrix(void)
{
    for (int i = 0; i < N; i++)
        delete [] A[i];
    delete [] A;
}
