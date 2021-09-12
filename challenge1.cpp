//Title: Challenge 01 - Rotating Arrays
//Description: Given an array of integers, a number, and a direction, this program
//performs a number of rotations on the integers in the given direction and prints
//the results.
//
//Compiles using g++ -std=c++98 -Wall -Wextra -o solution solution.cpp

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main() {

	string instructions; //Commands
	string original;	 //numbers to be stored in vector
	int numsToShift;	 //size of string
	int numTimes;		 //amount that numbers are shifted from original location
	char command;		 //L or R
	int integers;		 //Numbers for the vector
	int i;
	istringstream iss;

	vector <int> tmp;
	vector <int> result;

	//While instructions can be read from the input file
	while (getline(cin, instructions)) {

		//Reads commands and string in from standard input
		iss.clear();
		iss.str(instructions);
		iss >> numsToShift >> numTimes >> command;

		iss.clear();
		getline(cin, original);
		iss.str(original);
		while (iss >> integers) tmp.push_back(integers);

		//Ensures the number of times it needs to be shifted does not exceed its size
		while (numTimes > numsToShift) numTimes -= numsToShift;
		
		//Completes left shift
		if (command == 'L') {

			//Places rest of the numbers
			for(i = numTimes; i < numsToShift; i++)	result.push_back(tmp.at(i));

			//Stores numTimes numbers back on the end
			for(i = 0; i < numTimes; i++) result.push_back(tmp.at(i));
		}

		//Completes right shift
		if (command == 'R') {

			//Places numTimes numbers on back end at the front
			for(i = 0; i < numTimes; i++) result.push_back(tmp.at(i + (numsToShift - numTimes)));

			//Stores numsToShift - numTimes numbers from tmp on the end of result
			for(i = 0; i < numsToShift - numTimes; i++) result.push_back(tmp.at(i));
		}
	
		//Prints
		for (i = 0; i < (int)result.size() - 1; i++) cout << result.at(i) << " ";
		cout << result.back() << endl;

		tmp.clear();
		result.clear();
	}

	return 0;
}
