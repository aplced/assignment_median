#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <time.h>
#include <chrono> 

#include "Median/median.h"
#include "int_median.h"

using namespace std;
using namespace std::chrono;

void testInputExpectedOutput(vector<int> testData, double expectedMedian)
{
    cout << "Test input [";
    auto md = MedianData<NumericData<int>>();
    for_each(
        testData.begin(), 
        testData.end(), 
        [&](int number)-> void
        {
            cout << number << ",";
            md.add_number(number);
        }
    );
    cout << "]" << endl;

    cout << "Expected [" << expectedMedian << "] Actual [" << md.median() << "]" << endl;
}

void stress_test()
{
    const int stressTestSize = 100000;
    cout << "Runnint stress_test of [" << stressTestSize << "] insertions" << endl;

    srand (time(NULL));
    auto md = MedianData<NumericData<int>>(stressTestSize + 1);
    auto insertionTimes = MedianData<NumericData<long long>>(stressTestSize + 1);

    long totalInsertionsRunTime = 0;
    NumericData<int> tmpData = NumericData<int>();
    NumericData<long long> tmpTime = NumericData<long long>();
    for (int i = 0; i < stressTestSize; i++)
    {
        tmpData.set_data(rand() % 100 + 1);
        auto start = high_resolution_clock::now();
        md.add_number(tmpData);
        auto stop = high_resolution_clock::now(); 
        tmpTime.set_data(duration_cast<nanoseconds>(stop - start).count()); 
        insertionTimes.add_number(tmpTime);
        totalInsertionsRunTime += duration_cast<nanoseconds>(stop - start).count();
    }

    cout << "Accumulated median value " << md.median() << " from " << stressTestSize << " random int insertions" << endl;
    cout << "Total time [" << totalInsertionsRunTime << "]ns Average time per insertion [" << totalInsertionsRunTime / stressTestSize << "]ns" << endl;
    cout << "Insertion times Min[" << insertionTimes.min() << "]ns Max[" << insertionTimes.max() << "]ns Median[" << insertionTimes.median() << "]ns" << endl;
}

int main()
{
    testInputExpectedOutput({ 3, 1, 2 }, 2);
    testInputExpectedOutput({ 3, 1, 4, 2 }, 2);
    testInputExpectedOutput({ 1, 2, 2, 3, 4, 7, 9 }, 3);
    testInputExpectedOutput({ 9, 2, 2, 3, 4, 7, 1 }, 3);
    testInputExpectedOutput({ 2, 9, 1, 3, 7, 4, 2 }, 3);

    stress_test();
}