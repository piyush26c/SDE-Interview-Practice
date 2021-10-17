// https://www.cplusplus.com/reference/cctype/isdigit/

#include <cctype.h> // isdigit() 
// explore https://www.cplusplus.com/reference/cctype/

bool isNumber(const string &str) {
	for (char const &c: str) {
		if (isdigit(c) == 0) 
			return false;
	}
	return true;
}

// after exploring important functions are
/*
	isalnum
	isalpha
	isdigit
	islower
	isupper
	isspace
	ispunct    //{~`!@#$%^&*()_+-={}[]\|;':"<>?,./}

/*