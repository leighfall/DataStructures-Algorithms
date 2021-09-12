// Name: Autumn Henderson
// Date: April 25th, 2020
// Description: This program takes in pairs of arbitrary length integers into a
// custom, user-defined linked list and adds each pair of numbers, producing the
// sum.

// Challenge 06: Adding List-Based Integers
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//Forward declaration of class List
template<typename T> class List;

//Class Node
template<typename T>
class Node{

	friend class List<T>;

	public:
		Node(const T &);
		T getData() const;
		T data;
		Node<T> *next;
};

//Class List
template<typename T>
class List {
	public:
		List();
		~List();
		void Push_Front(Node<T> *newnode);
		void Push_Back(Node<T> *newnode);
		bool empty();
		void print();
		void clear();

		Node<T> *first;
};

//Global function add_lists takes three Lists of type int and returns
//a void. The function adds the first two lists and stores it in the
//third list.
void add_lists(List<int> &l1, List<int> &l2, List<int> &result) {

	int carry;
	Node <int> *ptr1;		//for List 1
	Node <int> *ptr2;		//for List 2
	Node <int> *newnode;	//for inserting into result
	int sum;
	int value1, value2;		//values to be added

	ptr1 = l1.first;
	ptr2 = l2.first;
	carry = 0;

	//While we haven't reached the end of either list
	while (ptr1 != NULL && ptr2 != NULL) {

		value1 = ptr1->getData();
		value2 = ptr2->getData();

		sum = value1 + value2 + carry;

		//Determines if carry is necessary
		if (sum > 9) {
			sum = sum - 10;
			carry = 1;
		}
		else carry = 0;

		//Inserts new node into result
		newnode = new Node<int>(sum);
		result.Push_Front(newnode);

		//Moves through the two lists
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;

	}

	//Takes the remainder of either list if they weren't the
	//same size and adds those values to result
	if(ptr1 == NULL && ptr2 != NULL) {
	
		//copy over rest of l2
		while(ptr2 != NULL) {
			sum = ptr2->data + carry;
			
			//Determines carry
			if (sum > 9) {
				sum = sum - 10;
				carry = 1;
			}
			else carry = 0;
			
			//Inserts value into result
			newnode = new Node<int>(sum);
			result.Push_Front(newnode);

			//Moves forward
			ptr2 = ptr2->next;
		}
	}
	else if (ptr2 == NULL && ptr1 != NULL) {
		
		//copy over rest of l1
		while(ptr1 != NULL) {
			
			//Determines carry
			sum = ptr1->data + carry;
			if (sum > 9) {
				sum = sum - 10;
				carry = 1;
			}
			else carry = 0;

			//Inserts value into result
			newnode = new Node<int>(sum);
			result.Push_Front(newnode);

			//Moves forward
			ptr1 = ptr1->next;
		}
	}

	//Determines final carry (ie result is larger than original values)
	if (carry == 1) {
		newnode = new Node<int>(carry);
		result.Push_Front(newnode);
	}
}

int main() {
    
	List <int> l1, l2, result;
	string integer1, integer2;
	string line;
	int value;
	Node <int> *newnode;
	istringstream iss;
	size_t i;

	//While there is input to add
	while (getline(cin, line)) {

		//Takes in input
		iss.clear();
		iss.str(line);
		iss >> integer1 >> integer2;

		i = 0;

		//Adds values to first list
		while (i < integer1.size()) {
			value = integer1.at(i) - '0';
			newnode = new Node<int>(value);
			l1.Push_Front(newnode);
			i++;
		}
		
		i = 0;

		//Adds values to second list
		while (i < integer2.size()) {

			value = integer2.at(i) - '0';
			newnode = new Node<int>(value);
			l2.Push_Front(newnode);

			i++;
		}

		//Call add function
		add_lists(l1, l2, result);

		//Print results
		result.print();

		//Clears everything
		l1.clear();
		l2.clear();
		result.clear();
	} 
	
	return 0;
}



/*---For Node Class---*/

template<typename T>
Node<T>::Node(const T &newdata) {
	data = newdata;
	next = NULL;
}

template<typename T>
T Node<T>::getData(void) const {
	return data;
}


/*---For List Class---*/

//Constructor
template<typename T>
List<T>::List() {first = NULL;}

//Destructor
template<typename T>
List<T>::~List() {
	clear();
}

//Clear function clears the list
template<typename T>
void List<T>::clear() {
	Node<T> *ptr1;
	Node<T> *ptr2;
	
	ptr1 = first;

	//delete other nodes;
	while(ptr1 != NULL) {
		
		ptr2 = ptr1->next;
		delete ptr1;
		ptr1 = ptr2;
	}

	first = NULL;
}

//Push_Front takes a node and appends it at the front of the list.
template<typename T>
void List<T>::Push_Front(Node<T> *newnode) {

	Node<T> *ptr;

	//Error checks for empty list
	if(first == NULL) first = newnode;
	else {
		ptr = first;
		first = newnode;
		newnode->next = ptr;
	}
}

//Returns whether list is empty
template<typename T>
bool List<T>::empty() { return (first == NULL); }

//Print function for printing a list
template<typename T>
void List<T>::print() {
	Node<T> *ptr;

	for(ptr = first; ptr != NULL; ptr = ptr->next) {
		cout << ptr->getData();
	}

	cout << endl;
}
