#include <med.h>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;

TEST_CASE("testing mySum") {
    CHECK(med::mySum(2,5) == 7);
}

TEST_CASE("Basic median test") {
    vector<int> vs = {1,2,3,4,5};
    med::MedianTwoHeap<int> m;
    for(auto v: vs) {
        m.insert(v);
    }
    CHECK(m.median()==3);
    m.clear();
    vs.push_back(6);
    CHECK(m.size()==0);
    for(auto v: vs) {
        m.insert(v);
    }
    CHECK(m.size()==6);
    CHECK(m.median()==3);

}