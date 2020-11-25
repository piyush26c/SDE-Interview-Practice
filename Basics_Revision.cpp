//new delete 
	- int *ip = new int;
	- int *jp = new int [10]; //array
	- delete []jp;;
	- delete ip;
//exception catching
	- catch (char* param_) {}
	- catch (...) {}
//algorithm specification
	- Input:
	- Output:
	- Definiteness:
	- Effectiveness:
//swaping without temp: 
swap (x, y) {
	x = x + y;
	y = x - y;
	x = x - y;
}
//print all permutation
void allPermutation (string &inputString_, int leftIndx_, int rightIndx_) {
	//base case
	if (leftIndx_ == rightIndx_) {
		cout << inputString_ << "\n";
	} else {
		for (int indx = leftIndx_; indx <= rightIndx_; indx++) {
			swap(inpuptString_[leftIndx_], inputString_[indx]);
			allPermutation(inputString_, indx + 1, rightIndx_);
			swap(inputString_[leftIndx_], inputString_[indx]);
		}
	}
} //time complexity : O(n * n!)



