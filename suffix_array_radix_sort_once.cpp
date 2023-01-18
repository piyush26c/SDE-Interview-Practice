/**  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    |                                               |
    | Creator  : Piyush Rajendra Chaudhari          |
    |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
**/
#include <bits/stdc++.h>

using namespace std;

/*
SUFFIX ARRAY IMPLEMENTATION
Reference: https://codeforces.com/edu/course/2/lesson/2/2

Time Complexity
	| _ n*log(n) + log(n) * (n)
		| _ O(n * (log(n))

Space Complexity
	| _ O(n)

*/


// Time Complexity : O(n)
// basically sorting suffix_array, the keys present in classes array [[[ONLY ONCE]]]
void count_sort(vector<int> &suffix_array, vector<int> &classes) {
  
  int n = (int) suffix_array.size();

  {
    // counting sort (by first element in pair<int, int>
    vector<int> cnt(n);

    for (auto &x : classes) {
      cnt[x]++;
    }

    vector<int> suffix_array_new(n);
    vector<int> pos(n);

    pos[0] = 0;

    for (int indx = 1; indx < n; indx++) {
      pos[indx] = pos[indx - 1] + cnt[indx - 1];
    }

    for (auto &x : suffix_array) {
      int bucketno = classes[x];
      suffix_array_new[pos[bucketno]] = x;
      pos[bucketno]++;
    }

    suffix_array = suffix_array_new;
  }
  return;
}

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


    for (int indx = 0; indx < n; indx++) {
      suffix_array[indx] = (suffix_array[indx] - (1 << k) + n) % n;
    }

  	count_sort(suffix_array, classes); // O(n)

    vector<int> classes_new(n);


  	//allocate class
  	classes_new[suffix_array[0]] = 0;
  	for (int indx = 1; indx < n; indx++) {
      pair<int, int> prev = {classes[suffix_array[indx - 1]], classes[(suffix_array[indx - 1] + (1 << k)) % n]};
      pair<int, int> now = {classes[suffix_array[indx]], classes[(suffix_array[indx] + (1 << k)) % n]};


  		if (prev == now) {
  			classes_new[suffix_array[indx]] = classes_new[suffix_array[indx - 1]];
  		} else {
  			classes_new[suffix_array[indx]] = classes_new[suffix_array[indx - 1]] + 1;
  		}
  	}
    classes = classes_new;

  	k += 1;
  }

  for (auto &x: suffix_array) {
  	cout << x << " ";
  }
  cout << '\n';

  return 0;
}
