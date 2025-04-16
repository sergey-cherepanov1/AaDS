#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <Eigen/Dense>

Eigen::MatrixXd readCSV(std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<double>> data;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            row.push_back(std::stod(cell));
        }
        data.push_back(row);
    }

    Eigen::MatrixXd mat(data.size(), data[0].size());
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[0].size(); ++j) {
            mat(i, j) = data[i][j];
        }
    }
    return mat;
}

void writeCSV(std::string& filename, Eigen::VectorXd& x) {
    std::ofstream file(filename);
    for (Eigen::Index i = 0; i < x.size(); ++i) {
        file << x(i);
        if (i != x.size() - 1) file << ",";
    }
}

int main() {
    
    return 0;
}
