#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <time.h>
#include <chrono> 

#include "NumericData.h"
#include "Median/MedianData.h"

using namespace std;
using namespace std::chrono;

void testInputExpectedOutput(vector<int> testData, double expectedMedian)
{
    cout << "Test input [";
    auto md = MedianData<NumericData<int>, double>();
    for_each(
        testData.begin(), 
        testData.end(), 
        [&](int number)-> void
        {
            cout << number << ",";
            md.add_number(number);
        }
    );
    cout << "]\t";

    cout << "Expected [" << expectedMedian << "]\tActual [" << md.median() << "]\t" << (expectedMedian == md.median() ? "PASS" : "FAIL") << endl;
}

void stress_test()
{
    const int stressTestSize = 10000000;
    cout << "Running stress_test of [" << stressTestSize << "] insertions" << endl;

    srand (time(NULL));
    auto md = MedianData<NumericData<int>, double>();

    long totalInsertionsRunTime = 0;
    auto tmpData = NumericData<int>();
    for (int i = 0; i < stressTestSize; i++)
    {
        tmpData.set_data(rand() % 100 + 1);
        auto start = high_resolution_clock::now();
        md.add_number(tmpData);
        auto stop = high_resolution_clock::now(); 
        totalInsertionsRunTime += duration_cast<nanoseconds>(stop - start).count();
    }

    cout << "Accumulated median value " << md.median() << " from " << stressTestSize << " random int insertions" << endl;
    cout << "Total time [" << totalInsertionsRunTime << "]ns Average time per insertion [" << totalInsertionsRunTime / stressTestSize << "]ns" << endl;
}

int main()
{
    testInputExpectedOutput({ 3, 1, 2 }, 2);
    testInputExpectedOutput({ 3, 1, 4, 2 }, 2.5);
    testInputExpectedOutput({ 1, 2, 2, 3, 4, 7, 9 }, 3);
    testInputExpectedOutput({ 9, 2, 2, 3, 4, 7, 1 }, 3);
    testInputExpectedOutput({ 2, 9, 1, 3, 7, 4, 2 }, 3);

    stress_test();
}