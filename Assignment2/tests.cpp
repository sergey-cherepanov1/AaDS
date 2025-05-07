/* Sergey Cherepanov st129987@student.spbu.ru
   Assignment2
*/

#include <gtest/gtest.h>
#include "gauss.h"

TEST(GaussTests, SimpleSystem) {
    Eigen::MatrixXd A(2, 3);
    A << 1, 2, 5,
         3, 4, 11;
    Eigen::VectorXd expected(2);
    expected << 1, 2;
    Eigen::VectorXd result = solve(A);
    ASSERT_TRUE(result.isApprox(expected, 1e-6));
}

TEST(GaussTests, ThreeByFourSystem) {
    Eigen::MatrixXd A(3, 4);
    A << 1, 2, 3, 14,
         2, -1, 1, 3,
         3, 1, -2, 0;
    Eigen::VectorXd expected(3);
    expected << 7.0/6.0, 13.0/6.0, 17.0/6.0;
    Eigen::VectorXd result = solve(A);
    ASSERT_TRUE(result.isApprox(expected, 1e-6));
}

TEST(GaussTests, ZeroPivot) {
    Eigen::MatrixXd A(2, 3);
    A << 0, 0, 1,
         0, 0, 2;
    ASSERT_THROW(solve(A), std::runtime_error);
}

TEST(GaussTests, InconsistentSystem) {
    Eigen::MatrixXd A(2, 3);
    A << 1, 1, 2,
         0, 0, 1;
    ASSERT_THROW(solve(A), std::runtime_error);
}

TEST(GaussTests, UnderdeterminedSystem) {
    Eigen::MatrixXd A(1, 3);
    A << 1, 2, 3;
    ASSERT_THROW(solve(A), std::runtime_error);
}

TEST(GaussTests, LargeRandomSystem) {
    int n = 10;
    unsigned int seed = 42;
    Eigen::MatrixXd A = generateRandomMatrix(n, n, seed);
    Eigen::VectorXd x(n);
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    for (int i = 0; i < n; ++i) {
        x(i) = dist(gen);
    }
    Eigen::VectorXd b = A * x;
    Eigen::MatrixXd augmented(n, n + 1);
    augmented.block(0, 0, n, n) = A;
    augmented.col(n) = b;
    Eigen::VectorXd result = solve(augmented);
    ASSERT_TRUE(result.isApprox(x, 1e-3));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
