/**  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    |                                               |
    | Creator  : Piyush Rajendra Chaudhari          |
    |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
**/
#include <bits/stdc++.h>

using namespace std;

struct TrieNode {
    unordered_map<string, TrieNode*> children;
    int size;  // Size of the file if it's a leaf node (file), -1 if it's a directory

    TrieNode() {
        size = -1;  // Initialize as a directory
    }
};

class CloudStorage {
public:
    CloudStorage() {
        root = new TrieNode();
    }

    bool addFile(const string& name, int size) {
        vector<string> path = splitPath(name);
        TrieNode* current = root;

        for (const string& directory : path) {
            if (current->children.find(directory) == current->children.end()) {
                current->children[directory] = new TrieNode();
            }
            current = current->children[directory];

            if (current->size != -1) {
                return false;  // File with the same name already exists
            }
        }

        current->size = size;  // Mark the leaf node as a file
        return true;
    }

    bool copyFile(const string& nameFrom, const string& nameTo) {
        TrieNode* nodeFrom = findNode(nameFrom);
        if (nodeFrom == nullptr || nodeFrom->size == -1) {
            return false;  // Source does not exist or is a directory
        }

        vector<string> pathTo = splitPath(nameTo);
        TrieNode* current = root;

        for (const string& directory : pathTo) {
            if (current->children.find(directory) == current->children.end()) {
                current->children[directory] = new TrieNode();
            }
            current = current->children[directory];
        }

        if (current->size != -1) {
            return false;  // File with the same name already exists at the destination
        }

        current->size = nodeFrom->size;  // Copy the file
        return true;
    }

    string getFileSize(const string& name) {
        TrieNode* node = findNode(name);
        if (node == nullptr || node->size == -1) {
            return "";
        }

        return to_string(node->size);
    }

private:
    TrieNode* root;

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
                return nullptr;
            }
            current = current->children[directory];
        }

        return current;
    }
};

vector<string> solve(vector<vector<string>>& queries) {
	vector<string> output;
	CloudStorage cloudStorage;

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
		}
	}

	return output;
}




int main () {
  ios::sync_with_stdio (false);
  cin.tie (0);
  
  vector<vector<string>> queries = {{"ADD_FILE", "/dir1/dir2/file.txt", "10"}, 
  									{"COPY_FILE", "/not-existing.file", "/dir1/file.txt"},
  									{"COPY_FILE", "/dir1/dir2/file.txt", "/dir1/file.txt"},
  									{"ADD_FILE", "/dir1/file.txt", "15"},
  									{"COPY_FILE", "/dir1/file.txt", "/dir1/dir2/file.txt"},
  									{"GET_FILE_SIZE", "/dir1/file.txt"},
  									{"GET_FILE_SIZE", "/not-existing.file"}
  								};


  vector<string> output = solve(queries);
  for (auto &x : output) {
  	cout << x << "\n";
  }

  return 0;
}