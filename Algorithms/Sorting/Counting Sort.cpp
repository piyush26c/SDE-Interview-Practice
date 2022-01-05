#include <bits/stdc++.h>
using namespace std;

/*
Video tutorial: https://youtu.be/1mh2vilbZMg
*/

// Reference Link: https://en.wikipedia.org/wiki/Counting_sort

class CountingSort {
	public:
	void sort(vector<int> &arr, int k) {
		int n = (int) arr.size();
		
		vector<int>count(k + 1, 0);
		vector<int>output(n);
		
		// 1. computing histogram of each element
		for (int i = 0; i < n; i++) {
			count[arr[i]] += 1;
		}
		
		// 2. perform prefix-sum
		for (int i = 1; i < n; i++) {
			count[i] += count[i - 1];
		}
		
		// 3. populating output array
		for (int i = n - 1; i >= 0; i--) {
			int elem
		}		
		
		return;
	}
};

int main() {
	
	vector<int> arr = {6, 1, 3, 2, 5, 4};
	
	int k = *max_element(arr.begin(),arr.end());
	
	CountingSort.sort(arr, k);
	
	return 0;
}


