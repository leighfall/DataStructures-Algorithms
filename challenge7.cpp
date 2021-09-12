// Challenge 07: sequence alignment
// Name: Autumn Henderson
// Date: April 18th, 2020
// Description: This program takes two strings and performs the Needleman Wunsch algorithm.

#include <iostream>  //string, cout, cin
#include <vector>	 //vector

using namespace std;

int Score(vector <vector <int> > &matrix, const string &s1, const string &s2) {
	
	int score;
	size_t i, j;

	//Populate first column and row
	matrix.at(0).at(0) = 0;
	matrix.at(1).at(0) = -1;
	matrix.at(0).at(1) = -1;
	
	for (i = 2; i < matrix.size(); i++) {
		matrix.at(i).at(0) = -1 + matrix.at(i-1).at(0);
	}
	for (j = 2; j < matrix.at(0).size(); j++) {
		matrix.at(0).at(j) = -1 + matrix.at(0).at(j-1);
	}

	//Populate the rest of the matrix
	for (i = 1; i <= s1.size(); i++) {
		for (j = 1; j <= s2.size(); j++) {

			//Determines if match or not
			if (s1.at(i - 1) == s2.at(j - 1)) score = 1;
			else score = -1;

			//Determines max	
			score = max ((matrix.at(i - 1).at(j - 1) + score), max((matrix.at(i - 1).at(j) - 1), (matrix.at(i).at(j - 1) -1)));	

			//Inserts
			matrix.at(i).at(j) = score;
		}
	}

	return score;
}

int main() {
    vector <vector <int> > matrix;
	string s1, s2;
	size_t i;
	int score;

	while(cin >> s1) {

		cin >> s2;
		
		matrix.resize(s1.size() + 1);
		for (i = 0; i < s1.size() + 1; i++) matrix.at(i).resize(s2.size() + 1);
	
		score = Score(matrix, s1, s2);
		
		cout << score << endl;

		matrix.resize(0);
	}

	return 0;
}


