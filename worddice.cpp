//Name: Autumn Henderson
//Date: April 16th, 2020
//Description: Given some number of "word dice", this program checks a list of
//words to see if the word can be spelled with the given dice utilizing Edmonds-Karp
//algorithm.

#include <iostream>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

struct Node {
	string letters;			//Letters part of the die
	int index;
	vector <Node *> edges;	
	Node *backedge;
};

struct WordDice {
	Node *source;
	Node *sink;
	vector <Node *> dice;	//Source connect to each die
	vector <Node *> word;	//Sink connect to each letter of word
};

/* Function Print takes a graph and prints its contents
void Print(WordDice *graph) {
	
	size_t i, j;

	//Print Source Information
	cout << "Node " << graph->source->index << ": " << graph->source->letters
		<< " Edges to ";
	for (i = 0; i < graph->source->edges.size(); i++) {
		cout << graph->source->edges.at(i)->index << " ";
	}
	cout << endl;

	//Print Dice information
	for (i = 0; i < graph->dice.size(); i++) {
		cout << "Node " << graph->dice.at(i)->index << ": " << graph->dice.at(i)->letters
			<< " Edges to ";
		for (j = 0; j < graph->dice.at(i)->edges.size(); j++) {
			cout << graph->dice.at(i)->edges.at(j)->index << " ";
		}
		cout << endl;
	}

	//Print Word information
	for (i = 0; i < graph->word.size(); i++) {
		cout << "Node " << graph->word.at(i)->index << ": " << graph->word.at(i)->letters
			<< " Edges to ";
		for (j = 0; j < graph->word.at(i)->edges.size(); j++) {
			cout << graph->word.at(i)->edges.at(j)->index << " ";
		}
		cout << endl;
	}

	//Print Sink information
	cout << "Node " << graph->sink->index << ": " << graph->sink->letters
		<< " Edges to ";
	for (i = 0; i < graph->sink->edges.size(); i++) {
		cout << graph->sink->edges.at(i)->index << " ";
	}
	cout << endl;

	cout << endl;
}
*/

int BFS(WordDice *graph) {
	size_t i, j;
	Node *ptr;
	//Clear all backedges
	
	graph->source->backedge = NULL;
	for(i = 0; i < graph->dice.size(); i++) {
		graph->dice.at(i)->backedge = NULL;
	}
	for(i = 0; i < graph->word.size(); i++) {
		graph->word.at(i)->backedge = NULL;
	}
	
	//Runs through Source's adjacency list
	for (i = 0; i < graph->source->edges.size(); i++) {
		ptr = graph->source->edges.at(i);

		//If there is an edge between dice and letter
		for (j = 0; j < ptr->edges.size(); j++) {

			if (ptr->edges.at(j)->index == 0) continue;

			//Set sink backedge
			graph->sink->backedge = ptr->edges.at(j);
			//Set word letter backedge
			ptr->edges.at(j)->backedge = ptr;
			//Set dice backedge
			ptr->backedge = graph->source;
			return 1;
		}
	}

	return 0;
}

//Function Swap_Edges takes all backedges not equal to NULL and assigns them
//to each node's edges.
void Swap_Edges(WordDice *graph) {
	size_t i;
	size_t j;
	bool exist;

	//Swap Backedge of dice
	for(i = 0; i < graph->source->edges.size(); i++) {
		if(graph->source->edges.at(i)->backedge != NULL) {
			for(j = 0; j < graph->source->edges.at(i)->edges.size(); j++) {
				if(graph->source->edges.at(i)->edges.at(j) != 0) {
					graph->source->edges.at(i)->edges.at(j) = graph->source;
				}
			}
		}
	}

	//Swap Backedge of word letter
	for(i = 0; i < graph->word.size(); i++) {
		if(graph->word.at(i)->backedge != NULL) {
			graph->word.at(i)->edges.at(0) = graph->word.at(i)->backedge;
		}
	}

	exist = false;
	//Set Sink edge
	for (i = 0; i < graph->sink->edges.size(); i++) {
		if(graph->sink->backedge->index == graph->sink->edges.at(i)->index) exist = true; 
	}
	if (exist == false) graph->sink->edges.push_back(graph->sink->backedge);

	//Remove Processed edge from Source
	graph->source->edges.erase(graph->source->edges.begin());
}

//AbletoSpell takes a graph and the word it's trying to spell
//and determines whether the word can be spelled.
int AbletoSpell(WordDice *graph, string fileword) {
	int rv;
	
	while(graph->sink->edges.size() < fileword.size()) {
		rv = BFS(graph);
		if (rv == false) break;
		
		Swap_Edges(graph);
	}
	
	if (graph->sink->edges.size() == fileword.size()) {
		return 1;
	}

	return 0;
}

//Print Solution takes a graph and a bool and determines which statements
//to print based off of whether a word was able to be spelled or not
void PrintSolution(WordDice *graph, bool solution, string word) {
	size_t i;

	if (solution == false) cout << "Cannot spell " << word;
	else {
		for (i = 0; i < graph->word.size() - 1; i++) {
			cout << graph->word.at(i)->edges.at(0)->index << ", ";
		}
		cout << graph->word.at(i)->edges.at(0)->index << ": " << word;
	}

	cout << endl;
}

//Function DeleteGraph takes a graph and deletes all created
//nodes. It returns a void.
void DeleteGraph(WordDice *graph) {
	Node *ptr;
	size_t i;

	//Delete Source & Sink
	ptr = graph->source;
	delete ptr;
	ptr = graph->sink;
	delete ptr;

	//Delete Dice
	for (i = 0; i < graph->dice.size(); i++) {
		ptr = graph->dice.at(i);
		delete ptr;
	}

	//Delete Word
	for (i = 0; i < graph->word.size(); i++) {
		ptr = graph->word.at(i);
		delete ptr;

	}
}


int main(int argc, char **argv) {

	string dice;
	string word;
	ifstream file;
	ifstream file2;
	string letters;
	string filewords;
	Node *die;
	Node *letter;
	WordDice *graph;
	int i;
	set <char> curr_letters;
	set <char>::iterator sit;
	string char_of_letters_string;
	int can_spell;

	if (argc != 3) {
		cout << "Usage: ./worddice file1.txt file2.txt\n";
		return -1;
	}

	dice = argv[1];
	word = argv[2];

	//Open and read in word information
	file.open(word.c_str());
	
	if (!file) {
		cerr << "Unable to open " << word << endl;
		return -3;
	}

	while(file >> filewords) {

		graph = new WordDice;

		//Open and read in dice information
		file2.open(dice.c_str());
		if (!file2) {
			cerr << "Unable to open " << dice << endl;
			return -2;
		}

		i = 1;

		//Assigns Letters, Index, & fills the Dice vector
		while(file2 >> letters) {
			die = new Node;
			die->letters = letters;
			die->index = i;
			graph->dice.push_back(die);
			i++;
		}

		file2.close();

		//Assigns Letters with each letter of the word, the index, and fills the Words vector
		for (int j = 0; j < (int)filewords.size(); j++) {
			letter = new Node;
			letter->letters = filewords.at(j);
			letter->index = i;
			graph->word.push_back(letter);
			i++;
		}

		//Assigns edges of all nodes
		
		//Iterates through each dice
		for (int j = 0; j < (int)graph->dice.size(); j++) {
			
			//Iterates through dice's 'letters' string
			for (int k = 0; k < (int)graph->dice.at(j)->letters.size(); k++) {
				
				//Iterates through curr_letters to see if letter has been processed already
				sit = curr_letters.find(graph->dice.at(j)->letters.at(k));
				if (sit == curr_letters.end()) {
					curr_letters.insert(graph->dice.at(j)->letters.at(k));

					//Take the letter and compare to word letters and assign edges
					for (int l = 0; l < (int)graph->word.size(); l++) {
						char_of_letters_string = graph->dice.at(j)->letters.at(k);
						if (char_of_letters_string == graph->word.at(l)->letters) {
							graph->dice.at(j)->edges.push_back(graph->word.at(l));
						}
					}
				}
			}
			
			curr_letters.clear();
		}

		//Assigns Source & Sink Edges
		graph->source = new Node;
		graph->source->letters = "SOURCE";
		graph->source->index = 0;
		for (int j = 0; j < (int)graph->dice.size(); j++) {
			graph->source->edges.push_back(graph->dice.at(j));
		}

		graph->sink = new Node;
		graph->sink->letters = "SINK";
		graph->sink->index = i;
	
		//Assigns Word Edges
		for (int j = 0; j < (int)graph->word.size(); j++) {
			graph->word.at(j)->edges.push_back(graph->sink);
		}
		
		i = 0;

		can_spell = AbletoSpell(graph, filewords);
		PrintSolution(graph, can_spell, filewords);
		DeleteGraph(graph);
	}

	file.close();

	return 0;
}
