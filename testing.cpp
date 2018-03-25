#include <iostream>
#include <ctime>
#include "matrix.hpp"
using namespace std;

int main()
{
    cout << "***************** TESTING RESULTS *****************\n\n";
    Matrix<int> A(3, 4);
    Matrix<int> B(4, 3);
    Matrix<int> C(3, 4);
    Matrix<int> R;

    srand(time(0));

    for(int i(0); i < A.getRows(); i++){
        for(int j(0); j < A.getColumns(); j++){
            A[i][j] = rand() % 200 - 100;
        }
    }

    for(int i(0); i < B.getRows(); i++){
        for(int j(0); j < B.getColumns(); j++){
            B[i][j] = rand() % 200 - 100;
        }
    }

    for(int i(0); i < C.getRows(); i++){
        for(int j(0); j < C.getColumns(); j++){
            C[i][j] = rand() % 200 - 100;
        }
    }

    cout << "A =\n" << A.toString() << "\n";
    cout << "\nB =\n" << B.toString() << "\n";
    cout << "\nC =\n" << C.toString() << "\n";

    R = A * B;
    cout << "\nA*B =\n" << R.toString() << "\n";
    R = A + C;
    cout << "\nA+C =\n" << R.toString() << "\n";
    R = C * 3;
    cout << "\nC*3 =\n" << R.toString() << "\n";
    C -= A;
    cout << "\nC -= A =\n" << C.toString() << "\n";
    B.decreaseAllBy(7);
    cout << "\nDecreasing all values of B by 7 =\n" << B.toString() << "\n";


    cout << "\n\n***************** TESTING SPEED *****************\n\n";
    int mtxSize(512);
    Matrix<float> D(mtxSize, mtxSize);
    Matrix<float> E(mtxSize, mtxSize);
    Matrix<float> F(mtxSize, mtxSize);

    for(int i(0); i < D.getRows(); i++){
        for(int j(0); j < D.getColumns(); j++){
            D[i][j] = (rand() % 2000 - 1000) / 10.0;
        }
    }

    for(int i(0); i < E.getRows(); i++){
        for(int j(0); j < E.getColumns(); j++){
            E[i][j] = (rand() % 2000 - 1000) / 10.0;
        }
    }

    clock_t t0, tf;
    cout << "Size of D: " << D.getRows() << " x " << D.getColumns() << "\n";
    cout << "Size of E: " << E.getRows() << " x " << E.getColumns() << "\n\n";

    t0 = clock();
    D + E;
    tf = clock();
    cout << "Operation: D+E      Time: " << (tf - t0) / (float)CLOCKS_PER_SEC << "s\n";
    t0 = clock();
    D - E;
    tf = clock();
    cout << "Operation: D-E      Time: " << (tf - t0) / (float)CLOCKS_PER_SEC << "s\n";
    t0 = clock();
    D * E;
    tf = clock();
    cout << "Operation: D*E      Time: " << (tf - t0) / (float)CLOCKS_PER_SEC << "s\n";
    t0 = clock();
    D * 4;
    tf = clock();
    cout << "Operation: D*4      Time: " << (tf - t0) / (float)CLOCKS_PER_SEC << "s\n";
    t0 = clock();
    F = D;
    tf = clock();
    cout << "Operation: F = D      Time: " << (tf - t0) / (float)CLOCKS_PER_SEC << "s\n";
    t0 = clock();
    D += E;
    tf = clock();
    cout << "Operation: D += E      Time: " << (tf - t0) / (float)CLOCKS_PER_SEC << "s\n";
    t0 = clock();
    D -= E;
    tf = clock();
    cout << "Operation: D -= E      Time: " << (tf - t0) / (float)CLOCKS_PER_SEC << "s\n";
    t0 = clock();
    D *= E;
    tf = clock();
    cout << "Operation: D *= E      Time: " << (tf - t0) / (float)CLOCKS_PER_SEC << "s\n";
    t0 = clock();
    D *= 2;
    tf = clock();
    cout << "Operation: D *= 2      Time: " << (tf - t0) / (float)CLOCKS_PER_SEC << "s\n";
    t0 = clock();
    D.increaseAllBy(3);
    tf = clock();
    cout << "Operation: Increase all values of D by 3      Time: " << (tf - t0) / (float)CLOCKS_PER_SEC << "s\n";
    t0 = clock();
    D.decreaseAllBy(5);
    tf = clock();
    cout << "Operation: Decrease all values of D by 5      Time: " << (tf - t0) / (float)CLOCKS_PER_SEC << "s\n";
}
