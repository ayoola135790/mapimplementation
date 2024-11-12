//Project 1: Doubly Linked List for Map
//Emmanuel Ogunleye


#include "Map.h"
#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

// default contructor which initializes an empty map 
// Constructor definition
Map::Map() : head(nullptr), tail(nullptr), m_size(0) {}


//chceks if map is empty
bool Map::empty() const {
	//chose to do an if/else to check if size is 0, returns true else false
	if (m_size == 0) {
		return true;
	}
	else {
		return false;
	}
}

//returns the number of key-value pairs in map
int Map::size() const {

	//similar as previous functions if size is 0, returns 0
	//otherwise, returns the size
	if (m_size == 0) {
		return 0;
	}
	else {
		return m_size;
	}
}


//inserts a new key-value pair into the map
bool Map::insert(const KeyType& key, const ValueType& value) {
	//if key already exists, returns false 
	//(love my if/else statements) 
	if (contains(key)) {
		return false;
	}

	//creates a new node with the given key and value
	Node* newNode = new Node(key, value);

	//if map is empty, sets head and tail to new node
	if (empty()) {
		head = newNode;
	}
	else {
		//else it appends the new node to the end of the map
		tail->next = newNode;
		newNode->prev = tail;
	}
	tail = newNode;

	//increases the size and returns true 
	m_size++;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	//starts at the head of the linked list
	Node* current = head;

	//traverse
	while (current != nullptr)
	{

		if (current->name == key)
		{
			//update value of node
			//if the current node's key matches the given key
			current->value = value;

			return true;
		}
		// Move to the next node
		current = current->next;
	}

	//if the key is not found in the linked list, return false
	return false;
}



//inserts a new key-value or updates value if key already exists  
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {

	//tries to update the value, if it works, returns true 
	if (update(key, value)) {
		return true;
	}
	else {
		//else it tries to insert the new key-value pair and returns the result
		return insert(key, value);
	}
}

//updates the value associated with a key, if key exists
bool Map::erase(const KeyType& key) {
	Node* current = head;
	while (current != nullptr) {
		//if key is found, remove the node and adjusts the pointer
		if (current->name == key) {
			//erase the node
			if (current == head && current == tail) {
				head = nullptr;
				tail = nullptr;
			}
			else if (current == head) {
				head = current->next;
				if (head != nullptr) {
					head->prev = nullptr;
				}
			}
			else if (current == tail) {
				tail = current->prev;
				if (tail != nullptr) {
					tail->next = nullptr;
				}
			}
			else {
				current->prev->next = current->next;
				current->next->prev = current->prev;
			}
			//deletes the node, decreases the size, then returns true 
			delete current;
			m_size--;
			return true;
		}
		current = current->next;
	}
	//if not found, returns false
	return false;
}



bool Map::contains(const KeyType& key) const {
	Node* current = head;

	// Traverse 
	while (current != nullptr) {
		if (current->name == key) {
			return true;
		}
		current = current->next;
	}
	return false;
}

//retrives the value associated with the given key
bool Map::get(const KeyType& key, ValueType& value) const {

	//almost missed const here, since I didn't have it
	//cost me a long time to figure out
	Node* current = head;
	while (current != nullptr) {
		//if the key is found, it returns true
		if (current->name == key) {
			value = current->value;
			return true;
		}
		current = current->next;
	}
	//not found, returns false 
	return false;
}


///retrieves the key-value pair at a specific index
bool Map::get(int i, KeyType& key, ValueType& value) const {

	//checks if the index is within the range
	if (i < 0 || i >= m_size) {
		return false;
	}

	//start from the head of the linked list
	Node* current = head;

	//traverses the linked list to reach the desired index
	for (int a = 0; a < i; a++) {
		current = current->next;
	}

	//retrieve the key and value from the node at the desired index
	key = current->name;
	value = current->value;
	return true;
}

//swaps the contents of this map with another 
void Map::swap(Map& other) {

	//swapping head, tail, and size between the two maps
	Node* t_head = head;
	head = other.head;
	other.head = t_head;

	Node* t_tail = tail;
	tail = other.tail;
	other.tail = t_tail;

	int t_size = m_size;
	m_size = other.m_size;
	other.m_size = t_size;
}


void subtract(const Map& m1, const Map& m2, Map& result)
{
	// Clear the result map
	result = Map();

	//iterate over each key-value pair in m1
	for (int i = 0; i < m1.size(); i++)
	{
		KeyType key;
		ValueType value;

		//Retrieve key-value pair at index i from m1
		m1.get(i, key, value);

		//if the key does not exist in m2, insert the pair into the result map/
		if (!m2.contains(key))
		{
			result.insert(key, value);
		}
	}
}


//Destructor
Map:: ~Map() {
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}

}

//Copy constructor
Map::Map(const Map& other) {
	head = nullptr;
	tail = nullptr;
	m_size = 0;

	//copies the key value pairs from the other map
	Node* current = other.head;
	while (current != nullptr) {
		insert(current->name, current->value);
		current = current->next;
	}
}


//Assignment operator
const Map& Map:: operator=(const Map& rhs) {
	if (this != &rhs) {
		//creates a temporary map and swaps contents with this map
		Map temp(rhs);
		swap(temp);

		Node* curr = head;
		while (curr != nullptr) {
			Node* next = curr->next;
			delete curr;
			curr = next;
		}
		head = nullptr;
		tail = nullptr;
		m_size = 0;
	}
	return *this;
}

void print(const Map& m)
{
	cout << endl << left << setw(10) << "Key:" << left << setw(10) << "Value:" << endl << endl;
	for (int i = 0; i < m.size(); i++)
	{
		KeyType name;
		ValueType value;
		m.get(i, name, value);
		cout << left << fixed << setprecision(2) << setw(10) << name;
		cout << left << fixed << setprecision(2) << setw(10) << value << endl;
	}

}

int main() {

}