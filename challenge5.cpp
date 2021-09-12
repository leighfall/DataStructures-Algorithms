// Challenge 05: Graph Paths
// Name: Autumn Henderson
// Date: February 22nd, 2020
// Description: Given a directed graph, this program determines if there is a path between
// two nodes in the graph

#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Main Execution

int main() {

	map <char, vector<char> > adj_list;
	map <char, vector<char> >::iterator nit;
	vector <char> v;
	vector <char> v2;
	int nedges;
	int npaths;
	char c1, c2;
	int graph_num;
	size_t i;
	bool edge_exist;

	graph_num = 1;

	while(cin >> nedges) {

		for(int j = 0; j < nedges; j++) {
			cin >> c1 >> c2;

			/*---Populate the full map---*/

			nit = adj_list.find(c1);
			
			//If c1 does not exist...
			if (nit == adj_list.end()) {
				//Create v with c2 as the first entry
				v.push_back(c2);
				//Insert into the map
				adj_list.insert(make_pair(c1, v));
			}
			//Else c1 already exists, push back on existing vector with c2
			else {
				if (nit->second.at(0) == '0') nit->second.at(0) = c2;
				else nit->second.push_back(c2);
			}
			
			//Ensure that all characters taken in are represented in the map
			nit = adj_list.find(c2);
			 
			if (nit == adj_list.end()) {
				v2.push_back('0');
				adj_list.insert(make_pair(c2, v2));
			}

			v.clear();
			v2.clear();

		}

		cin >> npaths;

		for (int j = 0; j < npaths; j++) {

			cin >> c1 >> c2;
			edge_exist = false;

			/*---Traversal---*/

			nit = adj_list.find(c1);
			
			for (i = 0; i < nit->second.size(); i++) {
				if (nit->second.at(i) == c2) {
					cout << "In Graph " << graph_num << " there is a path from " << c1 << " to " << c2 << endl;
					edge_exist = true;
				}
			}

			if (edge_exist == false) cout << "In Graph " << graph_num << " there is no path from " << c1 << " to " << c2 << endl;
		
		}
			
		/*---Resets variables---*/
			
		
		graph_num++;
		adj_list.clear();	
		cout << endl;
	}

	return (0);
}


