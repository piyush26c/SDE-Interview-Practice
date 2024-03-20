/**  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    |                                               |
    | Creator  : Piyush Rajendra Chaudhari          |
    |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
**/
#include <bits/stdc++.h>

using namespace std;


// Problem: Selling Stocks (Akuna Capital C++ Round 1)

int main () {
  ios::sync_with_stdio (false);
  cin.tie (0);
  
  vector<tuple<int, int, int>> priceupdate = {{3, 1, 4}, {5, 1, -1}, {8, 2, 2}, {12, 3, -5}};
  vector<tuple<int, int, bool, int>> orders = {{0, 2, true, 15}, {4, 1, false, 30}, {6, 1, true, 10}, {10, 2, true, 5}, {15, 4, false, 100}};
  int initial_price = 10;

  set<int> order_exec;


  unordered_map<int, tuple<int, int>> mp; // {stockid, [current_stock_price, profitnloss]


  int o = 0;
  int p = 0;

  while((o < (int) orders.size()) && (p < (int) priceupdate.size())) {
  	if (get<0>(priceupdate[p]) < get<0>(orders[o])) {
  		// execute priceupdate
  		int stockid = get<1>(priceupdate[p]);
  		int delta = get<2>(priceupdate[p]);

  		if (mp.find(stockid) == mp.end()) {
  			mp[stockid] = make_tuple(initial_price + delta, 0);
  		} else {
  			int old_stock_price = get<0>(mp[stockid]);
  			int profitnloss = get<1>(mp[stockid]);

  			mp[stockid] = make_tuple(old_stock_price + delta, profitnloss);
  		}
  		p += 1;

  	} else {
  		// execute orders

  		int stockid = get<1>(orders[o]);
  		bool buy = get<2>(orders[o]); // true = buy (negative), false = sell
  		int qty = get<3>(orders[o]);

  		order_exec.insert(stockid);

  		if (mp.find(stockid) == mp.end()) {
  			// first time, set stock price to initial_price
  			mp[stockid] = make_tuple(initial_price, 0);
  		}

  		int stock_price = get<0>(mp[stockid]);
  		int profitnloss = get<1>(mp[stockid]);

  		if (buy == true) {
  			mp[stockid] = make_tuple(stock_price, profitnloss - (qty * stock_price));
  		} else {
  			mp[stockid] = make_tuple(stock_price, profitnloss + (qty * stock_price));
  		}
  		o += 1;
  	}
  }

  while((o < (int) orders.size())) {
	// execute orders
	int stockid = get<1>(orders[o]);
	bool buy = get<2>(orders[o]); // true = buy (negative), false = sell
	int qty = get<3>(orders[o]);

	order_exec.insert(stockid);

	if (mp.find(stockid) == mp.end()) {
		// first time, set stock price to initial_price
		mp[stockid] = make_tuple(initial_price, 0);
	}	

	int stock_price = get<0>(mp[stockid]);
	int profitnloss = get<1>(mp[stockid]);

	if (buy == true) {
		mp[stockid] = make_tuple(stock_price, profitnloss - (qty * stock_price));
	} else {
		mp[stockid] = make_tuple(stock_price, profitnloss + (qty * stock_price));
	}
	o += 1;
  }

  while(p < (int) priceupdate.size()) {
	// execute priceupdate
	int stockid = get<1>(priceupdate[p]);
	int delta = get<2>(priceupdate[p]);

	if (mp.find(stockid) == mp.end()) {
		mp[stockid] = make_tuple(initial_price + delta, 0);
	} else {
		int old_stock_price = get<0>(mp[stockid]);
		int profitnloss = get<1>(mp[stockid]);

		mp[stockid] = make_tuple(old_stock_price + delta, profitnloss);
	}
	p += 1;
  }    

  vector<pair<int, int>> ans;
  for (auto& x : order_exec) {
  	ans.push_back(make_pair(x, get<1>(mp[x])));
  	cout << x << " : " << get<1>(mp[x]) << "\n";
  }

  return 0;
}