1] https://www.geeksforgeeks.org/data-structures/

2] https://www.geeksforgeeks.org/tag/amazon/



#######################################################################################################
------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------

1] Interview Exp:  Link: https://www.geeksforgeeks.org/amazon-interview-experience-for-6-months-intern-on-campus/

Q1] Implement a LIFO data structure that has the following operations: Push, Pop, GetMiddle, DeleteMiddle.
Ans:

struct Node {
	Node *prev;
	int val;
	Node *next;
	Node(int x) : prev(NULL), next(NULL), val(x) {}
};

class MyStack {
	public:
	Node *head;
	Node *mid;
	int numberOfNodes;
	
	MyStack() : head(NULL), mid(NULL), numberOfNodes(0);
	
	void push(int value_){
		Node *newNode = new Node(value_);
		if (head == NULL) {
			head = newNode;		
		} else {
			newNode->next = head;
			head = newNode;
		}
			
		numberOfNodes += 1;
		
		if (numberOfNodes == 1) {
			mid = head;
		} else {
			if (numberOfNodes % 2 == 0) {
				mid = mid->next;
			}
		}	
	}
	
	
	Node* pop() {
		if (head == NULL) {
			return NULL;
		} else {
			Node *nodeToBeReturned = new Node(head->val);
			Node *nodeToBeDeleted = head;
			head = head->next;
			head->prev = NULL;
			delete nodeToBeDeleted;
			
			numberOfNodes -= 1;
			
			if (numberOfNodes % 2 != 0) {
				mid = mid->prev;
			}
			return nodeToBeReturned;			
		}	
	}
	
	Node* getMiddle(){
		if (head == NULL) {
			return NULL;
		} else {
			Node *nodeToBeReturned = mid;
			return mid;		
		}
	}
	
	bool deleteMiddle(){
		if (head == NULL) {
			return false;
		} else {
			Node *nodeToBeDeleted = mid;
			mid-prev->next = mid->next;
			mid->next->prev = mid->prev;
			delete nodeToBeDeleted;
			
			numberOfNodes -= 1;
			
			return true;
		}		
	}
};

int main() {
	MyStack mStack = MyStack();
	return 0;
}

------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------

Q2] Implement the code for following pattern
1
11
21
1211
111221
312211.....
### this above pattern is called as "Look-and-Say-Sequence"

string lookAnsSaySequence(int numberOfLevel_) {
	if (numberOfLevel_ <= 0) {
		return -1;
	}
	string ans = "1";
	for(int i = 1; i <= numberOfLevel_; i++) {
		if (i == 2) {
			ans += "1";			
		} else {
			int count = 0;
			string temp = "";
			int indx = 0;
			while(indx < (int) ans.length()) {
				if (indx < (int) ans.length() && ans[indx] == ans[indx + 1]) {
					count += 1;					
				} else {
					count += 1;
					temp = temp + count - '0' + ans[indx - 1];									
					count = 0;
					ans = temp;					
				}
				indx += 1;				
			}		
		}
		cout << "Level : " << i << " : " << ans << "\n";		
	}
	return ans;	
}

------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------

Q3] Given an integer array, find all the numbers which don’t have a greater element on its right.
Ans.
vector<int> function (vector<int> &v) {
	vector<int> ans;
	int maxElementUTill = INT_MIN;
	for (int indx = (int) v.size() - 1; i >= 0; i--) {
		if (v[indx] > maxElementUTill) {
			maxElementUTill = v[indx];
			ans.push_back(v[indx]);
		}
	}
	reverse(ans.begin(), ans.end());
	return ans;
}
------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
Q4] Given an array of stock prices, perform 2 queries.
		[1] Change the value of the stock at ith index
		[2] Find minimum stock price within a given range
Ans.
/*
segment tree question : height of segment tree Log(N) && 
total number of nodes = n (number of leaf nodes) + (n - 1) (internal nodes)
first building the segment tree {by using recursion (bottom-up approach) in O(2N - 1) time & space i.e O(N)
Link[1]: https://medium.com/nybles/understanding-range-queries-and-updates-segment-tree-lazy-propagation-and-mos-algorithm-d2cd2f6586d8
Link[2]: https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/tutorial/
Here, using segment tree we can implement:
		Range Min Query
		Range Max Query
		Range Sum Query
		Range GCD Query			[In case 2: Range represented by the node lies completely outside the given range than "return 0"]
		Range LCM Query &		[In case 2: Range represented by the node lies completely outside the given range than "return 1"]
		Update at a point (Node) {not in range (that is done using Lazy propagation)}		
*/

//answer to above question
//this function is for minimum oriented queries range minimum query.
int rmqSegmentTree(vector<int>&segmentTree_, int leftBound, int rightBound, int startIndx, int endIndx, int treeNode) {
	// time compelxity O(Log(N))
	//case 1: Range represented by the node lies completely inside the given query range:
	if (leftBound <= startIndx && rightBound >= endIndx) {
		return segmentTree_[treeNode];
	}
	//case 2: Range represented by the node lies completely outside the given query range
	if (startIndx > rightBound || endIndx < leftBound) {
		return INT_MAX; //important line
	}
	int midIndx = startIndx + (endIndx - startIndx) / 2;
	//case 3: Range represented by the node lies partially inside and partially outside the given query range
	int ans1 = rmqSegmentTree(segmentTree_, leftBound, rightBound, startIndx, midIndx, 2 * treeNode);
	int ans2 = rmqSegmentTree(segmentTree_, leftBound, rightBound, midIndx + 1, endIndx, 2 * treeNode + 1);
	return min(ans1, ans2);
}
//this function (update @ point) is for minimum oriented queries
void updateSegmentTree(vector<int>&segmentTree_, int queryNodeIndx, int queryNodeUptdValue, int startIndx, int endIndx, int treeNode) {
	// time compelxity O(Log(N))
	if (startIndx == endIndx) {
		//value updated
		segmentTree_[treeNode] = queryNodeUptdValue;
		return;
	}
	int midIndx = startIndx + (endIndx - startIndx) / 2;
	if (queryNodeIndx <= midIndx) {
		updateSegmentTree(segmentTree_, queryNodeIndx, queryNodeUptdValue, startIndx, midIndx, 2 * treeNode);
	} else {
		updateSegmentTree(segmentTree_, queryNodeIndx, queryNodeUptdValue, midIndx + 1, endIndx, 2 * treeNode + 1);
	}
	segmentTree_[treeNode] = min(segmentTree_[2 * treeNode], segmentTree_[2 * treeNode + 1]);
}

//this function is for minimum oriented queries
void buildSegmentTree(vector<int>&inputArr_, vector<int>&segmentTree_, int startIndx, int endIndx, int treeNode) {
	//base case : when both start and end indices will be same
	if (startIndx == endIndx) {
		segmentTree_[treeNode] = inputArr_[startIndx];
		return;
	}
	int midIndx = startIndx + (endIndx - startIndx) / 2;
	buildSegmentTree(inputArr_, segmentTree_, startIndx, midIndx, 2 * treeNode);
	buildSegmentTree(inputArr_, segmentTree_, midIndx + 1, endIndx, 2 * treeNode + 1);
	
	segmentTree_[treeNode] = min(segmentTree_[2 * treeNode], segmentTree_[2 * treeNode + 1]);
}
----------------------------------------------------------------
int rsqSegmentTree(vector<int>&segmentTree_, int leftBound, int rightBound, int startIndx, int endIndx, int treeNode) {
	// time compelxity O(Log(N))
	//case 1: Range represented by the node lies completely inside the given query range:
	if (leftBound <= startIndx && rightBound >= endIndx) {
		return segmentTree_[treeNode];
	}
	//case 2: Range represented by the node lies completely outside the given query range
	if (startIndx > rightBound || endIndx < leftBound) {
		return 0; //important line
	}
	int midIndx = startIndx + (endIndx - startIndx) / 2;
	//case 3: Range represented by the node lies partially inside and partially outside the given query range
	int ans1 = rsqSegmentTree(segmentTree_, leftBound, rightBound, startIndx, midIndx, 2 * treeNode);
	int ans2 = rsqSegmentTree(segmentTree_, leftBound, rightBound, midIndx + 1, endIndx, 2 * treeNode + 1);
	return (ans1 + ans2);
}

//this function (update @ point) are for sum oriented queries (Extra done here)
void updateSegmentTree(vector<int>&segmentTree_, int queryNodeIndx, int queryNodeUptdValue, int startIndx, int endIndx, int treeNode) {
	// time compelxity O(Log(N))
	if (startIndx == endIndx) {
		//value updated
		segmentTree_[treeNode] = queryNodeUptdValue;
		return;
	}
	int midIndx = startIndx + (endIndx - startIndx) / 2;
	if (queryNodeIndx <= midIndx) {
		updateSegmentTree(segmentTree_, queryNodeIndx, queryNodeUptdValue, startIndx, midIndx, 2 * treeNode);
	} else {
		updateSegmentTree(segmentTree_, queryNodeIndx, queryNodeUptdValue, midIndx + 1, endIndx, 2 * treeNode + 1);
	}
	segmentTree_[treeNode] = segmentTree_[2 * treeNode] + segmentTree_[2 * treeNode + 1];
}

//this function are for sum oriented queries (Extra done here)
void buildSegmentTree(vector<int>&inputArr_, vector<int>&segmentTree_, int startIndx, int endIndx, int treeNode) {
	//base case : when both start and end indices will be same
	if (startIndx == endIndx) {
		segmentTree_[treeNode] = inputArr_[startIndx];
		return;
	}
	int midIndx = startIndx + (endIndx - startIndx) / 2;
	buildSegmentTree(inputArr_, segmentTree_, startIndx, midIndx, 2 * treeNode);
	buildSegmentTree(inputArr_, segmentTree_, midIndx + 1, endIndx, 2 * treeNode + 1);
	
	segmentTree_[treeNode] = segmentTree_[2 * treeNode] + segmentTree_[2 * treeNode + 1];
}
----------------------------------------------------------------
//similarly can three functions can be implemented for max oriented queries.
int main() {
	//input array of which segment tree is to be build
	vector<int> inputArr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int sizeOfInputArr = (int) inputArr.size();
	//segment tree array takes 2*N - 1 space but we will start from index 1 so will allocate 2*N space
	vector<int> segmentTree (2 * sizeOfInputArr);
	buildSegmentTree(inputArr, segmentTree, 0, sizeOfInputArr - 1, 1);
	//printing segmentTree array
	for (auto &x : segmentTree)
		cout << x << "\n";
	return 0;
}

----------------------------------------------------------------
/*
Lazy propagation :
		Range Update Queries -> Range Sum Queries
*/
//Range Update query implementation using Lazy Propagation
void ruqSegmentTree (vector<int>&segmentTree_, vector<int> lazyTree_, int queryUptdValue, int leftBound, int rightBound, int startIndx, int endIndx, int treeNode) {
	if (lazyTree_[treeNode] != 0) {
		segmentTree_[treeNode] += (endIndx - startIndx + 1) * lazyTree_[treeNode];
		if (startIndx != endIndx) {
			lazyTree_[2 * treeNode] += lazyTree_[treeNode];
			lazyTree_[2 * treeNode + 1] += lazyTree_[treeNode];
		}
		//no longer lazy
		lazyTree_[treeNode] = 0;
	}
	//case 2: Range represented by the node lies completely outside the given query range
	if (startIndx > rightBound || endIndx < startIndx) {
		return;
	}
	//case 1: Range represented by the node lies completely inside the given query range
	if (startIndx  >= leftBound && endIndx <= rightBound) {
		segmentTree_[treeNode] = (endIndx - startIndx + 1) * queryUptdValue;
		if (startIndx != endIndx) {
			lazyTree_[2 * treeNode] += queryUptdValue;
			lazyTree_[2 * treeNode + 1] += queryUptdValue;
		}
		return;
	}
	//case 3: Range represented by the node lies partially inside and partially outside the given query range
	int midIndx = startIndx + (endIndx - startIndx) / 2;
	ruqSegmentTree(segmentTree_, lazyTree_, queryUptdValue, leftBound, rightBound, startIndx, midIndx, treeNode);
	ruqSegmentTree(segmentTree_, lazyTree_, queryUptdValue, leftBound, rightBound, midIndx + 1, endIndx, treeNode);
	segmentTree_[treeNode] = segmentTree_[2 * treeNode] + segmentTree_[2 * treeNode + 1];
	return;	
}

----------------------------------------------------------------
//Range Sum query implementation using Lazy Propagation
int rsqSegmentTree (vector<int>&segmentTree_, vector<int> lazyTree_, int leftBound, int rightBound, int startIndx, int endIndx, int treeNode) {
	if (lazyTree_[treeNode] != 0) {
		segmentTree_[treeNode] += (endIndx - startIndx + 1) * lazyTree_[treeNode];
		if (startIndx != endIndx) {
			lazyTree_[2 * treeNode] += lazyTree_[treeNode];
			lazyTree_[2 * treeNode + 1] += lazyTree_[treeNode];
		}
		//no longer lazy
		lazyTree_[treeNode] = 0;
	}
	//case 2: Range represented by the node lies completely outside the given query range
	if (startIndx > rightBound || endIndx < startIndx) {
		return 0;
	}
	//case 1: Range represented by the node lies completely inside the given query range
	if (startIndx  >= leftBound && endIndx <= rightBound) {
		return segmentTree_[treeNode];
	}
	//case 3: Range represented by the node lies partially inside and partially outside the given query range
	int midIndx = startIndx + (endIndx - startIndx) / 2;
	int ans1 = rsqSegmentTree(segmentTree_, lazyTree_, leftBound, rightBound, startIndx, midIndx, treeNode);
	int ans2 = rsqSegmentTree(segmentTree_, lazyTree_, leftBound, rightBound, midIndx + 1, endIndx, treeNode);
	return (ans1 + ans2);
}

------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------

Q5] HOD of your college is supposed to give gifts to students.
	Input Parameters: n(number of students), List of edges represting friends, k(cost of a gift)
	If HOD gives gifts to student A, he will also have to give gifts to all the students whom A considers as his/her friend. 
	If A considers B as his/her friend, it’s not necessary that B considers A as his/her friend. Find the minimum cost HOD 
	will have to spend.
	For example, if A’s friend is B and B’s friend is C, 3 gifts have to be given.
Ans:

------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------

2]  Zig-Zag traversal of binary tree.
Ans.
/*
if the tree is like 
			 1
		   /   \
		   2    3
		  / \  / \
		  7  6 5  4
for this binary tree output should be 1 3 2 7 6 5 4 
Remember: whenever you see the pattern that numbers in order are consecutively according to level then there will be a stack implementation
but how many stack should be used is what you have to identify on time.
*/

truct Node {
    Node *left;
	int val;
    Node *right;

    Node(int value) : val(value), left (NULL), right (NULL) {}
};

vector<int> zigZagTraversal (Node* root) {
	stack<int> currentLevel;
	stack<int> nextLevel;
	vector<int> answer;
	bool leftToRight = false;
	//first insert root node in currentLevel
	currentLevel.push(root);
	while (currentLevel.empty() != true) {
		Node* currentNode = currentLevel.top();
		currentLevel.pop();
		answer.push_back(currentNode->val);
		if (currentNode != NULL) {
			if (leftToRight) {
				if (currentNode->right) {
					nextLevel.push(currentNode->right);
				}
				if (currentNode->left) {
					nextLevel.push(currentNode->left);
				}				
			} else {
				if (currentNode->left) {
					nextLevel.push(currentNode->left);
				} 
				if (currentNode->right) {
					nextLevel.push(currentNode->right);
				}
			}
		}
		if (currentLevel.empty() == true) {
			leftToRight = !leftToRight;
			currentLevel.swap(nextLevel);
		}
	}
	return answer;
}
------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
