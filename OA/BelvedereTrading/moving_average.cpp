/**  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    |                                               |
    | Creator  : Piyush Rajendra Chaudhari          |
    |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
**/
#include <bits/stdc++.h>

using namespace std;

template <typename A, typename B>
string to_string (pair<A, B> p);
 
template <typename A, typename B, typename C>
string to_string (tuple<A, B, C> p);
 
template <typename A, typename B, typename C, typename D>
string to_string (tuple<A, B, C, D> p);
 
string to_string (const string& s) {
  return '"' + s + '"';
}
 
string to_string( const char* s) {
  return to_string ((string) s);
}

string to_string (const char s){
 return to_string (string(1, s));
}
 
string to_string (bool b) {
  return (b ? "true" : "false");
}
 
string to_string (vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int> (v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string (v[i]);
  }
  res += "}";
  return res;
}
 
template <size_t N>
string to_string (bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char> ('0' + v[i]);
  }
  return res;
}
 
template <typename A>
string to_string (A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string (x);
  }
  res += "}";
  return res;
}
 
template <typename A, typename B>
string to_string (pair<A, B> p) {
  return "(" + to_string (p.first) + ", " + to_string (p.second) + ")";
}
 
template <typename A, typename B, typename C>
string to_string (tuple<A, B, C> p) {
  return "(" + to_string (get<0>(p)) + ", " + to_string (get<1>(p)) + ", " + to_string (get<2>(p)) + ")";
}
 
template <typename A, typename B, typename C, typename D>
string to_string (tuple<A, B, C, D> p) {
  return "(" + to_string (get<0>(p)) + ", " + to_string (get<1>(p)) + ", " + to_string (get<2>(p)) + ", " + to_string (get<3>(p)) + ")";
}
 
void debug_out () { 
  cerr << endl; 
}
 
template <typename Head, typename... Tail>
void debug_out (Head H, Tail... T) {
  cerr << " " << to_string (H);
  debug_out(T...);
}
 
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif


int main () {	
	ios::sync_with_stdio (false);
	cin.tie (0);

	string line;

	while(getline(cin, line)) {
		// for each input
		istringstream iss(line);
		string token;

		unordered_map<string, pair<double, int>> mp;
		int gsqn = -1;

		while(getline(iss, token, ';')) {
			// debug(token);
			// for each trade
			istringstream iss1(token);
			string token1;
			
			string key;
			double value = 0;
			int qty = 0;
			int sqn = 0;

			int cnt = 1;

			while(getline(iss1, token1, ',')) {
				switch(cnt) {
					case 1: {
						key = token1;
						break;
					}
					case 2: {
						value = stod(token1);
						break;
					}
					case 3: {
						qty = stoi(token1);
						break;
					}
					case 4: {
						sqn = stoi(token1);
						break;
					}
				}
				cnt +=1;
			}

			// logic starts here
			if (sqn > gsqn) {
				gsqn = sqn;
			} else {
				continue;
			}

			if (mp.find(key) != mp.end()) {
				// key found
				pair<double, int> pr = mp[key];
				mp[key] = make_pair((((pr.first * pr.second) + (value * qty)) / (pr.second + qty)),(pr.second + qty));
			} else {
				mp[key] = make_pair(value, qty);
			}

			cout << fixed << setprecision(2);
			cout << key << ": " << mp[key].first << '\n';


			
		}
	}
 
  return 0;
}