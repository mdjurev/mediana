#include <med.h>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

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


TEST_CASE("Sequences of 100") {
    std::vector<float> vs(100);
    std::iota(vs.begin(), vs.end(), 1.0f);
    med::MedianTwoHeap<float> m;

    SUBCASE("Increasing order") {
        for(auto v : vs)
            m.insert(v);
    }
    SUBCASE("Decreasing order") {
        // no ranges, just use iterators
        for(auto it=vs.rbegin(); it!=vs.rend(); it++)
            m.insert(*it);
    }
    SUBCASE("Random order") {
        std::shuffle(vs.begin(), vs.end(), std::minstd_rand0(4/*Chosen by a fair dice roll.*/));
        for(auto v : vs)
            m.insert(v);
    }
    CHECK(m.size()==100);
    CHECK(m.median()==50.5f);
}

TEST_CASE("Initializer list constructor") {
    med::MedianTwoHeap<int> m {1,2,3,4,5,6,7};
    CHECK(m.size()==7);
    CHECK(m.median()==4);
}

TEST_CASE("Basic constructors and assignment") {
    med::MedianTwoHeap<int> m7 {1,2,3,4,5,6,7};
    med::MedianTwoHeap<int> m5 {1,2,3,4,5};
    med::MedianTwoHeap<int> a(m7);
    CHECK(a.size()==7);
    CHECK(a.median()==4);
    a=m5;
    CHECK(a.size()==5);
    CHECK(a.median()==3);

    std::vector<float> vs(100);
    std::iota(vs.begin(), vs.end(), 1.0f);
    med::MedianTwoHeap<float> mf(vs.begin(), vs.end());
    CHECK(mf.size()==100);
    CHECK(mf.median()==50.5f);
}