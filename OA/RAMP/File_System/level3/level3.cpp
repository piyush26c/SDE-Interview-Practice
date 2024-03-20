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

using namespace std;


struct TrieNode {
    unordered_map<string, TrieNode*> children;
    int size;  // Size of the file if it's a leaf node (file), -1 if it's a directory

    TrieNode() {
        size = -1;  // Initialize as a directory
    }
};

class User {
public:
    User() : capacity(0), usedSpace(0) {}
    User(int capacity_) : capacity(capacity_), usedSpace(0) {}

    bool fileExistsInUser(const string& fileName) {
        for (const auto& userFile : userFiles) {
            if (userFile.first == fileName) {
                return true;
            }
        }
        return false;
    }

    const vector<pair<string, int>>& getOwnedFiles() const {
        return userFiles;
    }

    int getCapacity() const {
        return capacity;
    }

    int getUsedSpace() const {
        return usedSpace;
    }

    bool addFile(int size) {
        if (usedSpace + size <= capacity) {
            usedSpace += size;
            return true;
        }
        return false;
    }

    bool removeFile(int size) {
        if (usedSpace >= size) {
            usedSpace -= size;
            return true;
        }
        return false;
    }

    // Add a file to the user's file list
    void addOwnedFile(const string& name, int size) {
        userFiles.push_back({name, size});
    }

    // Remove the largest file from the user's file list
    string removeLargestFileUntillLessThanNewCapacity(int newCapacity) {
        int count = 0;
        if (userFiles.empty()) {
            // return false;
            return to_string(count);
        }

        // Sort the user's files by size in descending order
        sort(userFiles.begin(), userFiles.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            if (a.second == b.second) {
                return a.first < b.first; // Sort by name in ascending order if sizes are the same
            }
            return a.second > b.second; // Sort by size in descending order
        });

        // Remove the largest file until usedSpace <= newCapacity
        while(usedSpace > newCapacity) {
            count += 1;
            const pair<string, int>& largestFile = userFiles.front();
            usedSpace -= largestFile.second;
            userFiles.erase(userFiles.begin());
        }

        
        return to_string(count);
    }

private:
    int capacity;
    int usedSpace;
    vector<pair<string, int>> userFiles;
};



class CloudStorage {
public:
    CloudStorage() {
        root = new TrieNode();
    }

    unordered_map<string, User>& getUsers() {
        return users;
    }

    bool addUser(const string& userId, int capacity) {
        if (users.find(userId) != users.end()) {
            return false; // User already exists
        }
        users[userId] = User(capacity);
        return true;
    }

    string addFileBy(const string& userId, const string& name, int size) {
        if (users.find(userId) == users.end()) {
            return ""; // User does not exist
        }

        if ((userId == "admin") || (users[userId].addFile(size))) {
            vector<string> path = splitPath(name);
            TrieNode* current = root;

            for (const string& directory : path) {
                if (current->children.find(directory) == current->children.end()) {
                    current->children[directory] = new TrieNode();
                }
                current = current->children[directory];

                if (current->size != -1) {
                    // users[userId].removeFile(size);
                    return "";
                }
            }

            current->size = size;  // Mark the leaf node as a file
            users[userId].addOwnedFile(name, size); // Add the file to the user's file list
            return to_string(users[userId].getCapacity() - users[userId].getUsedSpace());
        } 
        return "";
    }

    string getFileSize(const string& name) {
        TrieNode* node = findNode(name);
        if (node == nullptr || node->size == -1) {
            return "";
        }

        return to_string(node->size);
    }

    string updateCapacity(const string& userId, int newCapacity) {
        if (users.find(userId) == users.end()) {
            return ""; // User does not exist
        }

        User& user = users[userId];

        if (user.getUsedSpace() > newCapacity) {
            // Remove the largest files until the used space is within the new capacity
            return user.removeLargestFileUntillLessThanNewCapacity(newCapacity);
        }

        return "0";
    }

    // same as previous
    bool addFile(const string& name, int size) {
       string output = addFileBy("admin", name, size);
       
       if (output.length() == 0) return false;

       return true;
    }

    bool copyFile(const string& nameFrom, const string& nameTo) {
        bool success = false;

        // Get the source node and size
        TrieNode* sourceNode = findNode(nameFrom);
        int fileSize = sourceNode->size;

        if (fileSize == -1) {
            return false; // Source file does not exist
        }

        // Iterate through all users
        for (auto& userPair : users) {
            User& user = userPair.second;
            string userId = userPair.first;
            
            // Check if the user owns the source file
            if (fileIsOwnedByUser(nameFrom, userId)) {
                // Check if the target file already exists
                if (!fileExistsForUser(nameTo, userId)) {
                    // Check if the user's capacity allows adding the file
                    if (user.addFile(fileSize)) {
                        // Perform the copy operation
                        success = true;
                        string temp = addFileBy(userId, nameTo, fileSize);

                    }
                }
            }
        }

        return success;
    }


    string findFiles(const string& prefix, const string& suffix) {
            vector<pair<string, int>> files;
            vector<pair<TrieNode*, string>> stack;  // Stack to perform iterative depth-first traversal

            stack.push_back({root, ""});

            while (!stack.empty()) {
                TrieNode* node = stack.back().first;
                string path = stack.back().second;
                stack.pop_back();

                if (node->size != -1) {
                    string name = path;
                    name = '/' + name;
                    if (name.size() >= suffix.size() && name.substr(name.size() - suffix.size()) == suffix &&
                        (prefix.empty() || name.find(prefix) == 0)) {
                        files.push_back({name, node->size});
                    }
                }

                for (const auto& child : node->children) {
                    string childPath = path.empty() ? child.first : path + '/' + child.first;
                    stack.push_back({child.second, childPath});
                }
            }

            sort(files.begin(), files.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
                if (a.second == b.second) {
                    return a.first < b.first; // Sort by name in ascending order if sizes are the same
                }
                return a.second > b.second; // Sort by size in descending order
            });

            vector<string> sortedFiles;
            for (const auto& file : files) {
                sortedFiles.push_back(file.first + "(" + to_string(file.second) + ")");
            }

            return joinStrings(sortedFiles, ", ");
        }

private:
    TrieNode* root;
    unordered_map<string, User> users; // <userId, User>


    // Helper function to check if a user owns a specific file
    bool fileIsOwnedByUser(const string& fileName, const string& userId) {
        if (users.find(userId) != users.end()) {
            User& user = users[userId];
            return user.fileExistsInUser(fileName);
        }
        return false;
    }

    // Helper function to check if a file exists for a user
    bool fileExistsForUser(const string& fileName, const string& userId) {
        TrieNode* node = findNode(fileName);
        return (node != nullptr && node->size != -1 && fileIsOwnedByUser(fileName, userId));
    }




    vector<string> splitPath(const string& path) {
        vector<string> result;
        size_t pos = 0;
        size_t found = path.find('/');
        while (found != string::npos) {
            result.push_back(path.substr(pos, found - pos));
            pos = found + 1;
            found = path.find('/', pos);
        }
        result.push_back(path.substr(pos));
        return result;
    }

    TrieNode* findNode(const string& name) {
        vector<string> path = splitPath(name);
        TrieNode* current = root;

        for (const string& directory : path) {
            if (current->children.find(directory) == current->children.end()) {
                return nullptr; // Node not found
            }
            current = current->children[directory];
        }

        return current;
    }

    string joinStrings(const vector<string>& strings, const string& delimiter) {
        string result;
        for (int i = 0; i < (int) strings.size(); i++) {
            result += strings[i];
            if (i < (int) strings.size() - 1) {
                result += delimiter;
            }
        }
        return result;
    }
};



vector<string> solve(vector<vector<string>>& queries) {
	vector<string> output;
	CloudStorage cloudStorage;

    // add admin irrespective of query
    cloudStorage.addUser("admin", INT_MAX);

	for (int i = 0; i < (int) queries.size(); i++) {
		string operation = queries[i][0];
		if (operation == "ADD_FILE") {
			int size = stoi(queries[i][2]);
            bool success = cloudStorage.addFile(queries[i][1], size);
			output.push_back(success ? "true" : "false");
		} 
		else if (operation == "COPY_FILE") {
			bool success = cloudStorage.copyFile(queries[i][1], queries[i][2]);
			output.push_back(success ? "true" : "false");
		} else if (operation == "GET_FILE_SIZE") {
			string size = cloudStorage.getFileSize(queries[i][1]);
			output.push_back(size);
		} else if (operation == "FIND_FILE") {
            output.push_back(cloudStorage.findFiles(queries[i][1], queries[i][2]));
        } else if (operation == "ADD_USER"){
            int capacity = stoi(queries[i][2]);
            bool success = cloudStorage.addUser(queries[i][1], capacity);
            output.push_back(success ? "true" : "false");
        } else if (operation == "ADD_FILE_BY") {
            int size = stoi(queries[i][3]);
            output.push_back(cloudStorage.addFileBy(queries[i][1], queries[i][2], size));
        } else if (operation == "UPDATE_CAPACITY") {
            int capacity = stoi(queries[i][2]);            
            output.push_back(cloudStorage.updateCapacity(queries[i][1], capacity));            
        }
	}

	return output;
}




int main () {
  ios::sync_with_stdio (false);
  cin.tie (0);
  
  vector<vector<string>> queries = {{"ADD_USER", "user1", "125"},
                                    {"ADD_USER", "user1", "100"},
                                    {"ADD_USER", "user2", "100"},
                                    {"ADD_FILE_BY", "user1", "/dir/file.big", "50"},
                                    {"ADD_FILE_BY", "user1", "/file.med", "30"},
                                    {"ADD_FILE_BY", "user2", "/file.med", "40"},
                                    {"COPY_FILE", "/file.med", "/dir/another/file.med"},
                                    {"COPY_FILE", "/file.med", "/dir/another/another/file.med"},
                                    {"ADD_FILE_BY", "user1", "/dir/file.small", "10"},
                                    {"ADD_FILE", "/dir/admin_file", "200"},
                                    {"ADD_FILE_BY", "user1", "/dir/file.small", "5"},
                                    {"ADD_FILE_BY", "user1", "/my_folder/file.huge", "100"},
                                    {"ADD_FILE_BY", "user3", "/my_folder/file.huge", "100"},
                                    {"UPDATE_CAPACITY", "user1", "300"},
                                    {"UPDATE_CAPACITY", "user1", "50"},
                                    {"UPDATE_CAPACITY", "user3", "1000"}

  								};


  vector<string> output = solve(queries);
  for (auto &x : output) {
  	cout << x << "\n";
  }

  return 0;
}