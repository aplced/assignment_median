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
    MedianData<IntData> md = MedianData<IntData>();
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
    const int stressTestSize = 1000000;
    srand (time(NULL));
    MedianData<IntData> md = MedianData<IntData>();
    MedianData<IntData> insertionTimes = MedianData<IntData>();

    auto testStart = high_resolution_clock::now();
    for (int i = 0; i < stressTestSize; i++)
    {
        auto start = high_resolution_clock::now(); 
        md.add_number(rand());
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<nanoseconds>(stop - start); 
        insertionTimes.add_number(duration.count());
    }
    auto testStop = high_resolution_clock::now();
    auto testDuration = duration_cast<nanoseconds>(testStop - testStart); 

    cout << "Accumulated median value " << md.median() << " from " << stressTestSize << " random int insertions" << endl;
    cout << "Times in nanoseconds" << endl;
    cout << "Total time [" << testDuration.count() << "] Average time per insertion ]" << testDuration.count() / stressTestSize << "]" << endl;
    cout << "Insertion times Min[" << insertionTimes.min() << "] Max[" << insertionTimes.max() << "] Median[" << insertionTimes.median() << "]" << endl;
}

int main()
{
    cout << "Running sanity tests" << endl;
    testInputExpectedOutput({ 1, 2, 2, 3, 4, 7, 9 }, 3);
    testInputExpectedOutput({ 9, 2, 2, 3, 4, 7, 1 }, 3);
    testInputExpectedOutput({ 2, 9, 1, 3, 7, 4, 2 }, 3);

    cout << "Runnint stress_test:" << endl;
    stress_test();
}