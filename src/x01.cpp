
#include <algorithm>
#include <ctime>
#include <iostream>
#include <QtAlgorithms>

const unsigned arraySize = 32768;

inline void stlVersion(bool sorting)
{
    clock_t start_time = clock();
    {
        int data[arraySize];
        for (unsigned c = 0; c < arraySize; c++) {
            data[c] = std::rand() % 256;
        }
        if (sorting) {
            std::sort(data, data + arraySize);
        }
        long long sum = 0;
        for (unsigned i = 0; i < 100000; i++) {
            for (unsigned c = 0; c < arraySize; ++c) {
                if (data[c] >= 128)
                    sum += data[c];
            }
        }
    }
    double elapsed_time = static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC;
    if (sorting) {
        std::cout << "STL Version, with sort, elapsed time: " << elapsed_time << std::endl;
    } else {
        std::cout << "STL Version, without sort, elapsed time: " << elapsed_time << std::endl;
    }
}

inline void qtVersion(bool sorting)
{
    clock_t start_time = clock();
    {
        int data[arraySize];
        for (unsigned c = 0; c < arraySize; c++) {
            data[c] = std::rand() % 256;
        }
        if (sorting) {
            qSort(data.begin(), data.end());
        }
        long long sum = 0;
        for (unsigned i = 0; i < 100000; i++) {
            for (unsigned c = 0; c < arraySize; ++c) {
                if (data[c] >= 128) {
                    sum += data[c];
                }
            }
        }
    }
    double elapsed_time = static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC;
    if (sorting) {
        std::cout << "Qt Version, with sort, elapsed time: " << elapsed_time << std::endl;
    } else {
        std::cout << "Qt Version, without sort, elapsed time: " << elapsed_time << std::endl;
    }
}

int main(int argc, char **argv)
{
    stlVersion(true);
    stlVersion(false);

    qtVersion(true);
    qtVersion(false);

    return 0;
}
