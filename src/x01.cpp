
#include <algorithm>
#include <iostream>
#include <QList>
#include <QtAlgorithms>
#include <chrono>

const unsigned arraySize = 32768;
template<typename Vector> void test_branch_prediction(bool sorting, const char *type)
{
    
    Vector array;
    array.reserve(arraySize);

    for (unsigned c = 0; c < arraySize; c++) {
        array.push_back(std::rand() % 256);
    }

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    if (sorting) {
        std::sort(std::begin(array), std::end(array));
    }

    long long sum = 0;
    for (unsigned i = 0; i < 100000; i++) {
        for (unsigned c = 0; c < arraySize; ++c) {
            if (array.at(c) >= 128) {
                sum += array.at(c);
            }
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    int result = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    if (sorting) {
        std::cout << type << " with    sort, elapsed time: " << result << std::endl;
    } else {
        std::cout << type << " without sort, elapsed time: " << result << std::endl;
    }
}

int main(int argc, char **argv)
{
    test_branch_prediction<QVector<int>>(true,"QVector");
    test_branch_prediction<QVector<int>>(false, "QVector");
    
    test_branch_prediction<std::vector<int>>(true, "std::vector");
    test_branch_prediction<std::vector<int>>(false, "std::vector");

    return 0;
}
