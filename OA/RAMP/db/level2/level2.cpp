/**  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    |                                               |
    | Creator  : Piyush Rajendra Chaudhari          |
    |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
**/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <list>
#include <climits>
#include <algorithm>
#include <queue>

using namespace std;

unordered_map<string, unordered_map<string, int>> database;
unordered_map<string, unordered_map<string, int>> modificationCount;
unordered_map<string, int> mfc;

struct KeyCompare {
    bool operator()(const string& key1, const string& key2) const {
        int count1 = mfc[key1];
//        for (const auto& it : modificationCount[key1]) {
//            count1 += it.second;
//        }
        int count2 = mfc[key2];
//        for (const auto& it : modificationCount[key2]) {
//            count2 += it.second;
//        }

        if (count1 == count2) {
            return key1 > key2; // Lexicographically smaller key comes first in case of a tie.
        }
        return count1 < count2;
    }
};

priority_queue<string, vector<string>, KeyCompare> topKeys;
set<string> processedKeys;
string SET_OR_INC(const string& key, const string& field, int value) {
    int previousValue = database[key][field];
    database[key][field] += value;
    modificationCount[key][field] += 1; // Count all changes as modifications
    mfc[key] += 1;
    if (previousValue == 0) {
        if (processedKeys.find(key) == processedKeys.end()) {
            topKeys.push(key);
            processedKeys.insert(key);
        }
    }
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
        // int previousValue = database[key][field s ];
        database[key].erase(field);
        if (modificationCount[key].size() == 1) {
            mfc.erase(key);
        } else {
            mfc[key] += 1;
        }
        modificationCount[key].erase(field);


        if (database[key].empty()) {
            database.erase(key);
            modificationCount.erase(key);
            mfc.erase(key);
            processedKeys.erase(key);
        }
        return true;
    }
    return false;
}

string TOP_N_KEYS(int n) {
    priority_queue<string, vector<string>, KeyCompare> copyOfTopKeys = topKeys; // Create a copy
    string result;
    int count = 0;
    set<string> uniqueKeys; // To prevent duplicate keys in the result

    while (!copyOfTopKeys.empty() && count < n) {
        string key = copyOfTopKeys.top();
        copyOfTopKeys.pop();
        if ((processedKeys.find(key) != processedKeys.end()) && (uniqueKeys.find(key) == uniqueKeys.end())) {
            int totalModifications = mfc[key];
//            for (const auto& it : modificationCount[key]) {
//                totalModifications += it.second;
//            }
//            if (totalModifications == 0) {
//                break;
//            }
            result += key + "(" + to_string(totalModifications) + ")";
            uniqueKeys.insert(key);
            count++;
            if (!copyOfTopKeys.empty() && count < n) {
                result += ", ";
            }
        }
    }

    return result;

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
        } else if (operation == "TOP_N_KEYS") {
            int value = stoi(queries[i][1]);
            output.push_back(TOP_N_KEYS(value));
        }
    }

    return output;
}

int main () {
    ios::sync_with_stdio (false);
    cin.tie (0);

    vector<vector<string>> queries = {{"SET_OR_INC", "C", "field1", "10"},
                                      {"TOP_N_KEYS", "5"},
                                      {"SET_OR_INC", "A", "field1", "5"},
                                      {"DELETE", "A", "field1"},
                                      {"SET_OR_INC", "B", "field1", "8"},
                                      {"SET_OR_INC", "B", "field1", "0"},
                                      {"TOP_N_KEYS", "3"},
                                      {"DELETE", "B", "field2"},
                                      {"SET_OR_INC", "B", "field2", "6"},
                                      {"SET_OR_INC", "A", "field1", "4"},
                                      {"SET_OR_INC", "A", "field1", "2"},
                                      {"TOP_N_KEYS", "2"}
    };

//    vector<vector<string>> queries = {
//                                      {"GET", "dept4", "floors"},
//                                      {"SET_OR_INC", "dept4", "floors", "10"},
//                                      {"SET_OR_INC", "dept4", "floors", "4"},
//                                      {"TOP_N_KEYS", "1"},
//                                      {"TOP_N_KEYS", "1"},
//                                      {"SET_OR_INC", "dept4", "flowers", "15"},
//                                      {"SET_OR_INC", "dept3", "floors", "6"},
//                                      {"SET_OR_INC", "dept3", "floors", "1"},
//                                      {"GET", "dept4", "floors"},
//                                      {"TOP_N_KEYS", "1"},
//                                      {"SET_OR_INC", "dept3", "floors", "1"},
//                                      {"DELETE", "dept4", "flowers"},
//                                      {"TOP_N_KEYS", "2"}
//    };

    vector<string> output = solve(queries);
    for (auto &x : output) {
        cout << x << "\n";
    }


    return 0;
}