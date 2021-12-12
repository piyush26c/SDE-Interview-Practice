#include <bits/stdc++.h>
using namespace std;

/*
Video tutorial: https://www.youtube.com/watch?v=hVl2b3bLzBw
Medium tutorial: https://medium.com/swlh/merge-two-sorted-arrays-without-extra-space-efficiently-o-1-gap-method-detailed-simplified-57a336146601

*/

// motto: To sort two given "sorted" array in O(1) space complexity
// time complexity: O(n * log(n))

class GAP {
	private:	
	int calculateGAP(int prevGAP) {
		// formula : currGAP = prevGAP / 2 + (prevGAP % 2)
		if (prevGAP == 1) return 0;
		else return ((int)(floor((double)prevGAP / 2)) + (prevGAP % 2) );		
	}
	
	int getNextEnd(int start, int gap, int m) {
		int end = 0;
		if ((start + gap) >= m) {
			end = (start + gap) - m;
		} else {
			end = start + gap;
		}
		return end;
	}
	
	public:
	void sort(vector<int> &arr1, vector<int> &arr2) {
		int m = (int) arr1.size();
		int n = (int) arr2.size();
		int gap = calculateGAP(m + n);
			
		while(gap) {
			
			for (int i = 0; (i + gap) <= (m + n - 1); i++) {
				int start = i;
				int end = getNextEnd(start, gap, m);
				
				// end index viz. (start + gap) is in first array itself
				if ((start + gap) < m) {
					if (arr1[start] > arr1[end]) {
						swap(arr1[start], arr1[end]);
					}
				} else {
					// when start index is in first arrray and end index is in second array
					if ((start < m) && (arr1[start] > arr2[end])) {
						swap(arr1[start], arr2[end]);
					}
					// both (start & end) indexes are in second array
					if (start >= m) {
						start = start - m;
						if (arr2[start] > arr2[end]) {
							swap(arr2[start], arr2[end]);
						}					
					}
				}
			}
			gap = calculateGAP(gap);
		}		
	}
	
};

int main () {
	
	int m, n;
	cin >> std::ws >> m >> n;
	vector<int> arr1(m);
	vector<int> arr2(n);
	
	for (int i = 0; i < m; i++) {
		cin >> arr1[i];
	}
	
	for (int i = 0; i < n; i++) {
		cin >> arr2[i];
	}
	
	GAP obj;
 	obj.sort(arr1, arr2);
	
	//input
	cout << "input: " << "\n";
	for (auto &x: arr1) {
		cout << x << " ";
	}
	cout << "\n";
	for (auto &x: arr2) {
		cout << x << " ";
	}
	
	//output
	cout << "\noutput: " << "\n";
	for (auto &x: arr1) {
		cout << x << " ";
	}
	cout << "\n";
	for (auto &x: arr2) {
		cout << x << " ";
	}	
	return 0;
}

/*
Sample Input [1]:
4 3
1 11 11 11
3 3 3

Output:
input: 
1 3 3 3 
11 11 11 
output: 
1 3 3 3 
11 11 11 

*/

/*
Sample Input [2]:
3 3
5 9 17
1 2 6

Output:
input: 
1 2 5 
6 9 17 
output: 
1 2 5 
6 9 17

*/
