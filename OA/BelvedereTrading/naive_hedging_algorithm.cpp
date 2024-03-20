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

void get_input(vector<double>& buy_at, vector<double>& sell_at) {	
	string line;
	getline(cin, line);
	istringstream iss(line);
	double num;
	while(iss >> num) {
		buy_at.push_back(num);
	}

	getline(cin, line);
	istringstream iss1(line);
	while(iss1 >> num) {
		sell_at.push_back(num);
	}
	return;
}

int main () {
  ios::sync_with_stdio (false);
  cin.tie (0);
  
  vector<double> buy_at;
  vector<double> sell_at;
  
  cout << fixed << setprecision(2);

  double qty = 0;
  double rpu = 0;

  double avg_buy = 0;
  double buy_prec = 0;

  double avg_sold = 0;
  double sold_prec = 0;
  
  get_input(buy_at, sell_at);

  while(cin >> qty >> rpu) {
  	double risk = qty * rpu;
  	double rnum1;
  	double rprec = modf(risk, &rnum1);

  	if (risk > 0) {
  		rprec += sold_prec;
  		rnum1 += rprec;
  		sold_prec = 0;  		
  	} else {
  		rprec += buy_prec;
  		rnum1 += rprec;
  		buy_prec = 0;
  	}
  	
  	double rnum;
  	rprec = modf(rnum1, &rnum);

	if (risk > 0) {
		sold_prec += rprec;
	} else {
		buy_prec += rprec;
	}

  	// case
  	if ((int) rnum == 0) {
  		continue;
  	}

  	// debug(risk, rnum, rprec);
  	rnum = abs(rnum);
  	double ornum = rnum;
  	// calculate average-fill
  	if (risk >= 0) {
  		// now sell
  		double temp_avg_sold = 0;
  		for (int i = 0; i < 6; i++) {
  			if ((i % 2 == 0) && (sell_at[i] > 0)) {
  				if (rnum < sell_at[i]) {
  					sell_at[i] -= rnum;  					
  					temp_avg_sold += (sell_at[i + 1]);
  					// debug(temp_avg_sold);
  					rnum = 0;
  					break;
  				} else if (rnum > sell_at[i]) {
  					temp_avg_sold += (sell_at[i + 1]);  					
  					rnum -= sell_at[i];
  					sell_at[i] = -1;
  				} else {
  					temp_avg_sold += (sell_at[i + 1]);
  					rnum = 0;
  					sell_at[i] = -1;
  					break;
  				}
  			}
  		}
  		
  		// final output
  		if (avg_sold > 0) {
  			avg_sold = (avg_sold + temp_avg_sold) / 2;
  		} else {
  			avg_sold = avg_sold + temp_avg_sold;
  		}

  		cout << (int) ornum * (-1) << " " << avg_sold << "\n";

  	} else if (risk < 0) {
  		// now buy
  		double temp_avg_buy = 0;
  		for (int i = 0; i < 6; i++) {
  			if ((i % 2 == 0) && (buy_at[i] > 0)) {
  				if (rnum < buy_at[i]) {
  					buy_at[i] -= rnum;  					
  					temp_avg_buy += (buy_at[i + 1]);
  					rnum = 0;
  					break;
  				} else if (rnum > buy_at[i]) {
  					temp_avg_buy += (buy_at[i + 1]);  					
  					rnum -= buy_at[i];
  					buy_at[i] = -1;
  				} else {
  					temp_avg_buy += (buy_at[i + 1]);
  					rnum = 0;
  					buy_at[i] = -1;
  					break;
  				}
  			}
  		}
  		
  		// final output
  		if (avg_buy > 0) {
  			avg_buy = (avg_buy + temp_avg_buy) / 2 ;
  		} else {
  			avg_buy = avg_buy + temp_avg_buy;
  		}
  		cout << (int) abs(ornum) << " " << avg_buy << "\n";
  	}

  	
  }

  // debug(buy_at, sell_at, qty, rpu);

  return 0;
}
