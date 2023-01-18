/**  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    |                                               |
    | Creator  : Piyush Rajendra Chaudhari          |
    |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
**/
#include <bits/stdc++.h>

using namespace std;

/*
SUFFIX ARRAY IMPLEMENTATION
Reference: https://codeforces.com/edu/course/2/lesson/2/1

Time Complexity
	| _ n*log(n) + log(n) * (n * log(n))
		| _ O(n * (log(n)) ^ 2)

Space Complexity
	| _ O(n)

*/

int main () {
  ios::sync_with_stdio (false);
  cin.tie (0);

  string s;
  cin >> s;

  // append "$" at the end of input string;
  s += "$";
  int n = (int) s.length();

  vector<int> suffix_array(n), classes(n);
  
  // implementation for suffix array
  {
  	// for k = 0 (phase - 0)
  	vector<pair<char, int>> arr(n);

  	// append each character of s in arr with index
  	for (int indx = 0; indx < n; indx++) {
  		arr[indx] = {s[indx],indx};
  	}

  	// sort the arr
  	sort(arr.begin(), arr.end()); // O(n * log(n))

  	// populate values in suffix_array
  	for (int indx = 0; indx < n; indx++) {
  		suffix_array[indx] = arr[indx].second;
  	}


  	// allocate class
  	classes[suffix_array[0]] = 0;
  	for (int indx = 1; indx < n; indx++) {
  		if (arr[indx].first == arr[indx - 1].first) {
  			classes[suffix_array[indx]] = classes[suffix_array[indx - 1]];
  		} else {
  			classes[suffix_array[indx]] = classes[suffix_array[indx - 1]] + 1;
  		}
  	}

  }


  int k = 0;
  while((1 << k) < n) { // O(log(n))
  	// from phase k to k + 1
  	vector<pair<pair<int, int>, int>> arr(n);  // {{left, right}, indx}
  	for (int indx = 0; indx < n; indx++) {
  		arr[indx] = {{classes[indx], classes[(indx + (1 << k)) % n]}, indx};
  	}

  	sort(arr.begin(), arr.end()); // O(n * log(n))

  	// populate values in sufffix_array
  	for (int indx = 0; indx < n; indx++) {
  		suffix_array[indx] = arr[indx].second;
  	}


  	//allocate class
  	classes[suffix_array[0]] = 0;
  	for (int indx = 1; indx < n; indx++) {
  		if (arr[indx].first == arr[indx - 1].first) {
  			classes[suffix_array[indx]] = classes[suffix_array[indx - 1]];
  		} else {
  			classes[suffix_array[indx]] = classes[suffix_array[indx - 1]] + 1;
  		}
  	}

  	k += 1;
  }

  for (auto &x: suffix_array) {
  	cout << x << " ";
  }
  cout << '\n';

  return 0;
}
