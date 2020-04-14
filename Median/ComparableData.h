#ifndef __COMPARABLE_DATA_H__
#define __COMPARABLE_DATA_H__

/*
* The interface for data that MedianData is going to operate on
* Data - the underlying data type implementing the interface
* MedianType - return type of the median
*/ 
template <typename Data, typename MedianType>
class ComparableData
{
public:
    /*
    * compare this ComparableData to another instance of Data
    * otherData - data to compare to
    * returns - 1 if greater than, 0 if equal to, -1 if less than otherData
    */ 
    virtual int compare(const Data& otherData) const = 0;

    /*
    * compare this ComparableData to the median type
    * medianValue - median type value to compare to
    * returns - 1 if greater than, 0 if equal to, -1 if less than otherData
    */ 
    virtual int compare(const MedianType& medianValue) const = 0;
    
    /*
    * Return this Data as median value
    */ 
    virtual MedianType as_median() const = 0;

    /*
    * Returns the median value of combining this ComparableData with another Data instance
    * otherData - data to compare to
    * returns the medianl value of the two Data instances
    */ 
    virtual MedianType median_with(const Data& otherData) const = 0;

    /*
    * Greater than comparisson of this ComparableData to the another Data instance
    * otherData - data to compare to
    * returns - true if greater, false otherwise
    */ 
    bool operator >(const Data& otherData) const
    {
        return compare(otherData) > 0;
    }

    /*
    * Less than comparisson of this ComparableData to the another Data instance
    * otherData - data to compare to
    * returns - true if less, false otherwise
    */ 
    bool operator <(const Data& otherData) const
    {
        return compare(otherData) < 0;
    }
};

#endif
