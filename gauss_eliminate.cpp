#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <cmath>

using namespace std;
using namespace Eigen;

VectorXd solve(const MatrixXd &A, const MatrixXd &b)
{
    int m = A.rows();
    int n = A.cols();
    // cout << m << ", " << n << endl;
    // cout << A << endl;
    // cout << b << endl;
    MatrixXd M;
    M.resize(m, n + 1);
    // cout << M.rows() << ", " << M.cols() << endl;
    // M.block(0, 0, m, n) = A;
    // M.block(0, n - 1, m, 1) = b;
    // cout << M;
}

VectorXd solve(MatrixXd &M)
{
    int m = M.rows();
    int n = M.cols();
    // find pivot && eliminate to Row Echelo Form
    for (int i = 0; i < m - 1; i++)
    {
        // find row that has max pivot
        int r = i; // row that has max fabs(pivot)
        for (int ii = i + 1; ii < m; ii++)
        {
            if (fabs(M(ii, i)) > fabs(M(r, i)))
            {
                r = ii;
            }
        }
        cout << i << " max pivot row=" << r << endl;
        // swap rows
        if (r != i)
            M.row(i).swap(M.row(r));
        cout << M << endl;

        // row echelon form
        cout << "ref" << endl;
        for (int ii = i + 1; ii < m; ii++)
        {
            M.row(ii) += (-M(ii, i) / M(i, i)) * M.row(i);
        }
        cout << M << endl;

        cout << "---------------" << endl;
    }

    // reverse back
    cout << "reverse back" << endl;
    for (int i = m - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < n - 1; j++)
        {
            M(i, n - 1) -= M(i, j) * M(j, n - 1);
        }
        M(i, n - 1) /= M(i, i);
        cout << i << endl;
        cout << M << endl;
    }
    return M.col(n - 1);
}

int main()
{
    // MatrixXd A(3, 3);
    // MatrixXd b(3, 1);
    // A << 2, 1, -1,
    //     -3, -1, 2,
    //     -2, 1, 2;
    // b << 8, -11, -3;
    // solve(A, b);
    MatrixXd M(3, 4);
    M << 2, 1, -1, 8,
        -3, -1, 2, -11,
        -2, 1, 2, -3;
    VectorXd x = solve(M);
    cout << x << endl;
}