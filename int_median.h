#ifndef __INT_MEDIAN_H__
#define __INT_MEDIAN_H__

#include "Median/median.h"

template <typename T>
class NumericData : public ComperableData<NumericData<T>, double>
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

        int compare(const double& medianValue) const override
        {
            return compare(NumericData((T)medianValue));
        }

        static double max_median()
        {
            return (double)numeric_limits<T>::max();
        }

        double as_median() const override
        {
            return (double)data;
        }

        double median_with(const NumericData& otherData) const override
        {
            return (data + otherData) / 2.0;
        }

        void set_data(T value)
        {
            data = value;
        }
    private:
        T data;
};

#endif
