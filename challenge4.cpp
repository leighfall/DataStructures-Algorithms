// Challenge 04: kth smallest numbers
// Name:  Autumn Henderson

// Brief description: Given a list of integers and a number k, this program finds the kth
// smallest elements without sorting or doing k successive scans.

// References: cplusplus.com/reference/queue/priority_queue/ for how to declare and use a 
// priority queue, make a min heap, and push and pop.

#include <iostream> //cout
#include <vector>	//vector
#include <sstream>	//istringstream
#include <queue>	//priority queue

using namespace std;

bool Is_Max(const vector<int> &v);

int main() {

	int N;				//# of elements in v
	int k;				//kth value
	int values;			//values for v
	string directions;	//N k
	string input;		//{a1, a2, ..., aN}
	istringstream iss;	//Processing input
	vector <int> v;		//container
	priority_queue<int, vector<int>, greater<int>> min; //make min heap
	bool max;			//Max heap or not

	while(getline(cin, directions)) {

		//Processes standard input
		iss.clear();
		iss.str(directions);
		iss >> N >> k;

		iss.clear();
		getline(cin, input);
		iss.str(input);

		while(iss >> values) v.push_back(values);

		//Checks if Max Heap
		max = Is_Max(v);
		if (max == true) cout << "Y  ";
		else cout << "N  ";

		//Makes Min Heap
		for(int i = 0; i < (int)v.size(); i++) min.push(v.at(i));

		//Finds k-1 smallest element
		k = k - 1;
		while (k != 0) {
			min.pop();
			k--;
		}

		cout << min.top() << endl;

		//Resets
		v.clear();
		while(min.empty() == false) min.pop();
	}

	return 0;
}

//Function Is_Max takes a vector by reference and returns whether it is a
//max heap or not
bool Is_Max(const vector<int> &v) {
	
	int i;
	bool is_max = true;

	for (i = 0; i < ((int)v.size() - 2) / 2; i++) {
		if(v.at(i) < v.at(2*i+1) || v.at(i) < v.at(2*i+2)) {
			is_max = false;
			break;
		}
	}

	return is_max;
}
