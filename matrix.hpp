#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

/// -------- EXCEPTIONS --------
class MatrixException : public exception {
  private:
    string msg;

  public:
    explicit MatrixException(const char* message) : msg(message) {}
    explicit MatrixException(const string& message): msg(message) {}
    virtual ~MatrixException() throw() {}
    virtual const char* what() const throw() {
        return msg.c_str();
    }
};

/// -------- MATRIX PROTOTYPE --------
template <class T>
class Matrix {
  private:
    int rows;
    int columns;
    vector <vector <T>> data;

    void setToZero();
    void copyMatrix(const Matrix<T>&);

  public:
    /* Set of constructors, that allows the Matrix to be
    initialized either by default, by row and column size,
    or copying an existing Matrix*/
    Matrix();
    Matrix(const int&, const int&);
    Matrix(const Matrix<T>&);

    int getRows();
    int getColumns();

    /* Method overloading the operator [] that allows the values
    of the Matrix to be accessed by [row][column] coordinates*/
    vector<T>& operator [] (size_t);

    /* Couple of methods that increase or decrease all values in a
    Matrix by the same constant. These methods use Generic Lambdas. */
    void increaseAllBy(const T&);
    void decreaseAllBy(const T&);

    /* Set of methods overloading common math operators to do
    Matrix operations. If the operation is not possible due to the
    size of the Matrices, the method will throw a MatrixException*/
    Matrix<T> operator + (const Matrix<T>&);
    Matrix<T> operator - (const Matrix<T>&);
    Matrix<T> operator * (const Matrix<T>&);
    Matrix<T> operator * (const T&);
    Matrix<T>& operator = (const Matrix<T>&);

    void operator += (const Matrix<T>&);
    void operator -= (const Matrix<T>&);
    void operator *= (const Matrix<T>&);
    void operator *= (const T&);

    /* Method that returns a string of the Matrix
    to print it out in a visual representation.*/
    string toString();
};

/// -------- MATRIX IMPLEMENTATION --------

/// Private Methods
template <class T>
void Matrix<T>::setToZero(){
    for_each(data.begin(), data.end(), [](vector<T>& vec){
        for_each(vec.begin(), vec.end(), [](T& elem){
            elem = 0;
        });
    });
}

template <class T>
void Matrix<T>::copyMatrix(const Matrix<T>& mtx){
    rows = mtx.rows;
    columns = mtx.columns;
    data.resize(rows, vector<T>(columns));

    for(int i(0); i < rows; i++){
        for(int j(0); j < columns; j++){
            data[i][j] = mtx.data[i][j];
        }
    }
}

/// Public Methods
template <class T>
Matrix<T>::Matrix() : rows(3), columns(3) {
    data.resize(rows, vector<T>(columns));
    setToZero();
}

template <class T>
Matrix<T>::Matrix(const int& r, const int& c) {
    rows = r;
    columns = c;
    data.resize(rows, vector<T>(columns));
    setToZero();
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& mtx) {
    copyMatrix(mtx);
}

template <class T>
int Matrix<T>::getRows() {
    return rows;
}

template <class T>
int Matrix<T>::getColumns() {
    return columns;
}

template <class T>
vector<T>& Matrix<T>::operator [] (size_t i) {
    return data[i];
}

template <class T>
void Matrix<T>::increaseAllBy(const T& num) {
    for_each(data.begin(), data.end(), [n = num](vector<T>& vec){
        for_each(vec.begin(), vec.end(), [&](T& elem){
            elem += n;
        });
    });
}

template <class T>
void Matrix<T>::decreaseAllBy(const T& num) {
    for_each(data.begin(), data.end(), [n = num](vector<T>& vec){
        for_each(vec.begin(), vec.end(), [&](T& elem){
            elem -= n;
        });
    });
}


template <class T>
Matrix<T> Matrix<T>::operator + (const Matrix<T>& rhs) {
    if(rows != rhs.rows || columns != rhs.columns){
        throw MatrixException("operator +: The matrices are not the same size.");
    }
    Matrix<T> result(rows, columns);
    for(int i(0); i < rows; i++){
        for(int j(0); j < columns; j++){
            result.data[i][j] = data[i][j] + rhs.data[i][j];
        }
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator - (const Matrix<T>& rhs) {
    if(rows != rhs.rows || columns != rhs.columns){
        throw MatrixException("operator -: The matrices are not the same size.");
    }
    Matrix<T> result(rows, columns);
    for(int i(0); i < rows; i++){
        for(int j(0); j < columns; j++){
            result.data[i][j] = data[i][j] - rhs.data[i][j];
        }
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator * (const Matrix<T>& rhs) {
    if(columns != rhs.rows){
        throw MatrixException("operator *: The matrices are not the required row and column size to multiply each other.");
    }

    Matrix<T> result(rows, rhs.columns);
    for(int i(0); i < rows; i++){
        for(int j(0); j < columns; j++){
            for(int k(0); k < columns; k++){
                result[i][j] += data[i][k] * rhs.data[k][j];
            }
        }
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator * (const T& num) {
    Matrix<T> result(rows, columns);
    for(int i(0); i < rows; i++){
        for(int j(0); j < columns; j++){
            result.data[i][j] = data[i][j] * num;
        }
    }

    return result;
}

template <class T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& rhs){
    copyMatrix(rhs);
    return *this;
}

template <class T>
void Matrix<T>::operator += (const Matrix<T>& rhs) {
    *this = *this + rhs;
}

template <class T>
void Matrix<T>::operator -= (const Matrix<T>& rhs) {
    *this = *this - rhs;
}

template <class T>
void Matrix<T>::operator *= (const Matrix<T>& rhs) {
    *this = *this * rhs;
}

template <class T>
void Matrix<T>::operator *= (const T& num) {
    *this = *this * num;
}

template <class T>
string Matrix<T>::toString(){
    string result;

    for(int i(0); i < columns; i++){
        result += " _______";
    }

    for(int i(0); i < rows; i++){
        result += "\n| ";
        for(int j(0); j <columns; j++){
            result += to_string(data[i][j]) + "\t| ";
        }

        result += "\n";
        for(int j(0); j < columns; j++){
            result += " _______";
        }
    }

    return result;
}

#endif // MATRIX_HPP_INCLUDED
