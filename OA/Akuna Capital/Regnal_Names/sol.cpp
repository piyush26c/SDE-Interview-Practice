/**  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    |                                               |
    | Creator  : Piyush Rajendra Chaudhari          |
    |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
**/
#include <bits/stdc++.h>

using namespace std;

// Problem: Regnal Names (Akuna Capital C++ Round 1)

int romanToInt(string s) {
    map<char, int> roman = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
                                 {'C', 100}, {'D', 500}, {'M', 1000}};

    int total = 0;
    int prevValue = 0;

    for (int i = (int) s.length() - 1; i >= 0; i--) {
        int value = roman[s[i]];

        if (value < prevValue)
            total -= value;
        else
            total += value;

        prevValue = value;
    }

    return total;
}


int main () {
  ios::sync_with_stdio (false);
  cin.tie (0);
  
  int n;
  // cin >> n;

  vector<string> arr = {"Nicholas VIII", "Hypapsos XXIV", "Garibald Yosef II", "Nicholas C", "Michelfranko XXIV"};
  n = (int) arr.size();



  // for (int i = 0; i < n; i++) {
  // 	string s;
  // 	getline(cin , s);
  // 	arr[i] = s;
  // 	cout << arr[i] << "\n";
  // }

  vector<tuple<int, string>> srt;
  unordered_map<int, string> mp;

  for (int i = 0; i < n; i++) {
  	string ip = arr[i];
  	vector<string> parts;

  	cout << "\nIP: " << ip;

  	istringstream iss(ip);
  	string word;

  	while(iss >> word) {
  		parts.push_back(word);
  	}

  	string romanstr = parts.back();
  	cout << "\nparts.back(): " <<  romanstr << '\n';
  	int romanint = romanToInt(romanstr);

  	string name = arr[i].substr(0, (int) arr[i].length() - 1 - (int) romanstr.length());

  	srt.push_back(make_tuple(romanint, name));
  	mp[romanint] = romanstr;
  }

  sort(srt.begin(), srt.end());

  vector<string> ans;

  for (int i = 0; i < n; i++) {
  	auto& [romanint, name] = srt[i];
  	ans.push_back(name + " " + mp[romanint]);
  }

  for (auto& x : ans) {
  	cout << x << " ";
  }

  return 0;
}