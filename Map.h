// guards for the project, since pragma is not guaranteed
// to work in the complier
#ifndef map_h
#define map_h

#include <iostream>
#include <string>

//no need for using namespace std;
using KeyType = std::string;
using ValueType = double;

//Map class for storing key-value pairs 
class Map
{

private:
	struct Node {

		//value that is associated with
		ValueType value;
		//the key for the map
		KeyType name;
		//chose a doubly linked list data structure
		//pointer to previous node
		Node* prev;
		//pointer to the next node
		Node* next;

		//Constructor intializing the node
		//with key, value, and pointers
		Node(const KeyType& n, const ValueType& v, Node* p = nullptr, Node* t = nullptr) :
			name(n), value(v), prev(p), next(t) {}
	};

	//pointer to first node in linked list 
	Node* head;
	Node* tail;
	int m_size;

public:
	//function declarations 
	Map();              // Create an empty map 

	//Destructor
	~Map();


	bool empty() const; // Return true if the map is empty, otherwise false.

	int size() const;   // Return the number of key/value pairs in the map.

	bool insert(const KeyType& key, const ValueType& value);
	// If key is not equal to any key currently in the map, and if the
	// key/value pair can be added to the map, then do so and return true.
	// Otherwise, make no change to the map and return false (indicating
	// that either the key is already in the map).

	bool update(const KeyType& key, const ValueType& value);
	// If key is equal to a key currently in the map, then make that key no
	// longer map to the value it currently maps to, but instead map to
	// the value of the second parameter; return true in this case.
	// Otherwise, make no change to the map and return false.

	bool insertOrUpdate(const KeyType& key, const ValueType& value);
	// If key is equal to a key currently in the map, then make that key no
	// longer map to the value it currently maps to, but instead map to
	// the value of the second parameter; return true in this case.
	// If key is not equal to any key currently in the map then add it and 
	// return true. In fact this function always returns true.

	bool erase(const KeyType& key);
	// If key is equal to a key currently in the map, remove the key/value
	// pair with that key from the map and return true.  Otherwise, make
	// no change to the map and return false.

	bool contains(const KeyType& key) const;
	// Return true if key is equal to a key currently in the map, otherwise
	// false.

	bool get(const KeyType& key, ValueType& value) const;
	// If key is equal to a key currently in the map, set value to the
	// value in the map that that key maps to, and return true.  Otherwise,
	// make no change to the value parameter of this function and return
	// false.

	bool get(int i, KeyType& key, ValueType& value) const;
	// If 0 <= i < size(), copy into the key and value parameters the
	// key and value of one of the key/value pairs in the map and return
	// true.  Otherwise, leave the key and value parameters unchanged and
	// return false.  (See below for details about this function.)

	void swap(Map& other);
	// Exchange the contents of this map with the other one.

	Map(const Map& other);
	const Map& operator=(const Map& rhs);


};


void subtract(const Map& m1, const Map& m2, Map& result);
void print(const Map& m);

#endif 


