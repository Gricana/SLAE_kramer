#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
    int N; double **A;
public:
    Matrix();
    Matrix(int);
    Matrix(const Matrix&);
    ~Matrix(void);
    double* operator [] (int);
    void setA(int, int, double);
protected:
    double** A_out() {return A;}
    double determinant(Matrix&, int);
};

#endif // MATRIX_H
