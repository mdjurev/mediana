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

TEST_CASE("Basic median test float") {
    vector<float> vs = {1.f,2.f,3.f,4.f,5.f};
    med::MedianTwoHeap<float> m;
    for(auto v: vs) {
        m.insert(v);
    }
    CHECK(m.median()==3.f);
    m.clear();
    vs.push_back(6.f);
    CHECK(m.size()==0);
    for(auto v: vs) {
        m.insert(v);
    }
    CHECK(m.size()==6);
    CHECK(m.median()==3.5f);
}

TEST_CASE("Some edge cases") {
    med::MedianTwoHeap<int> m;
    CHECK(m.median()==int());
    CHECK(m.size()==0);
    CHECK(m.empty());
    m.insert(1);
    CHECK(m.median()==1);
    m.insert(-1);
    CHECK(m.median()==0);
    int bigInt = 2000000000;
    m.clear();
    m.insert(bigInt);
    m.insert(bigInt+2);
    CHECK(m.median()==bigInt+1);

}