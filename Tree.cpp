#######################################################################################################
--------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------
Leetcode Tree Solution:

1]
Design an Expression Tree With Evaluate Function :
Ans.
// first create node structure;
struct Node {
    Node *left;
	int val;
    Node *right;

    Node(int value) : val(value), left (NULL), right (NULL) {}
};

vector<Node*> findPstOrdTraversal (Node *root) {
	vector<Node*> ans;
	stack<Node*> stack1, stack2;
	Node *tptr = root;
	do {
		while (tptr->right != NULL) {
			stack1.push(tptr);
			stack2.push(tptr);
			tptr = tptr->right;
		}
		if (!stack1.empty()) {
			tptr = stack1.pop();
		}		
		while (!stack1.empty() && tptr->left == NULL) {
			stack1.pop();
		}
		tptr = tptr->left;
	} while (!stack1.empty() || tptr != NULL);
	
	do {
		ans.push_back(stack2.top());
		stack2.pop();
	} while (!stack2.empty());
	return ans;
}

//utitlity function
bool isNumber (Node *node) {
	if (node->value == '*' || node->value == '/' || node->value == '-' || node->value == '+') {
		return false;
	} else {
		return true;
	}
}

//utility function
void (performCalc (stack<int>&stack1, int num1, int num2, Node* node) {
	if (node->value == '*') {
		stack1.push(num1 * num2);
	} else if (node->value == '/') {
		stack1.push(num1 / num2);
	} else if (node->value == '-') {
		stack1.push(num1 - num2);
	} else {
		stack1.push(num1 + num2);
	}
}

//first have a postorder traversal of given binary tree. 

int calcExpTreeValue (Node *root) {
	if (root == NULL) {
		return -1;
	}
	vector<Node*> postOrderTraversal = findPstOrdTraversal (root);
	stack<int> calculation;
	for (int i = 0; i < (int) postOrderTraversal.size(); i++) {
		if (isNumber(postOrderTraversal[i]->value)) {
			calculation.push(postOrderTraversal[i]);
		} else {
			int num2 = calculation.top();
			calculation.pop();
			int num1 = calculation.top();
			calculation.pop();
			performCalc(calculation, num1, num2, postOrderTraversal[i]);
		}
	}
	return calculation.top();	
}

---------------------------------------------------------------------------------------------------------------------------
Q2]
