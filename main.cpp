#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <time.h>
#include <chrono> 

#include "Median/NumericComparableData.h"
#include "Median/MedianData.h"

using namespace std;
using namespace std::chrono;

void testInputExpectedOutput(vector<int> testData, double expectedMedian)
{
    cout << "Test input [";
    auto md = MedianData<NumericComparableData<int>, double>();
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
    const int stressTestSize = 100000000;
    cout << "Running stress_test of [" << stressTestSize << "] insertions" << endl;

    srand (time(NULL));
    auto md = MedianData<NumericComparableData<int>, double>();
    auto insertionTimes = MedianData<NumericComparableData<unsigned long long>, double>();
    for (int i = 0; i < stressTestSize; i++)
    {
        auto start = high_resolution_clock::now();
        md.add_number(rand());
        auto stop = high_resolution_clock::now(); 
        insertionTimes.add_number(duration_cast<nanoseconds>(stop - start).count());
    }

    cout << "Accumulated median value " << md.median() << " from " << stressTestSize << " random int insertions" << endl;
    cout << "Total time [" << insertionTimes.total() << "]ns Average time per insertion [" << insertionTimes.mean() << "]ns" << endl;
    cout << "Insertion times Min[" << insertionTimes.min() << "]ns Max[" << insertionTimes.max() << "]ns Median[" << insertionTimes.median() << "]ns" << endl;
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