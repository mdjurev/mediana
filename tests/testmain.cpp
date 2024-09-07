#include <med.h>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


TEST_CASE("testing mySum") {
    CHECK(med::mySum(2,5) == 7);
}