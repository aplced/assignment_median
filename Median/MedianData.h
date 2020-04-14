#ifndef __MEDIAN_H__
#define __MEDIAN_H__

#include <algorithm>
#include <queue>

#include "ComparableData.h"

using namespace std;

template <typename Data, typename MedianType> 
class MedianData
{
    public:
        MedianData() 
        {
            static_assert(std::is_base_of<ComparableData<Data, MedianType>, Data>::value, "type parameter of this class must derive from ComparableData<Data>");

            medianValue = Data::max_median();
            leftHeap = priority_queue<Data>();
            rightHeap = priority_queue<Data, vector<Data>, greater<Data>>(); 
        }

        void add_number(Data data)
        {
            if (leftHeap.size() > rightHeap.size()) 
            { 
                add_to_heap_left_larger(data);   
            }
            else if(leftHeap.size() < rightHeap.size())
            { 
                add_to_heap_right_larger(data);
            }
            else //if (leftHeap.size() == rightHeap.size()) 
            { 
                add_to_heap_equal(data);
            }
        }

        MedianType median() const
        {
            return medianValue;
        }

    private:
        //Holds a precomputed current median value
        MedianType medianValue;

        priority_queue<Data> leftHeap;
        priority_queue<Data, vector<Data>, greater<Data>> rightHeap;

        //Balances the two heaps and adds the new data based on the position to the median
        void add_to_heap_left_larger(const Data& data)
        {
            if (data.compare(medianValue) < 0) 
            { 
                rightHeap.push(leftHeap.top()); 
                leftHeap.pop(); 
                leftHeap.push(data); 
            } 
            else
            {
                rightHeap.push(data); 
            }
            medianValue = leftHeap.top().median_with(rightHeap.top()); 
        }
        
        //Balances the two heaps and adds the new data based on the position to the median
        void add_to_heap_right_larger(const Data& data)
        {
            if (data.compare(medianValue) > 0) 
            { 
                leftHeap.push(rightHeap.top()); 
                rightHeap.pop(); 
                rightHeap.push(data); 
            } 
            else
            {
                leftHeap.push(data); 
            }
            medianValue = leftHeap.top().median_with(rightHeap.top()); 
        }
        
        //Adds the new data to the already balanced heaps based on the position to the median
        void add_to_heap_equal(const Data& data)
        {
            if (data.compare(medianValue) < 0) 
            { 
                leftHeap.push(data); 
                medianValue = leftHeap.top().as_median(); 
            } 
            else
            { 
                rightHeap.push(data); 
                medianValue = rightHeap.top().as_median(); 
            }
        }
};

#endif
