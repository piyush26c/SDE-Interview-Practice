/**  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    |                                               |
    | Creator  : Piyush Rajendra Chaudhari          | 
    | Timestamp: 22.11.2021 17:45:50                | 
    |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _| 
**/
#include <bits/stdc++.h>

using namespace std;

pair<int, int> reduce_fraction_to_lowest_form(int a, int b) {
  int minelem = min(a, b);
  int i = 2;
  while(i <= minelem) {
    if ((a % i == 0) && (b % i == 0)) {
      a /= i;
      b /= i;
      minelem = min(a, b);
    } else {
      i ++;
    }
  }
  return make_pair(a, b);
}

int main () {
  ios::sync_with_stdio (false);
  cin.tie (0);
  int a, b;
  cin >> std::ws >> a >> b;

  auto p = reduce_fraction_to_lowest_form(a, b);
  cout << "a: " << p.first << " b: " << p.second << "\n";
  return 0;
}