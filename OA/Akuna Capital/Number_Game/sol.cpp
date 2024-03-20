/**  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    |                                               |
    | Creator  : Piyush Rajendra Chaudhari          |
    |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
**/
#include <bits/stdc++.h>

using namespace std;

// Problem: Number Game (Akuna Capital C++ Round 1)

int main () {
  ios::sync_with_stdio (false);
  cin.tie (0);
  
  int n;
  cin >> n;
  vector<int> arr(n);

  for (int i = 0; i < n; i++) {
  	cin >> arr[i];
  }

  bool backward = false;

  int l = 0;
  int r = n - 1;
  int i = 0; 
  int miriam = 0;
  int alejandro = 0;

  while(i < n) {
  	if ((i % 2) == 0) {
  		// miriam turn
  		if (backward) {
  			miriam += arr[r];

  			if ((arr[r] % 3) == 0) {
  				backward = !backward;
  			}
  			r--;
  		} else {
  			miriam += arr[l];
  			if ((arr[l] % 3) == 0) {
  				backward = !backward;
  			}
  			l++;
  		}
  	} else {
  		// alejandro
  		if (backward) {
  			alejandro += arr[r];

  			if ((arr[r] % 3) == 0) {
  				backward = !backward;
  			}
  			r--;
  		} else {
  			alejandro += arr[l];
  			if ((arr[l] % 3) == 0) {
  				backward = !backward;
  			}
  			l++;
  		}
  	}
  	i += 1;
  }

  cout << "\nAnswer: " << miriam - alejandro;
  return 0;
}