/**  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    |                                               |
    | Creator  : Piyush Rajendra Chaudhari          |
    |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
**/
#include <bits/stdc++.h>

using namespace std;

unordered_map<string, unordered_map<string, int>> database;

string SET_OR_INC(const string& key, const string& field, int value) {
    database[key][field] += value;
    return to_string(database[key][field]);
}

string GET(const string& key, const string& field) {
    if (database.count(key) && database[key].count(field)) {
        return to_string(database[key][field]);
    }
    return "";
}

bool DELETE(const string& key, const string& field) {
    if (database.count(key) && database[key].count(field)) {
        database[key].erase(field);
        if (database[key].empty()) {
            database.erase(key);
        }
        return true;
    }
    return false;
}

vector<string> solve(vector<vector<string>>& queries) {
	vector<string> output;


	for (int i = 0; i < (int) queries.size(); i++) {
		string operation = queries[i][0];
		if (operation == "SET_OR_INC") {
			int value = stoi(queries[i][3]);
			output.push_back(SET_OR_INC(queries[i][1], queries[i][2], value));
		} else if (operation == "GET") {
			output.push_back(GET(queries[i][1], queries[i][2]));
		} else if (operation == "DELETE") {
			bool success = DELETE(queries[i][1], queries[i][2]);
			output.push_back(success ? "true" : "false");
		}
	}

	return output;
}

int main () {
  ios::sync_with_stdio (false);
  cin.tie (0);
  
  vector<vector<string>> queries = {{"SET_OR_INC", "A", "B", "5"},
                                    {"SET_OR_INC", "A", "B", "6"},
                                    {"GET", "A", "B"},
                                    {"GET", "A", "C"},
                                    {"DELETE", "A", "B"},
                                    {"DELETE", "A", "C"}
  								};


  vector<string> output = solve(queries);
  for (auto &x : output) {
  	cout << x << "\n";
  }

 
  return 0;
}