#include <iostream>
using namespace std;

struct Matrix {
    // двумерный массив с данными.
    int** data_ = nullptr;
    // количество столбцов
    size_t n_ = 0u;
    // количество строк
    size_t m_ = 0u;
};

// Создает заполненную нулями матрицу n x m.
void Construct(Matrix& out, size_t n, size_t m) {
    out.m_ = m;
    out.n_ = n;
    out.data_ = new int*[n];
    for (int i = 0; i < n; ++i) {
        out.data_[i] = new int[m];
        for (int j = 0; j < m; ++j) {
            out.data_[i][j] = 0;
        }
    }
}

// Освобождает выделенную память.
void Destruct(Matrix& in){
    for (int i = 0; i < in.n_; i++)
        delete[] in.data_[i];
    delete[] in.data_;
}

// Создает копию матрицы |matrix|.
Matrix Copy(const Matrix& matrix){
    Matrix res{};
    res.n_ = matrix.n_;
    res.m_ = matrix.m_;
    res.data_ = new int*[res.n_];
    for (int i = 0; i < res.n_; ++i) {
        res.data_[i] = new int[res.m_];
        for (int j = 0; j < res.m_; ++j) {
            res.data_[i][j] = matrix.data_[i][j];
        }
    }
    return res;
}
// Возвращает сумму двух матриц.
// Если операция невозможна - вернуть пустую матрицу
Matrix Add(const Matrix& a, const Matrix& b){
    Matrix res{};
    if ((a.n_ != b.n_) || (a.m_ != b.m_))
        return res;
    res.n_ = a.n_;
    res.m_ = a.m_;
    res.data_ = new int*[res.n_];
    for (int i = 0; i < res.n_; ++i) {
        res.data_[i] = new int[res.m_];
        for (int j = 0; j < res.m_; ++j) {
            res.data_[i][j] = a.data_[i][j] + b.data_[i][j];
        }
    }
    return res;

}
// Возвращает разницу двух матриц.
// Если операция невозможна - вернуть пустую матрицу
Matrix Sub(const Matrix& a, const Matrix& b){
    Matrix res{};
    if ((a.n_ != b.n_) || (a.m_ != b.m_))
        return res;
    res.n_ = a.n_;
    res.m_ = a.m_;
    res.data_ = new int*[res.n_];
    for (int i = 0; i < res.n_; ++i) {
        res.data_[i] = new int[res.m_];
        for (int j = 0; j < res.m_; ++j) {
            res.data_[i][j] = a.data_[i][j] - b.data_[i][j];
        }
    }
    return res;
}
// Возвращает произведение двух матриц.
// Если операция невозможна - вернуть пустую матрицу
Matrix Mult(const Matrix& a, const Matrix& b){
    Matrix res{};
    if (a.m_ != b.n_)
        return res;
    res.n_ = a.n_;
    res.m_ = b.m_;
    res.data_ = new int*[res.n_];
    for (int i = 0; i < res.n_; ++i) {
        res.data_[i] = new int[res.m_];
        for (int j = 0; j < res.m_; ++j) {
            res.data_[i][j] = 0;
            for (int k = 0; k < a.m_; k++){
                res.data_[i][j] += a.data_[i][k]*b.data_[k][j];
            }
        }
    }
    return res;
}

// Транспонирование матрицы.
void Transposition(Matrix& matrix){
    Matrix res{};
    res.n_ = matrix.m_;
    res.m_ = matrix.n_;
    res.data_ = new int*[res.n_];
    for (int i = 0; i < res.n_; i++) {
        res.data_[i] = new int[res.m_];
        for (int j = 0; j < res.m_; j++) {
            res.data_[i][j] = matrix.data_[j][i];
        }
    }
    matrix.n_ = res.n_;
    matrix.m_ = res.m_;
    matrix.data_ = res.data_;
}

// Сравнение двух матриц.
bool operator==(const Matrix& a, const Matrix& b){
    if ((a.n_ != b.n_) || (a.m_ != b.m_))
        return false;
    for (int i = 0; i < a.n_; ++i) {
        for (int j = 0; j < a.m_; ++j) {
            if (a.data_[i][j] != b.data_[i][j]){
                return false;
            }
        }
    }
    return true;
}
int main(){
    Matrix m1;
    Construct(m1,5,5);
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 6; ++j)
            m1.data_[i][j] = 5;
    }

    Matrix m2;
    Construct(m2,4,6);
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 6; ++j){
            m2.data_[i][j] = i+j;
        }
    }

    Matrix m3 = Add(m1, Copy(m1));
    Matrix m5 = Sub(m3, m1);
    cout << (m1 == m5) << endl;
    cout << (m1 == m2) << endl;

    Matrix m4 = Copy(m1);
    Transposition(m2); //та же
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            cout << m2.data_[i][j]<< " ";
        }
        cout << endl;
    }
    cout << endl;
    Matrix m6 = Mult(m1, m5);
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            cout << m6.data_[i][j]<< " ";
        }
        cout << endl;
    }

    Destruct(m1);
    Destruct(m2);
    Destruct(m3);
    Destruct(m4);
    Destruct(m5);
    Destruct(m6);
    return 0;
}
