// Challenge 03: Palindrome Permutation
// Name: Autumn Henderson
// Description: Given a string, this program determines if any permutation of the phrase
// (ignoring whitespace and punctuation) is a palindrome.

// References:
// geeksforgeeks.org/unordered_map-in-cpp-stl for how to initialize and
// iterate through an unordered map
// cplusplus.com/reference/cctype for how to use ispunct and isdigit functions for removing
// punctuation and digits

#include <iostream>
#include <unordered_map>
#include <ctype.h>

using namespace std;

int main() {
  
	string original;
	string altered;
	unordered_map <char, int> character_count;
	bool is_palindrome_permutation;
	int num_odd_chars;

	is_palindrome_permutation = false;
	num_odd_chars = 0;
	altered = "";

	while (getline(cin, original)) {

		//Filters out spaces, punctuation, numbers
		for (int i = 0; i < (int)original.size(); i++) {
			if (original.at(i) != ' ' && !ispunct(original.at(i)) && !isdigit(original.at(i))) {
				altered += original.at(i);
			}
		}

		//Populates map
		for (const auto &nit: altered) {
			if (character_count.find(nit) == character_count.end()) character_count[nit] = 1;
			else character_count[nit]++;
		}

		//Counts up odd occurrances
		for (auto i = character_count.begin(); i != character_count.end(); i++) {
			if ((i->second % 2) == 1) num_odd_chars++;
		}
	
		//Determines whether the original string is a palindrome permutation
		if (num_odd_chars <= 1) is_palindrome_permutation = true;

		//Prints whether phrase is palindrome permutation
		if (is_palindrome_permutation) cout << "\"" << original << "\" is a palindrome permutation\n";
		else cout << "\"" << original << "\" is not a palindrome permutation\n";

		//Resets
		is_palindrome_permutation = false;
		num_odd_chars = 0;
		character_count.clear();
		altered = "";
	}
	
	return (0);
}

