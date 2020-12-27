#include "calc_matrix.h"
#include <math.h>

void Calc_Matrix::setB(int column, double b)
{
       B[column] = b;
}

double Calc_Matrix::getX(int column)
{
    x_calc();
    return round(X[column] * 1000) / 1000;
}

void Calc_Matrix::det_calc()
{
    C = A_out();
    Matrix E(K);
    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < K; j++)
        {
            for (int m = 0; m < K; m++)
            {
                if (j == i)
                    E[m][j] = B[m];
                else
                    E[m][j] = C[m][j];
            }
        }
        D[i] = determinant(E, K);
    }
}

bool Calc_Matrix::IsZero()
{
    Matrix B(*this);
    double det = determinant(B, K);
    if (det == 0) return true;
    else return false;
}

bool Calc_Matrix::IsAllZeroDet()
{
   int k = 0;
   det_calc();
   for (int i = 0; i < K; i++)
       if (D[i] == 0) k++;
   if (k == K)
       return true;
   else
       return false;
}

bool Calc_Matrix::IsNotZeroAllDet()
{
    int k = 0;
    det_calc();
    for (int i = 0; i < K; i++)
        if (D[i] != 0) k++;
    if (k == K)
        return true;
    else
        return false;
}

void Calc_Matrix::x_calc()
{
    Matrix B(*this);
    double det = determinant(B, K);
    det_calc();
    for (int i = 0; i < K; i++)
    {
        X[i] = D[i] / det;
    }
}

double* Calc_Matrix::confirm_equal()
{
    C = A_out();
    double* V = new double [K];
    for (int i = 0; i < K; i++)
    {
        V[i] = 0;
        for (int j = 0; j < K; j++)
            V[i] += C[i][j] * X[j];
    }
    return V;
}

bool Calc_Matrix::confirm_log()
{
    double* V = confirm_equal();
    double e = 0.0001;
    for (int i = 0; i < K; i++)
        if (V[i] - B[i] > e)
            return false;
    return true;
}

Calc_Matrix::~Calc_Matrix(void)
{
    delete [] B;
    delete [] X;
    delete [] D;
}
