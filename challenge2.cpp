// Challenge 02: Closest Numbers
// Name: Autumn Henderson
// Description: Given a list of unsorted integers, this program finds the pair of elements that
// have the smallest absolute difference between them.

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

// Main Execution

int main() {
    
	int size;
	int integers;
	string str;
	istringstream iss;
	int difference;
	int tmp;
	vector <int> v;
	vector <int> s;
	
	//Read in integers from standard input and put in vector

	while (getline(cin, str)) {
		
		//Takes in inputs
		iss.clear();
		iss.str(str);
		iss >> size;

		iss.clear();
		getline(cin, str);
		iss.str(str);
		while (iss >> integers) v.push_back(integers);
	

		//Sort vector
		sort(v.begin(), v.end());

		//Assigns first difference
		difference = v.at(1) - v.at(0);

		//run loop comparing difference of i and i + 1
		for (int i = 0; i < (int)v.size() - 1; i++) {

			tmp = v.at(i + 1) - v.at(i);
		
			//If tmp and difference are equal, adds new pairs to vector s
			if (tmp == difference) {
				difference = tmp;
				s.push_back(v.at(i));
				s.push_back(v.at(i+1));
			}
			
			//Else, if the tmp is less than the difference, replace tmp and restart vector s
			else if (tmp < difference) {
				difference = tmp;
				s.clear();
				s.push_back(v.at(i));
				s.push_back(v.at(i+1));
			}
		}

		//Print
		for(int i = 0; i < (int)s.size() - 1; i++) cout << s.at(i) << " ";	
		cout << s.back() << endl;
	
		//Clear vectors
		s.clear();
		v.clear();
	}
	return EXIT_SUCCESS;
}
