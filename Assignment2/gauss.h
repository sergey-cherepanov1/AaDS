/* Sergey Cherepanov st129987@student.spbu.ru
   Assignment2
*/

#ifndef GAUSS_H
#define GAUSS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <random>
#include <Eigen/Dense>

Eigen::MatrixXd readCSV(std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Не удалось открыть файл " + filename);
    }
    std::vector<std::vector<double>> data;
    std::string line;

    while (std::getline(file, line))
    {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ','))
        {
            row.push_back(std::stod(cell));
        }
        data.push_back(row);
    }

    Eigen::MatrixXd mat(data.size(), data[0].size());
    for (size_t i = 0; i < data.size(); ++i)
    {
        for (size_t j = 0; j < data[0].size(); ++j)
        {
            mat(i, j) = data[i][j];
        }
    }
    return mat;
}

void writeCSV(std::string& filename, Eigen::VectorXd& x)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
    }
    for (Eigen::Index i = 0; i < x.size(); ++i)
    {
        file << x(i);
        if (i != x.size() - 1) file << ",";
    }
    file << "\n";
    file.close();
}

Eigen::VectorXd solve(Eigen::MatrixXd A)
{
    if (A.rows() < A.cols()-1)
    {
        throw std::runtime_error("Ошибка: число уравнений меньше числа переменных. Решение невозможно.\n");
    }

    for (int c = 0; c < A.rows() - 1; ++c)
    {
        double value = 0;
        for (int r = c; r < A.rows(); ++r)
        {
            if (A(r, c) != 0)
            {
                value = A(r, c);
                A.row(r).swap(A.row(c));
                break;
            }
        }
        if (value == 0)
        {
            throw std::runtime_error("Ошибка: ведущий элемент равен нулю(нулевой столбец)\n");
        }
        
        A.row(c) /= value;

        for (int r = c + 1; r < A.rows(); ++r)
        {
            A.row(r) -= A.row(c) * A(r, c);
        }
    }

    int n = A.cols();
    Eigen::MatrixXd temp(A.rows(), n);
    int new_row_idx = 0;

    for (int i = 0; i < A.rows(); ++i)
    {
        bool all_zero_coeffs = (A.row(i).head(n - 1).array() == 0).all();
        if (all_zero_coeffs)
        {
            if (A(i, n - 1) != 0)
            {
                throw std::runtime_error("Ошибка: строка с нулевыми коэффициентами, но свободный член не равен нулю\n");
            }
        }
        else
        {
            temp.row(new_row_idx++) = A.row(i);
        }
    }

    Eigen::MatrixXd A_clean = temp.topRows(new_row_idx);

    if (A_clean.rows() != n - 1)
    {
        throw std::runtime_error("Ошибка: число уравнений не совпадает с числом неизвестных\n");
    }
    
    int v = A_clean.rows();
    Eigen::VectorXd ans(v);
    for (int i = v - 1; i >= 0; --i)
    {
        double s = 0.0;
        for (int j = i + 1; j < v; ++j)
        {
            s += A_clean(i, j)  * ans(j);
        }
        ans(i) = (A_clean(i, v) - s) / A_clean(i, i);
    }
    
    return ans;
}

Eigen::MatrixXd generateRandomMatrix(int rows, int cols, unsigned int seed)
{
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    Eigen::MatrixXd mat(rows, cols);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            mat(i, j) = dist(gen);
        }
    }
    return mat;
}

#endif
