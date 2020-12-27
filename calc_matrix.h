#ifndef CALC_MATRIX_H
#define CALC_MATRIX_H
#include "matrix.h"

class Calc_Matrix : public Matrix
{
private:
    /// *B - указатель на массив свободных членов; *X - массив корней;
    ///*D - массив определителей; **C - указатель на массив указателей коэффициентов матрицы
    double *B, *X, *D, **C; int K;
    double* confirm_equal();
public:
    Calc_Matrix();
    Calc_Matrix(int k) : Matrix(k) {
        K = k;
        B = new double [K];
        for (int i = 0; i < K; i++) B[i] = 0;
        X = new double [K];
        D = new double [K];
        for (int i = 0; i < K; i++) D[i] = 0;
    }
    void setB(int, double);
    double getX(int);
    void det_calc();
    void x_calc();
    bool IsZero();
    bool IsAllZeroDet();
    bool IsNotZeroAllDet();
    bool confirm_log();
    ~Calc_Matrix(void);
};

#endif // CALC_MATRIX_H
