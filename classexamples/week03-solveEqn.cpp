#include <iostream>
#include <Eigen/Dense>

int main()
{
    // Solve the system of linear equations
    // 2x + y = 5
    // -x + y = 2
    // [ 2  1][x] = [5]
    // [-1  1][y] = [2]
    // Ax = p
    Eigen::MatrixXd A(2, 2);
    Eigen::MatrixXd x(2, 1);
    Eigen::MatrixXd p(2, 1);

    A(0,0) =  2; A(0,1) = 1;
    A(1,0) = -1; A(1,1) = 1;

    p(0,0) = 5;
    p(1,0) = 2;

    x = A.inverse() * p;
    std::cout << "x = " << x(0,0) << std::endl;
    std::cout << "y = " << x(1,0) << std::endl;
}

