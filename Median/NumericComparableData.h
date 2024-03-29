#ifndef __INT_MEDIAN_H__
#define __INT_MEDIAN_H__

#include <limits>

#include "ComparableData.h"

/*
* Helper class facilitating using ComparableData with basic numeric types (short, int, long, double...)
*/ 
template <typename T>
class NumericComparableData : public ComparableData<NumericComparableData<T>, double>
{
    public:
        NumericComparableData()
        {
        }

        NumericComparableData(T data)
        {
            this->data = data;
        }

        NumericComparableData(const NumericComparableData& other)
        {
            this->data = other.data;
        }

        NumericComparableData(const NumericComparableData&& other)
        {
            this->data = other.data;
        }

        NumericComparableData& operator=(const NumericComparableData&& other)
        {
            this->data = other.data;
            return *this;
        }

        NumericComparableData& operator=(const NumericComparableData& otherData) override
        {
            this->data = otherData.data;
            return *this;
        }

        operator T() const 
        { 
            return data; 
        }

        NumericComparableData& operator+=(const NumericComparableData& otherData) override
        {
            this->data += otherData.data;
            return *this;
        }

        NumericComparableData operator/(int number) override
        {
            return NumericComparableData(data/number);
        }

        int compare(const NumericComparableData& otherData) const override
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
            return compare(NumericComparableData((T)medianValue));
        }

        static NumericComparableData zero_value()
        {
            return NumericComparableData(0);
        }

        static NumericComparableData max_value()
        {
            return NumericComparableData(std::numeric_limits<T>::max());
        }

        static NumericComparableData min_value()
        {
            return NumericComparableData(std::numeric_limits<T>::min());
        }

        static double zero_median()
        {
            return 0.0;
        }

        static double max_median()
        {
            return (double)max_value();
        }

        double as_median() const override
        {
            return (double)data;
        }

        double median_with(const NumericComparableData& otherData) const override
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
