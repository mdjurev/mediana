#pragma once

#include <algorithm>
#include <vector>
#include <queue>
#include <assert.h>

namespace med
{
// just for CMake setup
inline int mySum(int a, int b) { return a+b;}

/// Data structure that allows adding of elements and extracting a median. Maintains two heaps.
/// There are two heaps, max-heap (before) and min-heap (after).
/// Max heap holds the median or one element below it as its max element. All other elements of it are lower than the median.
/// Min heap holds the median or one element above it as its min element. All other elements of it are higher than the median.
template<class T>
class MedianTwoHeap {
	using MaxHeap = typename std::priority_queue<T>;
	using MinHeap = typename std::priority_queue<T, std::vector<T>, std::greater<T> >;
	using size_type = typename std::priority_queue<T>::size_type;

	MaxHeap before;
	MinHeap after;

public:
	/// Inserts an element into the structure
	void insert(const T& t) {
		if(after.empty()) {
			after.push(t);
			assert(isBalanced());
			return;
		}
		if(before.empty()) {
			before.push(t);
			assert(isBalanced());
			return;
		}
		const T& b=before.top();
		const T& a=after.top();
		if(t<b) {
			before.push(t);
		} else if(t>a) {
			after.push(t);
		} else {
			// Could go into both, choose smaller one to avoid rebalance
			if(before.size()<after.size())
				before.push(t);
			else
				after.push(t);
		}
		rebalance();
	}

	/// Returns the median of the contents
	/// If the size is even, returns the average of the two middle elements 
	T median() const {
		const int bs = before.size();
		const int as = after.size();
		if(as>bs)
			return after.top();
		else if(bs<as)
			return before.top();
		else if(bs==0 && as==0)
			return T();
		else
			return (after.top()+before.top())/2;
	}

	/// Clears the contents
	void clear() {
		//Priority queue doesn't have clear method
		before=MaxHeap();
		after=MinHeap();
		assert(before.size()==0);
		assert(after.size()==0);
	}

	/// Checks whether the container is empty
	bool empty() const {
		return before.empty() && after.empty();
	}

	size_type size() const {
		return before.size()+after.size();
	}

private:
	// Returns true if before and after sizes differ by at most 1
	inline bool isBalanced() const {
		const int bs = before.size();
		const int as = after.size();
		return (bs==as || as==bs+1 || bs==as+1);
	}
	// Make sure that before and after sizes differ by at most 1
	void rebalance() {
		if(isBalanced())
			return;
		const int bs = before.size();
		const int as = after.size();
		if(bs>as) {
			after.push(before.top());
			before.pop();
		} else if(as>bs) {
			before.push(after.top());
			after.pop();
		}
		assert(isBalanced());
	}
};

	
} // namespace med