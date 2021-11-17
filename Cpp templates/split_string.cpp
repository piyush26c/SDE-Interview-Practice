
// function to split string using del{delimiter} in Cpp 
vector<string> splitString(string s, string del = " ")	// del: delimiter {" ", "%" etc.}
{
	size_t start = 0;
	size_t end = s.find(del);
	
	vector<string> res;
	
	while (end != string::npos) {
		// inserting word in result vector
		res.push_back(s.substr(start, end - start));
		start = end + del.size();
		end = s.find(del, start);
	}
	
	// for last word	
	res.push_back(s.substr(start)); // here we don't need end as end would be 18446744073709551615.
	// Also as at last iteration there will be no del present in string.
	
	return res;
}


// function to split string using del{delimiter} = " " <space> only in Cpp
vector<string> splitString(string s)
{	
	vector<string> res;
	
	stringstream ss(s);
	string word;
	while (ss >> word) {
	res.push_back(word);
	}
	
	return res;
}
