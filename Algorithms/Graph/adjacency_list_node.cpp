#include<bits/stdc++.h>
using namespace std;

class Node {
	public:
	string name;
	list<string> ngbrs;
	
	Node(string _name) : name(_name) {		
	}
};


class Graph {
    unordered_map<string, Node*> m;
	
	public:
	Graph(vector<string>cities) {
		for (auto &city : cities) {
			m[city] = new Node(city);
		}
	}
	
	void addEdge(string from, string to, bool undir = false) {
		m[from]->ngbrs.push_back(to);
		if (undir) {
			m[to]->ngbrs.push_back(from);
		}
	}
	
	void printAdjList() {
		for (auto &cityPair : m) {
		
			cout << cityPair.first << "   --------->   ";
			for (auto &ngbr : cityPair.second->ngbrs) {
				cout << ngbr << ", ";
			}			
			cout << "\n";
		}
	}	
};

int main(){
	
	vector<string> cities = {"Delhi", "London", "Paris", "New York"};
	Graph g(cities);
	g.addEdge("Delhi", "London");
	g.addEdge("New York", "London");
	g.addEdge("Delhi", "Paris");
	g.addEdge("Paris", "New York");

	g.printAdjList();
	
	return 0;
}
