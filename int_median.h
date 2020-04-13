#ifndef __INT_MEDIAN_H__
#define __INT_MEDIAN_H__

#include "Median/median.h"

class IntData : public ComperableData<IntData>
{
    public:
        IntData(int data)
        {
            this->data = data;
        }
        int compare(const IntData& otherData) override
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
        operator int() const { return data; }
    private:
        int data;
};

#endif
