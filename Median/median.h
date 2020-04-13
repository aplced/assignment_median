#ifndef __MEDIAN_H__
#define __MEDIAN_H__

#include <vector>

using namespace std;

template <class Data>
class ComperableData
{
    virtual int compare(const Data& otherData) = 0;
};

template <class Data> class MedianData
{
    public:
        MedianData() 
        {
            static_assert(std::is_base_of<ComperableData<Data>, Data>::value, "type parameter of this class must derive from ComperableData<Data>");

            medianValue = 0;
            numberData = vector<Data>();
        }

        void add_number(Data number)
        {
            if(numberData.empty())
            {
                numberData.push_back(number);
                medianValue = number;
            }
            else
            {
                binary_insertion_sort(number);
                precompute_median_value();
            }
        }

        Data median()
        {
            return medianValue;
        }

        Data min()
        {
            return numberData[0];
        }

        Data max()
        {
            return numberData[numberData.size() - 1];
        }

    private:
        //Holds a precomputed current median value
        double medianValue;
        //A vector containing all of the number data
        vector<Data> numberData;
        //Looks up where to insert the new data value in the sorted numberData vector 
        int insertion_index_lookup(Data data, int low, int high) 
        {
            if (high <= low)
            {
                return (data.compare(numberData[low]) > 0) ? (low + 1) : low;
            }
            int mid = (low + high)/2;
          
            if(data.compare(numberData[mid]) == 0)
            {
                return mid + 1;
            }
            if(data.compare(numberData[mid]) > 0)
            {
                return insertion_index_lookup(data, mid + 1, high);
            }
            else
            {
                return insertion_index_lookup(data, low, mid - 1);
            }       
        }
        //Performs a binary search and inserts the new number in its sorted position
        void binary_insertion_sort(Data data) 
        {
            int insertPos = insertion_index_lookup(data, 0, numberData.size() - 1);
            numberData.insert(numberData.begin() + insertPos, data);
        }
        //Calculate median of vector
        void precompute_median_value()
        {
            size_t size = numberData.size();

            if (size % 2 == 0)
            {
                medianValue = (numberData[size / 2 - 1] + numberData[size / 2]) / 2;
            }
            else 
            {
                medianValue = numberData[size / 2];
            }
        }
};

#endif
