#ifndef __INT_MEDIAN_H__
#define __INT_MEDIAN_H__

#include "Median/median.h"

template <class T>
class NumericData : public ComperableData<NumericData<T>>
{
    public:
        NumericData()
        {
        }

        NumericData(T data)
        {
            this->data = data;
        }

        NumericData(const NumericData& other)
        {
            this->data = other.data;
        }

        NumericData(const NumericData&& other)
        {
            this->data = other.data;
        }

        NumericData& operator=(const NumericData&& other)
        {
            this->data = other.data;
            return *this;
        }

        operator T() const 
        { 
            return data; 
        }

        int compare(const NumericData& otherData) const override
        {
            if(data > otherData)
            {
                return 1;
            }
            else if(data < otherData)
            {
                return -1;
            }
            else
            {
                return 0;
            }
            
        }

        void set_data(T value)
        {
            data = value;
        }
    private:
        T data;
};

#endif
