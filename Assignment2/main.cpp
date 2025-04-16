/* Sergey Cherepanov st129987@student.spbu.ru
   LabWork2
*/

#include "gauss.h"
#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter file name: ";
    std::string filename;
    std::cin >> filename;

    Eigen::MatrixXd A = readCSV(filename);
    Eigen::VectorXd solution = solve(A);
    std::cout << solution << "\n";

    std::string out_filename = "output.csv";
    writeCSV(out_filename, solution);

    return 0;
}
