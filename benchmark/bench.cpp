#include "med.h"
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

class Timer {
	std::chrono::time_point<std::chrono::system_clock> lastTime;
public:
	Timer() {
		lapMs();
	}
	/// Returns the number of milliseconds since start or last lap
	long long lapMs() {
		auto last = lastTime;
		lastTime = std::chrono::system_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(lastTime - last).count();
	}
};


// Appends an integer sequence to vector v
// the first element will be start, the
void appendSeq(vector<int> &v, int low, int high, unsigned int step=1, bool reverse=false, bool randomize=false) {
	size_t lastSize=v.size();
	assert(low<high);
	if(!reverse) {
		for(int i=low; i<=high; i+=step)
			v.push_back(i);
	} else {
		for(int i=high; i>=low; i-=step)
			v.push_back(i);
	}
	
	if(randomize) {
		std::shuffle(v.begin()+lastSize, v.end(), std::minstd_rand0(4/*Chosen by a fair dice roll.*/));
	}
}

int main(int argc, char **argv)
{
	//Number of repetitions
	int N=20;
	//Parse args
	if(argc>1) {
		try{
			N=stoi(argv[1]);
		} catch(...) {
			N=-1;
		}
	}
	if(argc>2 || N==-1) {
		cout<<"Usage: "<<argv[0]<<" N "<<" - runs the benchmark with N repetitions."<<endl;
	}
	
	typedef vector<int> ivec;
	vector<ivec*> testSequences;
	const int mln=1000000;
	
	//Add some sequences for testing:

	//Ascending
	ivec v1mu;
	appendSeq(v1mu, 1, mln);
	testSequences.push_back(&v1mu);
	
	//Descending
	ivec v1md;
	appendSeq(v1md, 1, mln, 1, true);
	testSequences.push_back(&v1md);

	//Ascending then descending
	ivec v1mud;
	appendSeq(v1mud, 1, mln);
	appendSeq(v1mud, mln+1, 2*mln, 1, true);
	testSequences.push_back(&v1mud);
	
	//Descending then ascending
	ivec v1mdu;
	appendSeq(v1mdu, 1, mln, 1, true);
	appendSeq(v1mdu, mln+1, 2*mln);
	testSequences.push_back(&v1mdu);
	

	typedef med::MedianTwoHeap<int> Mediani;
	vector<int> results;

	Timer t;
	for(ivec* vseq : testSequences) {
		for(int i=0; i<N; i++) {
			Mediani m(vseq->begin(), vseq->end());
			int res=m.median();
			if(i==0)
				results.push_back(res);
			else if(res!=results.back())
				return 1;
		}
	}
	long long ms = t.lapMs();

	cout << "Test took " << ms << "ms" << endl;
	cout << "Results:" << endl;
	for(int i: results) {
		cout << i << endl;
	}

}