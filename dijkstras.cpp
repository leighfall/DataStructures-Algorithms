//Name: Autumn Henderson
//Date: March 12th, 2020
//Title: Project 4: Path Finding
//Description: This program implements Dijsktra's algorithm to find the shortest
//path in a given 2D landscape.

#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

struct Node {

	int x;			//X coordinate within grid
	int y;			//Y coordinate within grid
	int weight;		//Cost to move through node
	int distance;	//Current optimal distance to node
	char type;		//terrain type

	bool visited;
	Node *backedge;
	vector<Node *> adj;
};

/*Function for Printing the Grid
void Print_Grid(const vector<vector<Node *> > &grid) {

	size_t i, j;
	Node *ptr;

	for(i = 0; i < grid.size(); i++) {

		for(j = 0; j < grid.at(i).size(); j++) {
			ptr = grid.at(i).at(j);
			cout << ptr->type;
		}
		cout << endl;
	}
	
	cout << endl;
}
*/
/*Function for Printing Node Information
void Print_Node(const Node *node) {
	Node *ptr;

	cout << "Node: (" << node->x << ", " << node->y << ")\n";
	cout << "X: " << node->x << " Y: " << node->y << endl;
	cout << "Weight: " << node->weight << endl;
	cout << "Distance: " << node->distance << endl;
	cout << "Type: " << node->type << endl;
	cout << "Visited: " << node->visited << endl;
	if(node->backedge != NULL) cout << "Backedge: " << node->backedge->x << " " << node->backedge->y << endl;
	for(size_t i = 0; i < node->adj.size(); i++) {
		ptr = node->adj.at(i);
		cout << ptr->type << " ";
	}
	cout << endl;
	cout << endl;
}
*/

//Main Function
int main() {
    vector<vector<Node *> > grid;	//Map
	int num_diff_tiles;
	int f, g, G, h, m, r;			//Values of map places
	char tile_type;					//Defines tiles
	int num_rows_of_grid, num_cols_of_grid;  
	multimap<int, Node *> mm;
	multimap<int, Node *>::iterator mit;
	Node *node, *node2, *start_node, *end_node;
	Node *ptr;
	int start_x, start_y;
	int end_x, end_y;
	int d;							//Distance
	list<Node *> backedges;
	list<Node *>::iterator lit;

	/*---Populate Grid---*/
	
	cin >> num_diff_tiles;

	//Tile values
	cin >> tile_type >> f;
	cin >> tile_type >> g;
	cin >> tile_type >> G;
	cin >> tile_type >> h;
	cin >> tile_type >> m;
	cin >> tile_type >> r;

	//Rows & Cols
	cin >> num_rows_of_grid >> num_cols_of_grid;

	//Grid
	grid.resize(num_rows_of_grid);
	for(int i = 0; i < num_rows_of_grid; i++) grid.at(i).resize(num_cols_of_grid);

	for(int i = 0; i < num_rows_of_grid; i++) {
		for(int j = 0; j < num_cols_of_grid; j++) {
			node = new Node;

			node->x = i;
			node->y = j;
			node->visited = false;
			node->backedge = NULL;
			node->distance = -1;

			cin >> tile_type;

			if(tile_type == 'f') {node->weight = f; node->type = 'f';}
			else if(tile_type == 'g') {node->weight = g; node->type = 'g';}
			else if(tile_type == 'G') {node->weight = G; node->type = 'G';}
			else if(tile_type == 'h') {node->weight = h; node->type = 'h';}
			else if(tile_type == 'm') {node->weight = m; node->type = 'm';}
			else {node->weight = r; node->type = 'r';}

			grid.at(i).at(j) = node;
		}
	}

	/*---Populate adjacency lists---*/

	//Top Row
	for(int j = 0; j < num_cols_of_grid; j++) {
		
		node = grid.at(0).at(j);

		if(j == 0) {
			node->adj.push_back(grid.at(0).at(j+1));		//Node to Right
		}
		else if(j == (num_cols_of_grid - 1)) {
			node->adj.push_back(grid.at(0).at(j-1));		//Node to Left
		}
		else {
			node->adj.push_back(grid.at(0).at(j+1));		//Node to Right
			node->adj.push_back(grid.at(0).at(j-1));		//Node to Left
		}

		if(num_rows_of_grid > 1) node->adj.push_back(grid.at(1).at(j)); //Node underneath
	}

	//Bottom Row
	for(int j = 0; j < num_cols_of_grid; j++) {
		
		node = grid.at(num_rows_of_grid - 1).at(j);

		if(j == 0) {
			node->adj.push_back(grid.at(num_rows_of_grid - 1).at(j+1));	//Node to Right
		}
		else if(j == (num_cols_of_grid - 1)) {
			node->adj.push_back(grid.at(num_rows_of_grid - 1).at(j-1));	//Node to Left
		}
		else {
			node->adj.push_back(grid.at(num_rows_of_grid - 1).at(j+1));	//Node to Right
			node->adj.push_back(grid.at(num_rows_of_grid - 1).at(j-1));	//Node to Left
		}

		if(num_rows_of_grid > 1) 
			node->adj.push_back(grid.at(num_rows_of_grid - 2).at(j)); //Node above
	}

	//All other Rows
	for(int j = 0; j < num_cols_of_grid; j++) {
		for(int i = 1; i < num_rows_of_grid - 1; i++) {
			
			node = grid.at(i).at(j);

			if(j == 0) {
				node->adj.push_back(grid.at(i).at(j+1)); //Node to Right
			}
			else if (j == (num_cols_of_grid - 1)) {
				node->adj.push_back(grid.at(i).at(j-1)); //Node to Left
			}
			else {
				node->adj.push_back(grid.at(i).at(j+1)); //Node to Right
				node->adj.push_back(grid.at(i).at(j-1)); //Node to Left
			}

			node->adj.push_back(grid.at(i-1).at(j));		//Node above
			node->adj.push_back(grid.at(i+1).at(j));		//Node below
		}
	}

	
	/*---Dijkstra's Algorithm---*/

	cin >> start_x >> start_y;
	cin >> end_x >> end_y;

	start_node = grid.at(start_x).at(start_y); //Assigns starting node
	end_node = grid.at(end_x).at(end_y); //Assigns ending node

	start_node->distance = 0;
	mm.insert(make_pair(start_node->distance, start_node));

	while(end_node->visited == 0) {

		//Remove node n from the front of the multimap and set its visited field to 'true'
		mit = mm.begin();
		node = mit->second;
		mm.erase(mit);
		node->visited = 1;

		for(int i = 0; i < (int)node->adj.size(); i++) {

			node2 = node->adj.at(i);
			if (node2->visited == 0) {
				
				d = node->distance + node->weight;
				
				if(node2->distance == -1 || d < node2->distance) {
					
					//If n2 was in the multimap, ignore it
					for(mit = mm.begin(); mit != mm.end(); mit++) {
						if(mit->second == node2) {
							mm.erase(mit);
							break;
						}
					}

					//Set n2's distance to d
					node2->distance = d;

					//set n2's backedge to n
					node2->backedge = node;

					//Insert n2 into the multimap, keyed on distance
					mm.insert(make_pair(node2->distance, node2));
				}
			}
		}
	}

	//Backtrace from target to beginning to find answer

	ptr = grid.at(end_node->x).at(end_node->y);
	while(ptr->backedge != NULL) {
		backedges.push_front(ptr->backedge);
		ptr = ptr->backedge;
	}

	/*---Printing---*/

	//Print Cost
	cout << end_node->distance << endl;

	//Print Path
	for(lit = backedges.begin(); lit != backedges.end(); lit++) {
	
		ptr = *lit;
		cout << ptr->x << " " << ptr->y << endl;
	}
	
	cout << end_node->x << " " << end_node->y << endl;

	//Delete all nodes
	
	for(int i = 0; i < num_rows_of_grid; i++) {
		for(int j = 0; j < num_cols_of_grid; j++) {
			ptr = grid.at(i).at(j);
			delete ptr;
		}
	}

	return 0;
}

