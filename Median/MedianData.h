#ifndef __MEDIAN_H__
#define __MEDIAN_H__

#include <algorithm>
#include <queue>

#include "ComparableData.h"

template <typename Data, typename MedianType> 
class MedianData
{
    public:
        MedianData() 
        {
            static_assert(std::is_base_of<ComparableData<Data, MedianType>, Data>::value, "type parameter of this class must derive from ComparableData<Data>");

            medianValue = Data::max_median();
            leftHeap = std::priority_queue<Data>();
            rightHeap = std::priority_queue<Data, std::vector<Data>, std::greater<Data>>(); 
        }

        void add_number(Data data)
        {
            totalDataItems++;

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

            if(data > maxValue)
            {
                maxValue = data;
            }

            if(data < minValue)
            {
                minValue = data;
            }

            totalValue += data;
        }

        MedianType median() const
        {
            return medianValue;
        }

        int size() const
        {
            return totalDataItems;
        }

        Data max() const
        {
            return maxValue;
        }

        Data min() const
        {
            return minValue;
        }

        Data total() const
        {
            return totalValue;
        }

        Data mean() const
        {
            return totalValue/totalDataItems;
        }

    private:
        //Holds a precomputed current median value
        MedianType medianValue;
        Data maxValue;
        Data minValue;
        Data totalValue;
        int totalDataItems;

        std::priority_queue<Data> leftHeap;
        std::priority_queue<Data, std::vector<Data>, std::greater<Data>> rightHeap;

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
