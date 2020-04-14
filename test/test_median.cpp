#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "NumericComparableData.h"
#include "MedianData.h"

TEST_CASE( "MedianData is initialized correctly", "[MedianData]" ) {
    auto md = MedianData<NumericComparableData<int>, double>();

    REQUIRE( md.size() == 0 );
    REQUIRE( md.total() == 0 );
    REQUIRE( md.min() == 0 );
    REQUIRE( md.max() == 0 );
    REQUIRE( md.mean() == 0 );
    REQUIRE( md.median() == 0 );
}

TEST_CASE( "Adding 5 results in correct data", "[MedianData]" ) {
    auto md = MedianData<NumericComparableData<int>, double>();
    md.add_number(5);
    
    REQUIRE( md.size() == 1 );
    REQUIRE( md.total() == 5 );
    REQUIRE( md.min() == 5 );
    REQUIRE( md.max() == 5 );
    REQUIRE( md.mean() == 5 );
    REQUIRE( md.median() == 5 );
}

TEST_CASE( "Adding 5 and 3 results in correct data", "[MedianData]" ) {
    auto md = MedianData<NumericComparableData<int>, double>();
    md.add_number(5);
    md.add_number(3);

    REQUIRE( md.size() == 2 );
    REQUIRE( md.total() == 8 );
    REQUIRE( md.min() == 3 );
    REQUIRE( md.max() == 5 );
    REQUIRE( md.mean() == 4 );
    REQUIRE( md.median() == 4 );
}

TEST_CASE( "Adding 5, 3 and 2 results in correct data", "[MedianData]" ) {
    auto md = MedianData<NumericComparableData<int>, double>();
    md.add_number(5);
    md.add_number(3);
    md.add_number(2);

    REQUIRE( md.size() == 3 );
    REQUIRE( md.total() == 10 );
    REQUIRE( md.min() == 2 );
    REQUIRE( md.max() == 5 );
    REQUIRE( md.mean() == 3 );
    REQUIRE( md.median() == 3 );
}

SCENARIO( "MedianData correctly calculates running median", "[MedianData]" ) {

    GIVEN( "NumericComparableData" ) {
        auto md = MedianData<NumericComparableData<int>, double>();
        
        REQUIRE( md.size() == 0 );
        REQUIRE( md.total() == 0 );
        REQUIRE( md.min() == 0 );
        REQUIRE( md.max() == 0 );
        REQUIRE( md.mean() == 0 );
        REQUIRE( md.median() == 0 );

        WHEN( "5 is added" ) {
            md.add_number(5);

            THEN( "size is 1" ) {
                REQUIRE( md.size() == 1 );
            }
            THEN( "total is 5" ) {
                REQUIRE( md.total() == 5 );
            }
            THEN( "min, max, mean and median are 5" ) {
                REQUIRE( md.min() == 5 );
                REQUIRE( md.max() == 5 );
                REQUIRE( md.mean() == 5 );
                REQUIRE( md.median() == 5 );
            }
        }
        WHEN( "5 and 3 are added" ) {
            md.add_number(5);
            md.add_number(3);

            THEN( "size is 2" ) {
                REQUIRE( md.size() == 2 );
            }
            THEN( "total is 8" ) {
                REQUIRE( md.total() == 8 );
            }
            THEN( "min, max, mean and median are calculated correctly" ) {
                REQUIRE( md.min() == 3 );
                REQUIRE( md.max() == 5 );
                REQUIRE( md.mean() == 4 );
                REQUIRE( md.median() == 4 );
            }
        }
        WHEN( "5, 3 and 2 are added" ) {
            md.add_number(5);
            md.add_number(3);
            md.add_number(2);

            THEN( "size is 3" ) {
                REQUIRE( md.size() == 3 );
            }
            THEN( "total is 10" ) {
                REQUIRE( md.total() == 10 );
            }
            THEN( "min, max, mean and median are calculated correctly" ) {
                REQUIRE( md.min() == 2 );
                REQUIRE( md.max() == 5 );
                REQUIRE( md.mean() == 3 );
                REQUIRE( md.median() == 3 );
            }
        }
    }
}